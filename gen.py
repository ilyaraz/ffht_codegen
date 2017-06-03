import sys

max_log_n = 30

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

def composite_step(buf_name, log_n, from_it, to_it, log_w, registers, move_instruction, special_steps, main_step, ident=''):
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
        res += ident + '    :: "r"(%s + j) : %s, "memory"\n' % (buf_name, clobber)
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
    res += ident + '      :: %s : %s, "memory"\n' % (', '.join(['"r"(%s + %s)' % (buf_name, x) for x in subcube]), clobber)
    res += ident + '    );\n'
    res += ident + '  }\n'
    res += ident + '}\n'
    return res

def float_avx_composite_step(buf_name, log_n, from_it, to_it, ident=''):
    return composite_step(buf_name, log_n, from_it, to_it, 3, ['ymm%d' % x for x in range(16)], 'vmovups', [float_avx_0, float_avx_1, float_avx_2], float_avx_3_etc, ident)

def double_avx_composite_step(buf_name, log_n, from_it, to_it, ident=''):
    return composite_step(buf_name, log_n, from_it, to_it, 2, ['ymm%d' % x for x in range(16)], 'vmovupd', [double_avx_0, double_avx_1], double_avx_2_etc, ident)

def plain_unmerged(type_name, log_n):
    res  = "inline void helper_%s_%d(%s *buf) {\n" % (type_name, log_n, type_name)
    for i in range(log_n):
        res += plain_step(type_name, 'buf', log_n, i, '  ')
    res += "}\n"
    return res

def greedy_merged(type_name, log_n, composite_step):
    try:
        composite_step('buf', log_n, 0, 0)
    except Exception:
        raise Exception('log_n is too small: %d' % log_n)
    res  = 'inline void helper_%s_%d(%s *buf) {\n' % (type_name, log_n, type_name)
    cur_it = 0
    while cur_it < log_n:
        cur_to_it = log_n
        while True:
            try:
                composite_step('buf', log_n, cur_it, cur_to_it)
                break
            except Exception:
                cur_to_it -= 1
                continue
        res += composite_step('buf', log_n, cur_it, cur_to_it, '  ')
        cur_it = cur_to_it
    res += '}\n'
    return res

if __name__ == '__main__':
    res = '#include "fht.h"\n'
    for (type_name, composite_step_generator) in [('float', float_avx_composite_step), ('double', double_avx_composite_step)]:
        for i in range(1, max_log_n + 1):
            try:
                aux = greedy_merged(type_name, i, composite_step_generator)
                res += aux
            except Exception:
                res += plain_unmerged(type_name, i)
        res += 'int fht_%s(%s *buf, int log_n) {\n' % (type_name, type_name)
        for i in range(1, max_log_n + 1):
            res += '  if (log_n == %d) {\n' % i
            res += '    helper_%s_%d(buf);\n' % (type_name, i)
            res += '    return 0;\n'
            res += '  }\n'
        res += '  return 1;\n'
        res += '}\n'
    print res,
