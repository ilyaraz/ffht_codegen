def float_avx_0(register, aux_registers, ident=''):
    """
    register must be disjoint from aux_registers
    """
    if len(aux_registers) < 4:
        raise Exception('need four auxiliary registers')
    res  = ident + '"vpermilps $160, %%%%%s, %%%%%s\\n"\n' % (register, aux_registers[0])
    res += ident + '"vpermilps $245, %%%%%s, %%%%%s\\n"\n' % (register, aux_registers[1])
    res += ident + '"vxorps %%%%%s, %%%%%s, %%%%%s\\n"\n' % (aux_registers[2], aux_registers[2], aux_registers[2])
    res += ident + '"vsubps %%%%%s, %%%%%s, %%%%%s\\n"\n' % (aux_registers[1], aux_registers[2], aux_registers[3])
    res += ident + '"vaddsubps %%%%%s, %%%%%s, %%%%%s\\n"\n' % (aux_registers[3], aux_registers[0], register)
    return res

def float_avx_1(register, aux_registers, ident=''):
    """
    register must be disjoint from aux_registers
    """
    if len(aux_registers) < 5:
        raise Exception('need five auxiliary registers')
    res  = ident + '"vpermilps $68, %%%%%s, %%%%%s\\n"\n' % (register, aux_registers[0])
    res += ident + '"vpermilps $238, %%%%%s, %%%%%s\\n"\n' % (register, aux_registers[1])
    res += ident + '"vxorps %%%%%s, %%%%%s, %%%%%s\\n"\n' % (aux_registers[2], aux_registers[2], aux_registers[2])
    res += ident + '"vsubps %%%%%s, %%%%%s, %%%%%s\\n"\n' % (aux_registers[1], aux_registers[2], aux_registers[3])
    res += ident + '"vblendps $204, %%%%%s, %%%%%s, %%%%%s\\n"\n' % (aux_registers[3], aux_registers[1], aux_registers[4])
    res += ident + '"vaddps %%%%%s, %%%%%s, %%%%%s\\n"\n' % (aux_registers[0], aux_registers[4], register)
    return res

def float_avx_2(register, aux_registers, ident=''):
    """
    register must be disjoint from aux_registers
    """
    if len(aux_registers) < 4:
        raise Exception('need four auxiliary registers')
    res  = ident + '"vxorps %%%%%s, %%%%%s, %%%%%s\\n"\n' % (aux_registers[0], aux_registers[0], aux_registers[0])
    res += ident + '"vsubps %%%%%s, %%%%%s, %%%%%s\\n"\n' % (register, aux_registers[0], aux_registers[1])
    res += ident + '"vperm2f128 $0, %%%%%s, %%%%%s, %%%%%s\\n"\n' % (register, register, aux_registers[2])
    res += ident + '"vperm2f128 $49, %%%%%s, %%%%%s, %%%%%s\\n"\n' % (aux_registers[1], register, aux_registers[3])
    res += ident + '"vaddps %%%%%s, %%%%%s, %%%%%s\\n"\n' % (aux_registers[2], aux_registers[3], register)
    return res

def float_avx_3_etc(from_register_0, from_register_1, to_register_0, to_register_1, ident=''):
    """
    all four registers must be distinct
    """
    res  = ident + '"vaddps %%%%%s, %%%%%s, %%%%%s\\n"\n' % (from_register_1, from_register_0, to_register_0)
    res += ident + '"vsubps %%%%%s, %%%%%s, %%%%%s\\n"\n' % (from_register_1, from_register_0, to_register_1)
    return res

def double_avx_0(register, aux_registers, ident=''):
    """
    register must be disjoint from aux_registers
    """
    if len(aux_registers) < 4:
        raise Exception('need four auxiliary registers')
    res  = ident + '"vpermilpd $0, %%%%%s, %%%%%s\\n"\n' % (register, aux_registers[0])
    res += ident + '"vpermilpd $15, %%%%%s, %%%%%s\\n"\n' % (register, aux_registers[1])
    res += ident + '"vxorpd %%%%%s, %%%%%s, %%%%%s\\n"\n' % (aux_registers[2], aux_registers[2], aux_registers[2])
    res += ident + '"vsubpd %%%%%s, %%%%%s, %%%%%s\\n"\n' % (aux_registers[1], aux_registers[2], aux_registers[3])
    res += ident + '"vaddsubpd %%%%%s, %%%%%s, %%%%%s\\n"\n' % (aux_registers[3], aux_registers[0], register)
    return res

