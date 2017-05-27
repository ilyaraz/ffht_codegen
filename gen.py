def generate_step(log_n, it, regime):
    if log_n <= 0:
        raise Exception("log_n must be positive")
    if it < 0:
        raise Exception("it must be non-negative")
    if it >= log_n:
        raise Exception("it must be smaller than log_n")
    if regime != "naive" and regime != "avx":
        raise Exception("not supported regime")
    if regime == "avx" and log_n < 3:
        raise Exception("avx regime needs at least 8 elements")
    n = 1 << log_n
    if regime == "naive":
        res  = "  for (int j = 0; j < %d; j += %d) {\n" % (n, 1 << (it + 1))
        res += "    for (int k = 0; k < %d; ++k) {\n" % (1 << it)
        res += "      float u = buf[j + k];\n"
        res += "      float v = buf[j + k + %d];\n" % (1 << it)
        res += "      buf[j + k] = u + v;\n"
        res += "      buf[j + k + %d] = u - v;\n" % (1 << it)
        res += "    }\n"
        res += "  }\n"
        return res
    if regime == "avx":
        if it == 0:
            res  = "  for (int j = 0; j < %d; j += 8) {\n" % n
            res += "    __m256 A = _mm256_load_ps(buf + j);\n"
            res += "    __m256 B = _mm256_permute_ps(A, (2 << 4) | (2 << 6));\n"
            res += "    __m256 C = _mm256_permute_ps(A, 1 | (1 << 2) | (3 << 4) | (3 << 6));\n"
            res += "    __m256 D = _mm256_sub_ps(ZERO, C);\n"
            res += "    __m256 E = _mm256_addsub_ps(B, D);\n"
            res += "    _mm256_store_ps(buf + j, E);\n"
            res += "  }\n"
            return res
        if it == 1:
            res  = "  for (int j = 0; j < %d; j += 8) {\n" % n
            res += "    __m256 E = _mm256_load_ps(buf + j);\n"
            res += "    __m256 A = _mm256_permute_ps(E, (1 << 2) | (1 << 6));\n"
            res += "    __m256 B = _mm256_permute_ps(E, 2 | (3 << 2) | (2 << 4) | (3 << 6));\n"
            res += "    __m256 C = _mm256_sub_ps(ZERO, B);\n"
            res += "    __m256 D = _mm256_blend_ps(B, C, (1 << 2) | (1 << 3) | (1 << 6) | (1 << 7));\n"
            res += "    E = _mm256_add_ps(A, D);\n"
            res += "    _mm256_store_ps(buf + j, E);\n"
            res += "  }\n"
            return res
        if it == 2:
            res  = "  for (int j = 0; j < %d; j += 8) {\n" % n
            res += "    __m256 E = _mm256_load_ps(buf + j);\n"
            res += "    __m256 B = _mm256_sub_ps(ZERO, E);\n"
            res += "    __m256 C = _mm256_permute2f128_ps(E, E, 0);\n"
            res += "    __m256 D = _mm256_permute2f128_ps(E, B, 1 | (3 << 4));\n"
            res += "    E = _mm256_add_ps(C, D);\n"
            res += "    _mm256_store_ps(buf + j, E);\n"
            res += "  }\n"
            return res
        res  = "  for (int j = 0; j < %d; j += %d) {\n" % (n, 1 << (it + 1))
        res += "    for (int k = 0; k < %d; k += 8) {\n" % (1 << it)
        res += "      __m256 uu = _mm256_load_ps(buf + j + k);\n"
        res += "      __m256 vv = _mm256_load_ps(buf + j + k + %d);\n" % (1 << it)
        res += "      _mm256_store_ps(buf + j + k, _mm256_add_ps(uu, vv));\n"
        res += "      _mm256_store_ps(buf + j + k + %d, _mm256_sub_ps(uu, vv));\n" % (1 << it)
        res += "    }\n"
        res += "  }\n"
        return res
    raise Exception("not supported regime")

def generate_steps(log_n, from_it, to_it, regime):
    if log_n <= 0:
        raise Exception("log_n must be positive")
    if from_it < 0:
        raise Exception("from_it must be non-negative")
    if from_it >= to_it:
        raise Exception("from_it must be smaller than to_it")
    if to_it > log_n:
        raise Exception("to_it must be at most log_n")
    if regime != "naive" and regime != "avx":
        raise Exception("invalid regime")
    n = 1 << log_n
    res  = "inline void steps_%d_%d_%d(float *buf) {\n" % (log_n, from_it, to_it)
    if regime == "avx":
        res += "  __m256 ZERO = _mm256_set_ps(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);\n"
    for i in range(from_it, to_it):
        res += generate_step(log_n, i, regime)
    res += "}\n"
    return res

for i in range(1, 31):
    mode = "avx"
    if i < 3:
        mode = "naive"
    print generate_steps(i, 0, i, mode)

dispatch  = "void fht(float *buf, int log_n) {\n"
dispatch += "  if (log_n == 0) {\n"
dispatch += "  }\n"
for i in range(1, 31):
    dispatch += "  else if (log_n == %d) {\n" % i
    dispatch += "    steps_%d_0_%d(buf);\n" % (i, i)
    dispatch += "  }\n"
dispatch += "  else {\n"
dispatch += "  }\n"
dispatch += "}\n"
print dispatch
