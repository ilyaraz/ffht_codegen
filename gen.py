def float_avx_0(from_register, to_register, aux_registers, ident=''):
    """
    from_register can be the same as to_register, but both must be disjoint from aux_registers
    """
    if len(aux_registers) != 4:
        raise Exception('need four auxiliary registers')
    res  = ident + '"vpermilps $160, %s, %s\\n"\n' % (from_register, aux_registers[0])
    res += ident + '"vpermilps $245, %s, %s\\n"\n' % (from_register, aux_registers[1])
    res += ident + '"vxorps %s, %s, %s\\n"\n' % (aux_registers[2], aux_registers[2], aux_registers[2])
    res += ident + '"vsubps %s, %s, %s\\n"\n' % (aux_registers[1], aux_registers[2], aux_registers[3])
    res += ident + '"vaddsubps %s, %s, %s\\n"\n' % (aux_registers[3], aux_registers[0], to_register)
    return res

def float_avx_1(from_register, to_register, aux_registers, ident=''):
    """
    from_register can be the same as to_register, but both must be disjoint from aux_registers
    """
    if len(aux_registers) != 5:
        raise Exception('need five auxiliary registers')
    res  = ident + '"vpermilps $68, %s, %s\\n"\n' % (from_register, aux_registers[0])
    res += ident + '"vpermilps $238, %s, %s\\n"\n' % (from_register, aux_registers[1])
    res += ident + '"vxorps %s, %s, %s\\n"\n' % (aux_registers[2], aux_registers[2], aux_registers[2])
    res += ident + '"vsubps %s, %s, %s\\n"\n' % (aux_registers[1], aux_registers[2], aux_registers[3])
    res += ident + '"vblendps $204, %s, %s, %s\\n"\n' % (aux_registers[3], aux_registers[1], aux_registers[4])
    res += ident + '"vaddps %s, %s, %s\\n"\n' % (aux_registers[0], aux_registers[4], to_register)
    return res

def float_avx_2(from_register, to_register, aux_registers, ident=''):
    """
    from_register can be the same as to_register, but both must be disjoint from aux_registers
    """
    if len(aux_registers) != 4:
        raise Exception('need four auxiliary registers')
    res  = ident + '"vxorps %s, %s, %s\\n"\n' % (aux_registers[0], aux_registers[0], aux_registers[0])
    res += ident + '"vsubps %s, %s, %s\\n"\n' % (from_register, aux_registers[0], aux_registers[1])
    res += ident + '"vperm2f128 $0, %s, %s, %s\\n"\n' % (from_register, from_register, aux_registers[2])
    res += ident + '"vperm2f128 $49, %s, %s, %s\\n"\n' % (aux_registers[1], from_register, aux_registers[3])
    res += ident + '"vaddps %s, %s, %s\\n"\n' % (aux_registers[2], aux_registers[3], to_register)
    return res

def float_avx_3_etc(from_register_1, from_register_2, to_register_1, to_register_2, ident=''):
    """
    all four registers must be distinct
    """
    res  = ident + '"vaddps %s, %s, %s\\n"\n' % (from_register_2, from_register_1, to_register_1)
    res += ident + '"vsubps %s, %s, %s\\n"\n' % (from_register_2, from_register_1, to_register_2)
    return res


def float_plain_step(log_n, it):
    if log_n <= 0:
        raise Exception("log_n must be positive")
    if it < 0:
        raise Exception("it must be non-negative")
    if it >= log_n:
        raise Exception("it must be smaller than log_n")
    n = 1 << log_n
    res  = "  for (int j = 0; j < %d; j += %d) {\n" % (n, 1 << (it + 1))
    res += "    for (int k = 0; k < %d; ++k) {\n" % (1 << it)
    res += "      float u = buf[j + k];\n"
    res += "      float v = buf[j + k + %d];\n" % (1 << it)
    res += "      buf[j + k] = u + v;\n"
    res += "      buf[j + k + %d] = u - v;\n" % (1 << it)
    res += "    }\n"
    res += "  }\n"
    return res