def double_avx_1(register, aux_registers, ident=''):
    """
    register must be disjoint from aux_registers
    """
    if len(aux_registers) < 4:
        raise Exception('need four auxiliary registers')
    res  = ident + '"vperm2f128 $0, %%%%%s, %%%%%s, %%%%%s\\n"\n' % (register, register, aux_registers[0])
    res += ident + '"vxorpd %%%%%s, %%%%%s, %%%%%s\\n"\n' % (aux_registers[1], aux_registers[1], aux_registers[1])
    res += ident + '"vsubpd %%%%%s, %%%%%s, %%%%%s\\n"\n' % (register, aux_registers[1], aux_registers[2])
    res += ident + '"vperm2f128 $49, %%%%%s, %%%%%s, %%%%%s\\n"\n' % (aux_registers[2], register, aux_registers[3])
    res += ident + '"vaddpd %%%%%s, %%%%%s, %%%%%s\\n"\n' % (aux_registers[3], aux_registers[0], register)
    return res

def double_avx_2_etc(from_register_0, from_register_1, to_register_0, to_register_1, ident=''):
    """
    all four registers must be distinct
    """
    res  = ident + '"vaddpd %%%%%s, %%%%%s, %%%%%s\\n"\n' % (from_register_1, from_register_0, to_register_0)
    res += ident + '"vsubpd %%%%%s, %%%%%s, %%%%%s\\n"\n' % (from_register_1, from_register_0, to_register_1)
    return res

def plain_step(type_name, buf_name, log_n, it, ident=''):
    if log_n <= 0:
        raise Exception("log_n must be positive")
    if it < 0:
        raise Exception("it must be non-negative")
    if it >= log_n:
        raise Exception("it must be smaller than log_n")
    n = 1 << log_n
    res  = ident + "for (int j = 0; j < %d; j += %d) {\n" % (n, 1 << (it + 1))
    res += ident + "  for (int k = 0; k < %d; ++k) {\n" % (1 << it)
    res += ident + "    %s u = %s[j + k];\n" % (type_name, buf_name)
    res += ident + "    %s v = %s[j + k + %d];\n" % (type_name, buf_name, 1 << it)
    res += ident + "    %s[j + k] = u + v;\n" % buf_name
    res += ident + "    %s[j + k + %d] = u - v;\n" % (buf_name, 1 << it)
    res += ident + "  }\n"
    res += ident + "}\n"
    return res

def composite_step(log_n, from_it, to_it, log_w, registers, move_instruction, special_steps, main_step, ident=''):
    if log_n < log_w:
        raise Exception('need at least %d elements' % (1 << log_w))
    num_registers = len(registers)
    if num_registers % 2 == 1:
        raise Exception('odd number of registers: %d' % num_registers)
    num_nontrivial_levels = 0
    if to_it > log_w:
        first_nontrivial = max(from_it, log_w)
        num_nontrivial_levels = to_it - first_nontrivial
        if 1 << num_nontrivial_levels > num_registers / 2:
            raise Exception('not enough registers')
    n = 1 << log_n
    input_registers = []
    output_registers = []
    for i in range(num_registers):
        if i < num_registers / 2:
            input_registers.append(registers[i])
        else:
            output_registers.append(registers[i])
    clobber = ', '.join(['"%%%s"' % x for x in registers])
    if num_nontrivial_levels == 0:
        res  = ident + 'for (int j = 0; j < %d; j += %d) {\n' % (n, 1 << log_w)
        res += ident + '  __asm__ volatile (\n'
        res += ident + '    "%s (%%0), %%%%%s\\n"\n' % (move_instruction, input_registers[0])
        for it in range(from_it, to_it):
            res += special_steps[it](input_registers[0], output_registers, ident + '    ')
        res += ident + '    "%s %%%%%s, (%%0)\\n"\n' % (move_instruction, input_registers[0])
        res += ident + '    :: "r"(buf + j) : %s, "memory"\n' % clobber
        res += ident + '  );\n'
        res += ident + '}\n'
        return res
    res  = ident + 'for (int j = 0; j < %d; j += %d) {\n' % (n, 1 << to_it)
    res += ident + '  for (int k = 0; k < %d; k += %d) {\n' % (1 << (to_it - num_nontrivial_levels), 1 << log_w)
    subcube = []
    for l in range(1 << num_nontrivial_levels):
        subcube.append('j + k + ' + str(l * (1 << (to_it - num_nontrivial_levels))))
    res += ident + '    __asm__ volatile (\n'
    for l in range(1 << num_nontrivial_levels):
        res += ident + '      "%s (%%%d), %%%%%s\\n"\n' % (move_instruction, l, input_registers[l])
    for it in range(from_it, log_w):
        for ii in range(1 << num_nontrivial_levels):
            res += special_steps[it](input_registers[ii], output_registers, ident + '      ')
    for it in range(num_nontrivial_levels):
        for ii in range(0, 1 << num_nontrivial_levels, 1 << (it + 1)):
            for jj in range(1 << it):
                res += main_step(input_registers[ii + jj], input_registers[ii + jj + (1 << it)], output_registers[ii + jj], output_registers[ii + jj + (1 << it)], ident + '      ')
        tmp = input_registers
        input_registers = output_registers
        output_registers = tmp
    for l in range(1 << num_nontrivial_levels):
        res += ident + '      "%s %%%%%s, (%%%d)\\n"\n' % (move_instruction, input_registers[l], l)
    res += ident + '      :: %s : %s, "memory"\n' % (', '.join(['"r"(buf + %s)' % x for x in subcube]), clobber)
    res += ident + '    );\n'
    res += ident + '  }\n'
    res += ident + '}\n'
    return res

def float_avx_composite_step(log_n, from_it, to_it, ident=''):
    return composite_step(log_n, from_it, to_it, 3, ['ymm%d' % x for x in range(16)], 'vmovups', [float_avx_0, float_avx_1, float_avx_2], float_avx_3_etc, ident)

def double_avx_composite_step(log_n, from_it, to_it, ident=''):
    return composite_step(log_n, from_it, to_it, 2, ['ymm%d' % x for x in range(16)], 'vmovupd', [double_avx_0, double_avx_1], double_avx_2_etc, ident)

def float_avx_greedy_merged(log_n):
    res  = "inline void helper_%d(float *buf);\n" % log_n
    res += "inline void helper_%d(float *buf) {\n" % log_n
    if log_n < 6:
        res += float_avx_composite_step(log_n, 0, log_n, '  ')
    else:
        res += float_avx_composite_step(log_n, 0, 6, '  ')
        cur = 6
        while cur < log_n:
            new_end = cur + 3
            res += float_avx_composite_step(log_n, cur, min(new_end, log_n), '  ')
            cur = new_end
    res += "}\n"
    return res

def double_avx_greedy_merged(log_n):
    res  = "inline void double_helper_%d(double *buf);\n" % log_n
    res += "inline void double_helper_%d(double *buf) {\n" % log_n
    if log_n < 5:
        res += double_avx_composite_step(log_n, 0, log_n, '  ')
    else:
        res += double_avx_composite_step(log_n, 0, 5, '  ')
        cur = 5
        while cur < log_n:
            new_end = cur + 3
            res += double_avx_composite_step(log_n, cur, min(new_end, log_n), '  ')
            cur = new_end
    res += "}\n"
    return res

def float_avx_greedy_merged_recursive(log_n):
    res  = "void helper_%d(float *buf, int depth);\n" % log_n
    res += "void helper_%d(float *buf, int depth) {\n" % log_n
    res += "  if (depth == 12) {\n"
    res += float_avx_composite_step(12, 0, 6, '    ')
    res += float_avx_composite_step(12, 6, 9, '    ')
    res += float_avx_composite_step(12, 9, 12, '    ')
    res += "    return;\n"
    res += "  }\n"
    cur = 15
    while cur <= log_n:
        res += "  if (depth == %d) {\n" % cur
        for i in range(8):
            res += "    helper_%d(buf + %d, %d);\n" % (log_n, i * (1 << (cur - 3)), (cur - 3))
        res += float_avx_composite_step(cur, cur - 3, cur, '    ');
        res += "    return;\n"
        res += "  }\n"
        cur += 3
    if log_n % 3 != 0:
        res += "  if (depth == %d) {\n" % log_n
        for i in range(1 << (log_n % 3)):
            res += "    helper_%d(buf + %d, %d);\n" % (log_n, i * (1 << (log_n - log_n % 3)), (log_n - log_n % 3))
        res += float_avx_composite_step(log_n, log_n - log_n % 3, log_n, '    ');
        res += "    return;\n"
        res += "  }\n"
        cur += 3
    res += "}\n"
    return res