def float_avx_composite_step(log_n, from_it, to_it):
    if log_n < 3:
        raise Exception('need at least 8 elements for AVX')
    num_nontrivial_levels = 0
    if to_it > 3:
        first_nontrivial = max(from_it, 3)
        num_nontrivial_levels = to_it - first_nontrivial
        if num_nontrivial_levels > 3:
            raise Exception('not enough registers')
    n = 1 << log_n
    input_registers = []
    output_registers = []
    for l in range(8):
        input_registers.append('%%ymm' + str(l))
        output_registers.append('%%ymm' + str(8 + l))
    if num_nontrivial_levels == 0:
        res  = '  for (int j = 0; j < %d; j += 8) {\n' % n
        res += '    __asm__ volatile (\n'
        res += '      "vmovups (%s), %s\\n"\n' % ('%0', input_registers[0])
        for it in range(from_it, to_it):
            if it == 0:
                res += float_avx_0(input_registers[0], input_registers[0], output_registers[:4], '      ')
            if it == 1:
                res += float_avx_1(input_registers[0], input_registers[0], output_registers[:5], '      ')
            if it == 2:
                res += float_avx_2(input_registers[0], input_registers[0], output_registers[:4], '      ')
        res += '      "vmovups %s, (%s)\\n"\n' % (input_registers[0], '%0')
        res += '      :: "r"(buf + j) : %s, "memory"\n' % (', '.join(['"%ymm' + str(k) + '"' for k in range(16)]))
        res += '    );\n'
        res += '  }\n'
        return res
    res  = '  for (int j = 0; j < %d; j += %d) {\n' % (n, 1 << to_it)
    res += '    for (int k = 0; k < %d; k += 8) {\n' % (1 << (to_it - num_nontrivial_levels))
    subcube = []
    for l in range(1 << num_nontrivial_levels):
        subcube.append('j + k + ' + str(l * (1 << (to_it - num_nontrivial_levels))))
    res += '      __asm__ volatile (\n'
    for l in range(1 << num_nontrivial_levels):
        res += '        "vmovups (%s), %s\\n"\n' % ('%' + str(l), input_registers[l])
    for it in range(from_it, 3):
        for ii in range(1 << num_nontrivial_levels):
            if it == 0:
                res += float_avx_0(input_registers[ii], input_registers[ii], output_registers[:4], '        ')
            if it == 1:
                res += float_avx_1(input_registers[ii], input_registers[ii], output_registers[:5], '        ')
            if it == 2:
                res += float_avx_2(input_registers[ii], input_registers[ii], output_registers[:4], '        ')
    for it in range(num_nontrivial_levels):
        for ii in range(0, 1 << num_nontrivial_levels, 1 << (it + 1)):
            for jj in range(1 << it):
                res += float_avx_3_etc(input_registers[ii + jj], input_registers[ii + jj + (1 << it)], output_registers[ii + jj], output_registers[ii + jj + (1 << it)], '        ')
        tmp = input_registers
        input_registers = output_registers
        output_registers = tmp
    for l in range(1 << num_nontrivial_levels):
        res += '        "vmovups %s, (%s)\\n"\n' % (input_registers[l], '%' + str(l))
    res += '        :: %s : %s, "memory"\n' % (', '.join(['"r"(buf + %s)' % x for x in subcube]), ', '.join(['"%ymm' + str(k) + '"' for k in range(16)]))
    res += '      );\n'
    res += '    }\n'
    res += '  }\n'
    return res

def float_avx_greedy_merged(log_n):
    res  = "inline void helper_%d(float *buf) {\n" % log_n
    if log_n < 6:
        res += float_avx_composite_step(log_n, 0, log_n)
    else:
        res += float_avx_composite_step(log_n, 0, 6)
        cur = 6
        while cur < log_n:
            new_end = cur + 3
            res += float_avx_composite_step(log_n, cur, min(new_end, log_n))
            cur = new_end
    res += "}\n"
    return res

def float_plain_unmerged(log_n):
    n = 1 << log_n
    res  = "inline void helper_%d(float *buf) {\n" % log_n
    for i in range(0, log_n):
        res += float_plain_step(log_n, i)
    res += "}\n"
    return res

for i in range(1, 31):
    if i < 3:
        print float_plain_unmerged(i)
    else:
        print float_avx_greedy_merged(i)

dispatch  = "void fht(float *buf, int log_n) {\n"
dispatch += "  if (log_n == 0) {\n"
dispatch += "  }\n"
for i in range(1, 31):
    dispatch += "  else if (log_n == %d) {\n" % i
    dispatch += '    helper_%d(buf);\n' % i
    dispatch += "  }\n"
dispatch += "  else {\n"
dispatch += "  }\n"
dispatch += "}\n"
print dispatch