def double_avx_greedy_merged_recursive(log_n):
    res  = "void double_helper_%d(double *buf, int depth);\n" % log_n
    res += "void double_helper_%d(double *buf, int depth) {\n" % log_n
    res += "  if (depth == 11) {\n"
    res += double_avx_composite_step(11, 0, 5, '    ')
    res += double_avx_composite_step(11, 5, 8, '    ')
    res += double_avx_composite_step(11, 8, 11, '    ')
    res += "    return;\n"
    res += "  }\n"
    cur = 14
    while cur <= log_n:
        res += "  if (depth == %d) {\n" % cur
        for i in range(8):
            res += "    double_helper_%d(buf + %d, %d);\n" % (log_n, i * (1 << (cur - 3)), (cur - 3))
        res += double_avx_composite_step(cur, cur - 3, cur, '    ');
        res += "    return;\n"
        res += "  }\n"
        cur += 3
    if cur != log_n + 3:
        res += "  if (depth == %d) {\n" % log_n
        for i in range(1 << (log_n - cur + 3)):
            res += "    double_helper_%d(buf + %d, %d);\n" % (log_n, i * (1 << (cur - 3)), (cur - 3))
        res += double_avx_composite_step(log_n, cur - 3, log_n, '    ');
        res += "    return;\n"
        res += "  }\n"
    res += "}\n"
    return res

def float_plain_unmerged(log_n):
    n = 1 << log_n
    res  = "inline void helper_%d(float *buf) {\n" % log_n
    for i in range(0, log_n):
        res += plain_step('float', 'buf', log_n, i, '  ')
    res += "}\n"
    return res

def double_plain_unmerged(log_n):
    n = 1 << log_n
    res  = "inline void double_helper_%d(double *buf) {\n" % log_n
    for i in range(0, log_n):
        res += plain_step('double', 'buf', log_n, i, '  ')
    res += "}\n"
    return res

print '#include "fht.h"\n'

for i in range(1, 31):
    if i < 3:
        print float_plain_unmerged(i)
    elif i <= 12:
        print float_avx_greedy_merged(i)
    else:
        print float_avx_greedy_merged_recursive(i)

for i in range(1, 31):
    if i < 2:
        print double_plain_unmerged(i)
    elif i <= 11:
        print double_avx_greedy_merged(i)
    else:
        print double_avx_greedy_merged_recursive(i)

dispatch  = "void fht_float(float *buf, int log_n) {\n"
dispatch += "  if (log_n == 0) {\n"
dispatch += "  }\n"
for i in range(1, 31):
    if i <= 12:
        dispatch += "  else if (log_n == %d) {\n" % i
        dispatch += '    helper_%d(buf);\n' % i
        dispatch += "  }\n"
    else:
        dispatch += "  else if (log_n == %d) {\n" % i
        dispatch += '    helper_%d(buf, %d);\n' % (i, i)
        dispatch += "  }\n"
dispatch += "  else {\n"
dispatch += "  }\n"
dispatch += "}\n"
dispatch += "void fht_double(double *buf, int log_n) {\n"
dispatch += "  if (log_n == 0) {\n"
dispatch += "  }\n"
for i in range(1, 31):
    if i <= 11:
        dispatch += "  else if (log_n == %d) {\n" % i
        dispatch += '    double_helper_%d(buf);\n' % i
        dispatch += "  }\n"
    else:
        dispatch += "  else if (log_n == %d) {\n" % i
        dispatch += '    double_helper_%d(buf, %d);\n' % (i, i)
        dispatch += "  }\n"
dispatch += "  else {\n"
dispatch += "  }\n"
dispatch += "}\n"
print dispatch
