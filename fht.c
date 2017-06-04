#include "fht.h"
inline void helper_float_1(float *buf);
inline void helper_float_1(float *buf) {
  for (int j = 0; j < 2; j += 2) {
    for (int k = 0; k < 1; ++k) {
      float u = buf[j + k];
      float v = buf[j + k + 1];
      buf[j + k] = u + v;
      buf[j + k + 1] = u - v;
    }
  }
}
inline void helper_float_2(float *buf);
inline void helper_float_2(float *buf) {
  for (int j = 0; j < 4; j += 2) {
    for (int k = 0; k < 1; ++k) {
      float u = buf[j + k];
      float v = buf[j + k + 1];
      buf[j + k] = u + v;
      buf[j + k + 1] = u - v;
    }
  }
  for (int j = 0; j < 4; j += 4) {
    for (int k = 0; k < 2; ++k) {
      float u = buf[j + k];
      float v = buf[j + k + 2];
      buf[j + k] = u + v;
      buf[j + k + 2] = u - v;
    }
  }
}
void helper_float_3_recursive(float *buf, int depth);
void helper_float_3_recursive(float *buf, int depth) {
  if (depth == 3) {
    for (int j = 0; j < 8; j += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vpermilps $160, %%ymm0, %%ymm8\n"
        "vpermilps $245, %%ymm0, %%ymm9\n"
        "vxorps %%ymm10, %%ymm10, %%ymm10\n"
        "vsubps %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
        "vpermilps $68, %%ymm0, %%ymm8\n"
        "vpermilps $238, %%ymm0, %%ymm9\n"
        "vxorps %%ymm10, %%ymm10, %%ymm10\n"
        "vsubps %%ymm9, %%ymm10, %%ymm11\n"
        "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
        "vaddps %%ymm8, %%ymm12, %%ymm0\n"
        "vxorps %%ymm8, %%ymm8, %%ymm8\n"
        "vsubps %%ymm0, %%ymm8, %%ymm9\n"
        "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
        "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
        "vaddps %%ymm10, %%ymm11, %%ymm0\n"
        "vmovups %%ymm0, (%0)\n"
        :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
      );
    }
    return;
  }
}
void helper_float_3(float *buf);
void helper_float_3(float *buf) {
  helper_float_3_recursive(buf, 3);
}
void helper_float_4_recursive(float *buf, int depth);
void helper_float_4_recursive(float *buf, int depth) {
  if (depth == 4) {
    for (int j = 0; j < 16; j += 16) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_4(float *buf);
void helper_float_4(float *buf) {
  helper_float_4_recursive(buf, 4);
}
void helper_float_5_recursive(float *buf, int depth);
void helper_float_5_recursive(float *buf, int depth) {
  if (depth == 5) {
    for (int j = 0; j < 32; j += 32) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vmovups %%ymm0, (%0)\n"
          "vmovups %%ymm1, (%1)\n"
          "vmovups %%ymm2, (%2)\n"
          "vmovups %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_5(float *buf);
void helper_float_5(float *buf) {
  helper_float_5_recursive(buf, 5);
}
void helper_float_6_recursive(float *buf, int depth);
void helper_float_6_recursive(float *buf, int depth) {
  if (depth == 6) {
    for (int j = 0; j < 64; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_6(float *buf);
void helper_float_6(float *buf) {
  helper_float_6_recursive(buf, 6);
}
void helper_float_7_recursive(float *buf, int depth);
void helper_float_7_recursive(float *buf, int depth) {
  if (depth == 6) {
    for (int j = 0; j < 64; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 7) {
    helper_float_7_recursive(buf + 0, 6);
    helper_float_7_recursive(buf + 64, 6);
    for (int j = 0; j < 128; j += 128) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_7(float *buf);
void helper_float_7(float *buf) {
  helper_float_7_recursive(buf, 7);
}
inline void helper_float_8(float *buf);
inline void helper_float_8(float *buf) {
  for (int j = 0; j < 256; j += 64) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vmovups (%2), %%ymm2\n"
        "vmovups (%3), %%ymm3\n"
        "vmovups (%4), %%ymm4\n"
        "vmovups (%5), %%ymm5\n"
        "vmovups (%6), %%ymm6\n"
        "vmovups (%7), %%ymm7\n"
        "vpermilps $160, %%ymm0, %%ymm8\n"
        "vpermilps $245, %%ymm0, %%ymm9\n"
        "vxorps %%ymm10, %%ymm10, %%ymm10\n"
        "vsubps %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
        "vpermilps $160, %%ymm1, %%ymm8\n"
        "vpermilps $245, %%ymm1, %%ymm9\n"
        "vxorps %%ymm10, %%ymm10, %%ymm10\n"
        "vsubps %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
        "vpermilps $160, %%ymm2, %%ymm8\n"
        "vpermilps $245, %%ymm2, %%ymm9\n"
        "vxorps %%ymm10, %%ymm10, %%ymm10\n"
        "vsubps %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
        "vpermilps $160, %%ymm3, %%ymm8\n"
        "vpermilps $245, %%ymm3, %%ymm9\n"
        "vxorps %%ymm10, %%ymm10, %%ymm10\n"
        "vsubps %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
        "vpermilps $160, %%ymm4, %%ymm8\n"
        "vpermilps $245, %%ymm4, %%ymm9\n"
        "vxorps %%ymm10, %%ymm10, %%ymm10\n"
        "vsubps %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
        "vpermilps $160, %%ymm5, %%ymm8\n"
        "vpermilps $245, %%ymm5, %%ymm9\n"
        "vxorps %%ymm10, %%ymm10, %%ymm10\n"
        "vsubps %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
        "vpermilps $160, %%ymm6, %%ymm8\n"
        "vpermilps $245, %%ymm6, %%ymm9\n"
        "vxorps %%ymm10, %%ymm10, %%ymm10\n"
        "vsubps %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
        "vpermilps $160, %%ymm7, %%ymm8\n"
        "vpermilps $245, %%ymm7, %%ymm9\n"
        "vxorps %%ymm10, %%ymm10, %%ymm10\n"
        "vsubps %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
        "vpermilps $68, %%ymm0, %%ymm8\n"
        "vpermilps $238, %%ymm0, %%ymm9\n"
        "vxorps %%ymm10, %%ymm10, %%ymm10\n"
        "vsubps %%ymm9, %%ymm10, %%ymm11\n"
        "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
        "vaddps %%ymm8, %%ymm12, %%ymm0\n"
        "vpermilps $68, %%ymm1, %%ymm8\n"
        "vpermilps $238, %%ymm1, %%ymm9\n"
        "vxorps %%ymm10, %%ymm10, %%ymm10\n"
        "vsubps %%ymm9, %%ymm10, %%ymm11\n"
        "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
        "vaddps %%ymm8, %%ymm12, %%ymm1\n"
        "vpermilps $68, %%ymm2, %%ymm8\n"
        "vpermilps $238, %%ymm2, %%ymm9\n"
        "vxorps %%ymm10, %%ymm10, %%ymm10\n"
        "vsubps %%ymm9, %%ymm10, %%ymm11\n"
        "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
        "vaddps %%ymm8, %%ymm12, %%ymm2\n"
        "vpermilps $68, %%ymm3, %%ymm8\n"
        "vpermilps $238, %%ymm3, %%ymm9\n"
        "vxorps %%ymm10, %%ymm10, %%ymm10\n"
        "vsubps %%ymm9, %%ymm10, %%ymm11\n"
        "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
        "vaddps %%ymm8, %%ymm12, %%ymm3\n"
        "vpermilps $68, %%ymm4, %%ymm8\n"
        "vpermilps $238, %%ymm4, %%ymm9\n"
        "vxorps %%ymm10, %%ymm10, %%ymm10\n"
        "vsubps %%ymm9, %%ymm10, %%ymm11\n"
        "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
        "vaddps %%ymm8, %%ymm12, %%ymm4\n"
        "vpermilps $68, %%ymm5, %%ymm8\n"
        "vpermilps $238, %%ymm5, %%ymm9\n"
        "vxorps %%ymm10, %%ymm10, %%ymm10\n"
        "vsubps %%ymm9, %%ymm10, %%ymm11\n"
        "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
        "vaddps %%ymm8, %%ymm12, %%ymm5\n"
        "vpermilps $68, %%ymm6, %%ymm8\n"
        "vpermilps $238, %%ymm6, %%ymm9\n"
        "vxorps %%ymm10, %%ymm10, %%ymm10\n"
        "vsubps %%ymm9, %%ymm10, %%ymm11\n"
        "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
        "vaddps %%ymm8, %%ymm12, %%ymm6\n"
        "vpermilps $68, %%ymm7, %%ymm8\n"
        "vpermilps $238, %%ymm7, %%ymm9\n"
        "vxorps %%ymm10, %%ymm10, %%ymm10\n"
        "vsubps %%ymm9, %%ymm10, %%ymm11\n"
        "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
        "vaddps %%ymm8, %%ymm12, %%ymm7\n"
        "vxorps %%ymm8, %%ymm8, %%ymm8\n"
        "vsubps %%ymm0, %%ymm8, %%ymm9\n"
        "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
        "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
        "vaddps %%ymm10, %%ymm11, %%ymm0\n"
        "vxorps %%ymm8, %%ymm8, %%ymm8\n"
        "vsubps %%ymm1, %%ymm8, %%ymm9\n"
        "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
        "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
        "vaddps %%ymm10, %%ymm11, %%ymm1\n"
        "vxorps %%ymm8, %%ymm8, %%ymm8\n"
        "vsubps %%ymm2, %%ymm8, %%ymm9\n"
        "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
        "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
        "vaddps %%ymm10, %%ymm11, %%ymm2\n"
        "vxorps %%ymm8, %%ymm8, %%ymm8\n"
        "vsubps %%ymm3, %%ymm8, %%ymm9\n"
        "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
        "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
        "vaddps %%ymm10, %%ymm11, %%ymm3\n"
        "vxorps %%ymm8, %%ymm8, %%ymm8\n"
        "vsubps %%ymm4, %%ymm8, %%ymm9\n"
        "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
        "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
        "vaddps %%ymm10, %%ymm11, %%ymm4\n"
        "vxorps %%ymm8, %%ymm8, %%ymm8\n"
        "vsubps %%ymm5, %%ymm8, %%ymm9\n"
        "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
        "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
        "vaddps %%ymm10, %%ymm11, %%ymm5\n"
        "vxorps %%ymm8, %%ymm8, %%ymm8\n"
        "vsubps %%ymm6, %%ymm8, %%ymm9\n"
        "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
        "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
        "vaddps %%ymm10, %%ymm11, %%ymm6\n"
        "vxorps %%ymm8, %%ymm8, %%ymm8\n"
        "vsubps %%ymm7, %%ymm8, %%ymm9\n"
        "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
        "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
        "vaddps %%ymm10, %%ymm11, %%ymm7\n"
        "vaddps %%ymm1, %%ymm0, %%ymm8\n"
        "vsubps %%ymm1, %%ymm0, %%ymm9\n"
        "vaddps %%ymm3, %%ymm2, %%ymm10\n"
        "vsubps %%ymm3, %%ymm2, %%ymm11\n"
        "vaddps %%ymm5, %%ymm4, %%ymm12\n"
        "vsubps %%ymm5, %%ymm4, %%ymm13\n"
        "vaddps %%ymm7, %%ymm6, %%ymm14\n"
        "vsubps %%ymm7, %%ymm6, %%ymm15\n"
        "vaddps %%ymm10, %%ymm8, %%ymm0\n"
        "vsubps %%ymm10, %%ymm8, %%ymm2\n"
        "vaddps %%ymm11, %%ymm9, %%ymm1\n"
        "vsubps %%ymm11, %%ymm9, %%ymm3\n"
        "vaddps %%ymm14, %%ymm12, %%ymm4\n"
        "vsubps %%ymm14, %%ymm12, %%ymm6\n"
        "vaddps %%ymm15, %%ymm13, %%ymm5\n"
        "vsubps %%ymm15, %%ymm13, %%ymm7\n"
        "vaddps %%ymm4, %%ymm0, %%ymm8\n"
        "vsubps %%ymm4, %%ymm0, %%ymm12\n"
        "vaddps %%ymm5, %%ymm1, %%ymm9\n"
        "vsubps %%ymm5, %%ymm1, %%ymm13\n"
        "vaddps %%ymm6, %%ymm2, %%ymm10\n"
        "vsubps %%ymm6, %%ymm2, %%ymm14\n"
        "vaddps %%ymm7, %%ymm3, %%ymm11\n"
        "vsubps %%ymm7, %%ymm3, %%ymm15\n"
        "vmovups %%ymm8, (%0)\n"
        "vmovups %%ymm9, (%1)\n"
        "vmovups %%ymm10, (%2)\n"
        "vmovups %%ymm11, (%3)\n"
        "vmovups %%ymm12, (%4)\n"
        "vmovups %%ymm13, (%5)\n"
        "vmovups %%ymm14, (%6)\n"
        "vmovups %%ymm15, (%7)\n"
        :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
      );
    }
  }
  for (int j = 0; j < 256; j += 256) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vmovups (%2), %%ymm2\n"
        "vmovups (%3), %%ymm3\n"
        "vaddps %%ymm1, %%ymm0, %%ymm8\n"
        "vsubps %%ymm1, %%ymm0, %%ymm9\n"
        "vaddps %%ymm3, %%ymm2, %%ymm10\n"
        "vsubps %%ymm3, %%ymm2, %%ymm11\n"
        "vaddps %%ymm10, %%ymm8, %%ymm0\n"
        "vsubps %%ymm10, %%ymm8, %%ymm2\n"
        "vaddps %%ymm11, %%ymm9, %%ymm1\n"
        "vsubps %%ymm11, %%ymm9, %%ymm3\n"
        "vmovups %%ymm0, (%0)\n"
        "vmovups %%ymm1, (%1)\n"
        "vmovups %%ymm2, (%2)\n"
        "vmovups %%ymm3, (%3)\n"
        :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
      );
    }
  }
}
void helper_float_9_recursive(float *buf, int depth);
void helper_float_9_recursive(float *buf, int depth) {
  if (depth == 6) {
    for (int j = 0; j < 64; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 9) {
    helper_float_9_recursive(buf + 0, 6);
    helper_float_9_recursive(buf + 64, 6);
    helper_float_9_recursive(buf + 128, 6);
    helper_float_9_recursive(buf + 192, 6);
    helper_float_9_recursive(buf + 256, 6);
    helper_float_9_recursive(buf + 320, 6);
    helper_float_9_recursive(buf + 384, 6);
    helper_float_9_recursive(buf + 448, 6);
    for (int j = 0; j < 512; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_9(float *buf);
void helper_float_9(float *buf) {
  helper_float_9_recursive(buf, 9);
}
void helper_float_10_recursive(float *buf, int depth);
void helper_float_10_recursive(float *buf, int depth) {
  if (depth == 10) {
    for (int j = 0; j < 1024; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 1024; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 1024; j += 1024) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_10(float *buf);
void helper_float_10(float *buf) {
  helper_float_10_recursive(buf, 10);
}
void helper_float_11_recursive(float *buf, int depth);
void helper_float_11_recursive(float *buf, int depth) {
  if (depth == 11) {
    for (int j = 0; j < 2048; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 2048) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vmovups %%ymm0, (%0)\n"
          "vmovups %%ymm1, (%1)\n"
          "vmovups %%ymm2, (%2)\n"
          "vmovups %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_11(float *buf);
void helper_float_11(float *buf) {
  helper_float_11_recursive(buf, 11);
}
void helper_float_12_recursive(float *buf, int depth);
void helper_float_12_recursive(float *buf, int depth) {
  if (depth == 12) {
    for (int j = 0; j < 4096; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 4096) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_12(float *buf);
void helper_float_12(float *buf) {
  helper_float_12_recursive(buf, 12);
}
void helper_float_13_recursive(float *buf, int depth);
void helper_float_13_recursive(float *buf, int depth) {
  if (depth == 11) {
    for (int j = 0; j < 2048; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 2048) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vmovups %%ymm0, (%0)\n"
          "vmovups %%ymm1, (%1)\n"
          "vmovups %%ymm2, (%2)\n"
          "vmovups %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 13) {
    helper_float_13_recursive(buf + 0, 11);
    helper_float_13_recursive(buf + 2048, 11);
    helper_float_13_recursive(buf + 4096, 11);
    helper_float_13_recursive(buf + 6144, 11);
    for (int j = 0; j < 8192; j += 8192) {
      for (int k = 0; k < 2048; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vmovups %%ymm0, (%0)\n"
          "vmovups %%ymm1, (%1)\n"
          "vmovups %%ymm2, (%2)\n"
          "vmovups %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2048), "r"(buf + j + k + 4096), "r"(buf + j + k + 6144) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_13(float *buf);
void helper_float_13(float *buf) {
  helper_float_13_recursive(buf, 13);
}
void helper_float_14_recursive(float *buf, int depth);
void helper_float_14_recursive(float *buf, int depth) {
  if (depth == 12) {
    for (int j = 0; j < 4096; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 4096) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 14) {
    helper_float_14_recursive(buf + 0, 12);
    helper_float_14_recursive(buf + 4096, 12);
    helper_float_14_recursive(buf + 8192, 12);
    helper_float_14_recursive(buf + 12288, 12);
    for (int j = 0; j < 16384; j += 16384) {
      for (int k = 0; k < 4096; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vmovups %%ymm0, (%0)\n"
          "vmovups %%ymm1, (%1)\n"
          "vmovups %%ymm2, (%2)\n"
          "vmovups %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096), "r"(buf + j + k + 8192), "r"(buf + j + k + 12288) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_14(float *buf);
void helper_float_14(float *buf) {
  helper_float_14_recursive(buf, 14);
}
void helper_float_15_recursive(float *buf, int depth);
void helper_float_15_recursive(float *buf, int depth) {
  if (depth == 13) {
    for (int j = 0; j < 8192; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 8192; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 8192; j += 4096) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 8192; j += 8192) {
      for (int k = 0; k < 4096; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 15) {
    helper_float_15_recursive(buf + 0, 13);
    helper_float_15_recursive(buf + 8192, 13);
    helper_float_15_recursive(buf + 16384, 13);
    helper_float_15_recursive(buf + 24576, 13);
    for (int j = 0; j < 32768; j += 32768) {
      for (int k = 0; k < 8192; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vmovups %%ymm0, (%0)\n"
          "vmovups %%ymm1, (%1)\n"
          "vmovups %%ymm2, (%2)\n"
          "vmovups %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8192), "r"(buf + j + k + 16384), "r"(buf + j + k + 24576) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_15(float *buf);
void helper_float_15(float *buf) {
  helper_float_15_recursive(buf, 15);
}
void helper_float_16_recursive(float *buf, int depth);
void helper_float_16_recursive(float *buf, int depth) {
  if (depth == 13) {
    for (int j = 0; j < 8192; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 8192; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 8192; j += 4096) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 8192; j += 8192) {
      for (int k = 0; k < 4096; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 16) {
    helper_float_16_recursive(buf + 0, 13);
    helper_float_16_recursive(buf + 8192, 13);
    helper_float_16_recursive(buf + 16384, 13);
    helper_float_16_recursive(buf + 24576, 13);
    helper_float_16_recursive(buf + 32768, 13);
    helper_float_16_recursive(buf + 40960, 13);
    helper_float_16_recursive(buf + 49152, 13);
    helper_float_16_recursive(buf + 57344, 13);
    for (int j = 0; j < 65536; j += 65536) {
      for (int k = 0; k < 8192; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8192), "r"(buf + j + k + 16384), "r"(buf + j + k + 24576), "r"(buf + j + k + 32768), "r"(buf + j + k + 40960), "r"(buf + j + k + 49152), "r"(buf + j + k + 57344) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_16(float *buf);
void helper_float_16(float *buf) {
  helper_float_16_recursive(buf, 16);
}
void helper_float_17_recursive(float *buf, int depth);
void helper_float_17_recursive(float *buf, int depth) {
  if (depth == 12) {
    for (int j = 0; j < 4096; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 4096) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 15) {
    helper_float_17_recursive(buf + 0, 12);
    helper_float_17_recursive(buf + 4096, 12);
    helper_float_17_recursive(buf + 8192, 12);
    helper_float_17_recursive(buf + 12288, 12);
    helper_float_17_recursive(buf + 16384, 12);
    helper_float_17_recursive(buf + 20480, 12);
    helper_float_17_recursive(buf + 24576, 12);
    helper_float_17_recursive(buf + 28672, 12);
    for (int j = 0; j < 32768; j += 32768) {
      for (int k = 0; k < 4096; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096), "r"(buf + j + k + 8192), "r"(buf + j + k + 12288), "r"(buf + j + k + 16384), "r"(buf + j + k + 20480), "r"(buf + j + k + 24576), "r"(buf + j + k + 28672) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 17) {
    helper_float_17_recursive(buf + 0, 15);
    helper_float_17_recursive(buf + 32768, 15);
    helper_float_17_recursive(buf + 65536, 15);
    helper_float_17_recursive(buf + 98304, 15);
    for (int j = 0; j < 131072; j += 131072) {
      for (int k = 0; k < 32768; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vmovups %%ymm0, (%0)\n"
          "vmovups %%ymm1, (%1)\n"
          "vmovups %%ymm2, (%2)\n"
          "vmovups %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32768), "r"(buf + j + k + 65536), "r"(buf + j + k + 98304) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_17(float *buf);
void helper_float_17(float *buf) {
  helper_float_17_recursive(buf, 17);
}
void helper_float_18_recursive(float *buf, int depth);
void helper_float_18_recursive(float *buf, int depth) {
  if (depth == 12) {
    for (int j = 0; j < 4096; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 4096) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 15) {
    helper_float_18_recursive(buf + 0, 12);
    helper_float_18_recursive(buf + 4096, 12);
    helper_float_18_recursive(buf + 8192, 12);
    helper_float_18_recursive(buf + 12288, 12);
    helper_float_18_recursive(buf + 16384, 12);
    helper_float_18_recursive(buf + 20480, 12);
    helper_float_18_recursive(buf + 24576, 12);
    helper_float_18_recursive(buf + 28672, 12);
    for (int j = 0; j < 32768; j += 32768) {
      for (int k = 0; k < 4096; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096), "r"(buf + j + k + 8192), "r"(buf + j + k + 12288), "r"(buf + j + k + 16384), "r"(buf + j + k + 20480), "r"(buf + j + k + 24576), "r"(buf + j + k + 28672) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 18) {
    helper_float_18_recursive(buf + 0, 15);
    helper_float_18_recursive(buf + 32768, 15);
    helper_float_18_recursive(buf + 65536, 15);
    helper_float_18_recursive(buf + 98304, 15);
    helper_float_18_recursive(buf + 131072, 15);
    helper_float_18_recursive(buf + 163840, 15);
    helper_float_18_recursive(buf + 196608, 15);
    helper_float_18_recursive(buf + 229376, 15);
    for (int j = 0; j < 262144; j += 262144) {
      for (int k = 0; k < 32768; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32768), "r"(buf + j + k + 65536), "r"(buf + j + k + 98304), "r"(buf + j + k + 131072), "r"(buf + j + k + 163840), "r"(buf + j + k + 196608), "r"(buf + j + k + 229376) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_18(float *buf);
void helper_float_18(float *buf) {
  helper_float_18_recursive(buf, 18);
}
void helper_float_19_recursive(float *buf, int depth);
void helper_float_19_recursive(float *buf, int depth) {
  if (depth == 13) {
    for (int j = 0; j < 8192; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 8192; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 8192; j += 4096) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 8192; j += 8192) {
      for (int k = 0; k < 4096; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 16) {
    helper_float_19_recursive(buf + 0, 13);
    helper_float_19_recursive(buf + 8192, 13);
    helper_float_19_recursive(buf + 16384, 13);
    helper_float_19_recursive(buf + 24576, 13);
    helper_float_19_recursive(buf + 32768, 13);
    helper_float_19_recursive(buf + 40960, 13);
    helper_float_19_recursive(buf + 49152, 13);
    helper_float_19_recursive(buf + 57344, 13);
    for (int j = 0; j < 65536; j += 65536) {
      for (int k = 0; k < 8192; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8192), "r"(buf + j + k + 16384), "r"(buf + j + k + 24576), "r"(buf + j + k + 32768), "r"(buf + j + k + 40960), "r"(buf + j + k + 49152), "r"(buf + j + k + 57344) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 19) {
    helper_float_19_recursive(buf + 0, 16);
    helper_float_19_recursive(buf + 65536, 16);
    helper_float_19_recursive(buf + 131072, 16);
    helper_float_19_recursive(buf + 196608, 16);
    helper_float_19_recursive(buf + 262144, 16);
    helper_float_19_recursive(buf + 327680, 16);
    helper_float_19_recursive(buf + 393216, 16);
    helper_float_19_recursive(buf + 458752, 16);
    for (int j = 0; j < 524288; j += 524288) {
      for (int k = 0; k < 65536; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 65536), "r"(buf + j + k + 131072), "r"(buf + j + k + 196608), "r"(buf + j + k + 262144), "r"(buf + j + k + 327680), "r"(buf + j + k + 393216), "r"(buf + j + k + 458752) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_19(float *buf);
void helper_float_19(float *buf) {
  helper_float_19_recursive(buf, 19);
}
void helper_float_20_recursive(float *buf, int depth);
void helper_float_20_recursive(float *buf, int depth) {
  if (depth == 12) {
    for (int j = 0; j < 4096; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 4096) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 15) {
    helper_float_20_recursive(buf + 0, 12);
    helper_float_20_recursive(buf + 4096, 12);
    helper_float_20_recursive(buf + 8192, 12);
    helper_float_20_recursive(buf + 12288, 12);
    helper_float_20_recursive(buf + 16384, 12);
    helper_float_20_recursive(buf + 20480, 12);
    helper_float_20_recursive(buf + 24576, 12);
    helper_float_20_recursive(buf + 28672, 12);
    for (int j = 0; j < 32768; j += 32768) {
      for (int k = 0; k < 4096; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096), "r"(buf + j + k + 8192), "r"(buf + j + k + 12288), "r"(buf + j + k + 16384), "r"(buf + j + k + 20480), "r"(buf + j + k + 24576), "r"(buf + j + k + 28672) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 18) {
    helper_float_20_recursive(buf + 0, 15);
    helper_float_20_recursive(buf + 32768, 15);
    helper_float_20_recursive(buf + 65536, 15);
    helper_float_20_recursive(buf + 98304, 15);
    helper_float_20_recursive(buf + 131072, 15);
    helper_float_20_recursive(buf + 163840, 15);
    helper_float_20_recursive(buf + 196608, 15);
    helper_float_20_recursive(buf + 229376, 15);
    for (int j = 0; j < 262144; j += 262144) {
      for (int k = 0; k < 32768; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32768), "r"(buf + j + k + 65536), "r"(buf + j + k + 98304), "r"(buf + j + k + 131072), "r"(buf + j + k + 163840), "r"(buf + j + k + 196608), "r"(buf + j + k + 229376) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 20) {
    helper_float_20_recursive(buf + 0, 18);
    helper_float_20_recursive(buf + 262144, 18);
    helper_float_20_recursive(buf + 524288, 18);
    helper_float_20_recursive(buf + 786432, 18);
    for (int j = 0; j < 1048576; j += 1048576) {
      for (int k = 0; k < 262144; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vmovups %%ymm0, (%0)\n"
          "vmovups %%ymm1, (%1)\n"
          "vmovups %%ymm2, (%2)\n"
          "vmovups %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 262144), "r"(buf + j + k + 524288), "r"(buf + j + k + 786432) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_20(float *buf);
void helper_float_20(float *buf) {
  helper_float_20_recursive(buf, 20);
}
void helper_float_21_recursive(float *buf, int depth);
void helper_float_21_recursive(float *buf, int depth) {
  if (depth == 13) {
    for (int j = 0; j < 8192; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 8192; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 8192; j += 4096) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 8192; j += 8192) {
      for (int k = 0; k < 4096; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 16) {
    helper_float_21_recursive(buf + 0, 13);
    helper_float_21_recursive(buf + 8192, 13);
    helper_float_21_recursive(buf + 16384, 13);
    helper_float_21_recursive(buf + 24576, 13);
    helper_float_21_recursive(buf + 32768, 13);
    helper_float_21_recursive(buf + 40960, 13);
    helper_float_21_recursive(buf + 49152, 13);
    helper_float_21_recursive(buf + 57344, 13);
    for (int j = 0; j < 65536; j += 65536) {
      for (int k = 0; k < 8192; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8192), "r"(buf + j + k + 16384), "r"(buf + j + k + 24576), "r"(buf + j + k + 32768), "r"(buf + j + k + 40960), "r"(buf + j + k + 49152), "r"(buf + j + k + 57344) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 19) {
    helper_float_21_recursive(buf + 0, 16);
    helper_float_21_recursive(buf + 65536, 16);
    helper_float_21_recursive(buf + 131072, 16);
    helper_float_21_recursive(buf + 196608, 16);
    helper_float_21_recursive(buf + 262144, 16);
    helper_float_21_recursive(buf + 327680, 16);
    helper_float_21_recursive(buf + 393216, 16);
    helper_float_21_recursive(buf + 458752, 16);
    for (int j = 0; j < 524288; j += 524288) {
      for (int k = 0; k < 65536; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 65536), "r"(buf + j + k + 131072), "r"(buf + j + k + 196608), "r"(buf + j + k + 262144), "r"(buf + j + k + 327680), "r"(buf + j + k + 393216), "r"(buf + j + k + 458752) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 21) {
    helper_float_21_recursive(buf + 0, 19);
    helper_float_21_recursive(buf + 524288, 19);
    helper_float_21_recursive(buf + 1048576, 19);
    helper_float_21_recursive(buf + 1572864, 19);
    for (int j = 0; j < 2097152; j += 2097152) {
      for (int k = 0; k < 524288; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vmovups %%ymm0, (%0)\n"
          "vmovups %%ymm1, (%1)\n"
          "vmovups %%ymm2, (%2)\n"
          "vmovups %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 524288), "r"(buf + j + k + 1048576), "r"(buf + j + k + 1572864) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_21(float *buf);
void helper_float_21(float *buf) {
  helper_float_21_recursive(buf, 21);
}
void helper_float_22_recursive(float *buf, int depth);
void helper_float_22_recursive(float *buf, int depth) {
  if (depth == 11) {
    for (int j = 0; j < 2048; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 2048) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vmovups %%ymm0, (%0)\n"
          "vmovups %%ymm1, (%1)\n"
          "vmovups %%ymm2, (%2)\n"
          "vmovups %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 14) {
    helper_float_22_recursive(buf + 0, 11);
    helper_float_22_recursive(buf + 2048, 11);
    helper_float_22_recursive(buf + 4096, 11);
    helper_float_22_recursive(buf + 6144, 11);
    helper_float_22_recursive(buf + 8192, 11);
    helper_float_22_recursive(buf + 10240, 11);
    helper_float_22_recursive(buf + 12288, 11);
    helper_float_22_recursive(buf + 14336, 11);
    for (int j = 0; j < 16384; j += 16384) {
      for (int k = 0; k < 2048; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2048), "r"(buf + j + k + 4096), "r"(buf + j + k + 6144), "r"(buf + j + k + 8192), "r"(buf + j + k + 10240), "r"(buf + j + k + 12288), "r"(buf + j + k + 14336) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 17) {
    helper_float_22_recursive(buf + 0, 14);
    helper_float_22_recursive(buf + 16384, 14);
    helper_float_22_recursive(buf + 32768, 14);
    helper_float_22_recursive(buf + 49152, 14);
    helper_float_22_recursive(buf + 65536, 14);
    helper_float_22_recursive(buf + 81920, 14);
    helper_float_22_recursive(buf + 98304, 14);
    helper_float_22_recursive(buf + 114688, 14);
    for (int j = 0; j < 131072; j += 131072) {
      for (int k = 0; k < 16384; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 16384), "r"(buf + j + k + 32768), "r"(buf + j + k + 49152), "r"(buf + j + k + 65536), "r"(buf + j + k + 81920), "r"(buf + j + k + 98304), "r"(buf + j + k + 114688) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 20) {
    helper_float_22_recursive(buf + 0, 17);
    helper_float_22_recursive(buf + 131072, 17);
    helper_float_22_recursive(buf + 262144, 17);
    helper_float_22_recursive(buf + 393216, 17);
    helper_float_22_recursive(buf + 524288, 17);
    helper_float_22_recursive(buf + 655360, 17);
    helper_float_22_recursive(buf + 786432, 17);
    helper_float_22_recursive(buf + 917504, 17);
    for (int j = 0; j < 1048576; j += 1048576) {
      for (int k = 0; k < 131072; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 131072), "r"(buf + j + k + 262144), "r"(buf + j + k + 393216), "r"(buf + j + k + 524288), "r"(buf + j + k + 655360), "r"(buf + j + k + 786432), "r"(buf + j + k + 917504) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 22) {
    helper_float_22_recursive(buf + 0, 20);
    helper_float_22_recursive(buf + 1048576, 20);
    helper_float_22_recursive(buf + 2097152, 20);
    helper_float_22_recursive(buf + 3145728, 20);
    for (int j = 0; j < 4194304; j += 4194304) {
      for (int k = 0; k < 1048576; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vmovups %%ymm0, (%0)\n"
          "vmovups %%ymm1, (%1)\n"
          "vmovups %%ymm2, (%2)\n"
          "vmovups %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 1048576), "r"(buf + j + k + 2097152), "r"(buf + j + k + 3145728) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_22(float *buf);
void helper_float_22(float *buf) {
  helper_float_22_recursive(buf, 22);
}
void helper_float_23_recursive(float *buf, int depth);
void helper_float_23_recursive(float *buf, int depth) {
  if (depth == 12) {
    for (int j = 0; j < 4096; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 4096) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 15) {
    helper_float_23_recursive(buf + 0, 12);
    helper_float_23_recursive(buf + 4096, 12);
    helper_float_23_recursive(buf + 8192, 12);
    helper_float_23_recursive(buf + 12288, 12);
    helper_float_23_recursive(buf + 16384, 12);
    helper_float_23_recursive(buf + 20480, 12);
    helper_float_23_recursive(buf + 24576, 12);
    helper_float_23_recursive(buf + 28672, 12);
    for (int j = 0; j < 32768; j += 32768) {
      for (int k = 0; k < 4096; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096), "r"(buf + j + k + 8192), "r"(buf + j + k + 12288), "r"(buf + j + k + 16384), "r"(buf + j + k + 20480), "r"(buf + j + k + 24576), "r"(buf + j + k + 28672) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 18) {
    helper_float_23_recursive(buf + 0, 15);
    helper_float_23_recursive(buf + 32768, 15);
    helper_float_23_recursive(buf + 65536, 15);
    helper_float_23_recursive(buf + 98304, 15);
    helper_float_23_recursive(buf + 131072, 15);
    helper_float_23_recursive(buf + 163840, 15);
    helper_float_23_recursive(buf + 196608, 15);
    helper_float_23_recursive(buf + 229376, 15);
    for (int j = 0; j < 262144; j += 262144) {
      for (int k = 0; k < 32768; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32768), "r"(buf + j + k + 65536), "r"(buf + j + k + 98304), "r"(buf + j + k + 131072), "r"(buf + j + k + 163840), "r"(buf + j + k + 196608), "r"(buf + j + k + 229376) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 21) {
    helper_float_23_recursive(buf + 0, 18);
    helper_float_23_recursive(buf + 262144, 18);
    helper_float_23_recursive(buf + 524288, 18);
    helper_float_23_recursive(buf + 786432, 18);
    helper_float_23_recursive(buf + 1048576, 18);
    helper_float_23_recursive(buf + 1310720, 18);
    helper_float_23_recursive(buf + 1572864, 18);
    helper_float_23_recursive(buf + 1835008, 18);
    for (int j = 0; j < 2097152; j += 2097152) {
      for (int k = 0; k < 262144; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 262144), "r"(buf + j + k + 524288), "r"(buf + j + k + 786432), "r"(buf + j + k + 1048576), "r"(buf + j + k + 1310720), "r"(buf + j + k + 1572864), "r"(buf + j + k + 1835008) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 23) {
    helper_float_23_recursive(buf + 0, 21);
    helper_float_23_recursive(buf + 2097152, 21);
    helper_float_23_recursive(buf + 4194304, 21);
    helper_float_23_recursive(buf + 6291456, 21);
    for (int j = 0; j < 8388608; j += 8388608) {
      for (int k = 0; k < 2097152; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vmovups %%ymm0, (%0)\n"
          "vmovups %%ymm1, (%1)\n"
          "vmovups %%ymm2, (%2)\n"
          "vmovups %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2097152), "r"(buf + j + k + 4194304), "r"(buf + j + k + 6291456) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_23(float *buf);
void helper_float_23(float *buf) {
  helper_float_23_recursive(buf, 23);
}
void helper_float_24_recursive(float *buf, int depth);
void helper_float_24_recursive(float *buf, int depth) {
  if (depth == 12) {
    for (int j = 0; j < 4096; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 4096) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 15) {
    helper_float_24_recursive(buf + 0, 12);
    helper_float_24_recursive(buf + 4096, 12);
    helper_float_24_recursive(buf + 8192, 12);
    helper_float_24_recursive(buf + 12288, 12);
    helper_float_24_recursive(buf + 16384, 12);
    helper_float_24_recursive(buf + 20480, 12);
    helper_float_24_recursive(buf + 24576, 12);
    helper_float_24_recursive(buf + 28672, 12);
    for (int j = 0; j < 32768; j += 32768) {
      for (int k = 0; k < 4096; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096), "r"(buf + j + k + 8192), "r"(buf + j + k + 12288), "r"(buf + j + k + 16384), "r"(buf + j + k + 20480), "r"(buf + j + k + 24576), "r"(buf + j + k + 28672) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 18) {
    helper_float_24_recursive(buf + 0, 15);
    helper_float_24_recursive(buf + 32768, 15);
    helper_float_24_recursive(buf + 65536, 15);
    helper_float_24_recursive(buf + 98304, 15);
    helper_float_24_recursive(buf + 131072, 15);
    helper_float_24_recursive(buf + 163840, 15);
    helper_float_24_recursive(buf + 196608, 15);
    helper_float_24_recursive(buf + 229376, 15);
    for (int j = 0; j < 262144; j += 262144) {
      for (int k = 0; k < 32768; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32768), "r"(buf + j + k + 65536), "r"(buf + j + k + 98304), "r"(buf + j + k + 131072), "r"(buf + j + k + 163840), "r"(buf + j + k + 196608), "r"(buf + j + k + 229376) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 21) {
    helper_float_24_recursive(buf + 0, 18);
    helper_float_24_recursive(buf + 262144, 18);
    helper_float_24_recursive(buf + 524288, 18);
    helper_float_24_recursive(buf + 786432, 18);
    helper_float_24_recursive(buf + 1048576, 18);
    helper_float_24_recursive(buf + 1310720, 18);
    helper_float_24_recursive(buf + 1572864, 18);
    helper_float_24_recursive(buf + 1835008, 18);
    for (int j = 0; j < 2097152; j += 2097152) {
      for (int k = 0; k < 262144; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 262144), "r"(buf + j + k + 524288), "r"(buf + j + k + 786432), "r"(buf + j + k + 1048576), "r"(buf + j + k + 1310720), "r"(buf + j + k + 1572864), "r"(buf + j + k + 1835008) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 24) {
    helper_float_24_recursive(buf + 0, 21);
    helper_float_24_recursive(buf + 2097152, 21);
    helper_float_24_recursive(buf + 4194304, 21);
    helper_float_24_recursive(buf + 6291456, 21);
    helper_float_24_recursive(buf + 8388608, 21);
    helper_float_24_recursive(buf + 10485760, 21);
    helper_float_24_recursive(buf + 12582912, 21);
    helper_float_24_recursive(buf + 14680064, 21);
    for (int j = 0; j < 16777216; j += 16777216) {
      for (int k = 0; k < 2097152; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2097152), "r"(buf + j + k + 4194304), "r"(buf + j + k + 6291456), "r"(buf + j + k + 8388608), "r"(buf + j + k + 10485760), "r"(buf + j + k + 12582912), "r"(buf + j + k + 14680064) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_24(float *buf);
void helper_float_24(float *buf) {
  helper_float_24_recursive(buf, 24);
}
void helper_float_25_recursive(float *buf, int depth);
void helper_float_25_recursive(float *buf, int depth) {
  if (depth == 13) {
    for (int j = 0; j < 8192; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 8192; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 8192; j += 4096) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 8192; j += 8192) {
      for (int k = 0; k < 4096; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 16) {
    helper_float_25_recursive(buf + 0, 13);
    helper_float_25_recursive(buf + 8192, 13);
    helper_float_25_recursive(buf + 16384, 13);
    helper_float_25_recursive(buf + 24576, 13);
    helper_float_25_recursive(buf + 32768, 13);
    helper_float_25_recursive(buf + 40960, 13);
    helper_float_25_recursive(buf + 49152, 13);
    helper_float_25_recursive(buf + 57344, 13);
    for (int j = 0; j < 65536; j += 65536) {
      for (int k = 0; k < 8192; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8192), "r"(buf + j + k + 16384), "r"(buf + j + k + 24576), "r"(buf + j + k + 32768), "r"(buf + j + k + 40960), "r"(buf + j + k + 49152), "r"(buf + j + k + 57344) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 19) {
    helper_float_25_recursive(buf + 0, 16);
    helper_float_25_recursive(buf + 65536, 16);
    helper_float_25_recursive(buf + 131072, 16);
    helper_float_25_recursive(buf + 196608, 16);
    helper_float_25_recursive(buf + 262144, 16);
    helper_float_25_recursive(buf + 327680, 16);
    helper_float_25_recursive(buf + 393216, 16);
    helper_float_25_recursive(buf + 458752, 16);
    for (int j = 0; j < 524288; j += 524288) {
      for (int k = 0; k < 65536; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 65536), "r"(buf + j + k + 131072), "r"(buf + j + k + 196608), "r"(buf + j + k + 262144), "r"(buf + j + k + 327680), "r"(buf + j + k + 393216), "r"(buf + j + k + 458752) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 22) {
    helper_float_25_recursive(buf + 0, 19);
    helper_float_25_recursive(buf + 524288, 19);
    helper_float_25_recursive(buf + 1048576, 19);
    helper_float_25_recursive(buf + 1572864, 19);
    helper_float_25_recursive(buf + 2097152, 19);
    helper_float_25_recursive(buf + 2621440, 19);
    helper_float_25_recursive(buf + 3145728, 19);
    helper_float_25_recursive(buf + 3670016, 19);
    for (int j = 0; j < 4194304; j += 4194304) {
      for (int k = 0; k < 524288; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 524288), "r"(buf + j + k + 1048576), "r"(buf + j + k + 1572864), "r"(buf + j + k + 2097152), "r"(buf + j + k + 2621440), "r"(buf + j + k + 3145728), "r"(buf + j + k + 3670016) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 25) {
    helper_float_25_recursive(buf + 0, 22);
    helper_float_25_recursive(buf + 4194304, 22);
    helper_float_25_recursive(buf + 8388608, 22);
    helper_float_25_recursive(buf + 12582912, 22);
    helper_float_25_recursive(buf + 16777216, 22);
    helper_float_25_recursive(buf + 20971520, 22);
    helper_float_25_recursive(buf + 25165824, 22);
    helper_float_25_recursive(buf + 29360128, 22);
    for (int j = 0; j < 33554432; j += 33554432) {
      for (int k = 0; k < 4194304; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4194304), "r"(buf + j + k + 8388608), "r"(buf + j + k + 12582912), "r"(buf + j + k + 16777216), "r"(buf + j + k + 20971520), "r"(buf + j + k + 25165824), "r"(buf + j + k + 29360128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_25(float *buf);
void helper_float_25(float *buf) {
  helper_float_25_recursive(buf, 25);
}
void helper_float_26_recursive(float *buf, int depth);
void helper_float_26_recursive(float *buf, int depth) {
  if (depth == 11) {
    for (int j = 0; j < 2048; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 2048) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vmovups %%ymm0, (%0)\n"
          "vmovups %%ymm1, (%1)\n"
          "vmovups %%ymm2, (%2)\n"
          "vmovups %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 14) {
    helper_float_26_recursive(buf + 0, 11);
    helper_float_26_recursive(buf + 2048, 11);
    helper_float_26_recursive(buf + 4096, 11);
    helper_float_26_recursive(buf + 6144, 11);
    helper_float_26_recursive(buf + 8192, 11);
    helper_float_26_recursive(buf + 10240, 11);
    helper_float_26_recursive(buf + 12288, 11);
    helper_float_26_recursive(buf + 14336, 11);
    for (int j = 0; j < 16384; j += 16384) {
      for (int k = 0; k < 2048; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2048), "r"(buf + j + k + 4096), "r"(buf + j + k + 6144), "r"(buf + j + k + 8192), "r"(buf + j + k + 10240), "r"(buf + j + k + 12288), "r"(buf + j + k + 14336) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 17) {
    helper_float_26_recursive(buf + 0, 14);
    helper_float_26_recursive(buf + 16384, 14);
    helper_float_26_recursive(buf + 32768, 14);
    helper_float_26_recursive(buf + 49152, 14);
    helper_float_26_recursive(buf + 65536, 14);
    helper_float_26_recursive(buf + 81920, 14);
    helper_float_26_recursive(buf + 98304, 14);
    helper_float_26_recursive(buf + 114688, 14);
    for (int j = 0; j < 131072; j += 131072) {
      for (int k = 0; k < 16384; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 16384), "r"(buf + j + k + 32768), "r"(buf + j + k + 49152), "r"(buf + j + k + 65536), "r"(buf + j + k + 81920), "r"(buf + j + k + 98304), "r"(buf + j + k + 114688) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 20) {
    helper_float_26_recursive(buf + 0, 17);
    helper_float_26_recursive(buf + 131072, 17);
    helper_float_26_recursive(buf + 262144, 17);
    helper_float_26_recursive(buf + 393216, 17);
    helper_float_26_recursive(buf + 524288, 17);
    helper_float_26_recursive(buf + 655360, 17);
    helper_float_26_recursive(buf + 786432, 17);
    helper_float_26_recursive(buf + 917504, 17);
    for (int j = 0; j < 1048576; j += 1048576) {
      for (int k = 0; k < 131072; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 131072), "r"(buf + j + k + 262144), "r"(buf + j + k + 393216), "r"(buf + j + k + 524288), "r"(buf + j + k + 655360), "r"(buf + j + k + 786432), "r"(buf + j + k + 917504) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 23) {
    helper_float_26_recursive(buf + 0, 20);
    helper_float_26_recursive(buf + 1048576, 20);
    helper_float_26_recursive(buf + 2097152, 20);
    helper_float_26_recursive(buf + 3145728, 20);
    helper_float_26_recursive(buf + 4194304, 20);
    helper_float_26_recursive(buf + 5242880, 20);
    helper_float_26_recursive(buf + 6291456, 20);
    helper_float_26_recursive(buf + 7340032, 20);
    for (int j = 0; j < 8388608; j += 8388608) {
      for (int k = 0; k < 1048576; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 1048576), "r"(buf + j + k + 2097152), "r"(buf + j + k + 3145728), "r"(buf + j + k + 4194304), "r"(buf + j + k + 5242880), "r"(buf + j + k + 6291456), "r"(buf + j + k + 7340032) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 26) {
    helper_float_26_recursive(buf + 0, 23);
    helper_float_26_recursive(buf + 8388608, 23);
    helper_float_26_recursive(buf + 16777216, 23);
    helper_float_26_recursive(buf + 25165824, 23);
    helper_float_26_recursive(buf + 33554432, 23);
    helper_float_26_recursive(buf + 41943040, 23);
    helper_float_26_recursive(buf + 50331648, 23);
    helper_float_26_recursive(buf + 58720256, 23);
    for (int j = 0; j < 67108864; j += 67108864) {
      for (int k = 0; k < 8388608; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8388608), "r"(buf + j + k + 16777216), "r"(buf + j + k + 25165824), "r"(buf + j + k + 33554432), "r"(buf + j + k + 41943040), "r"(buf + j + k + 50331648), "r"(buf + j + k + 58720256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_26(float *buf);
void helper_float_26(float *buf) {
  helper_float_26_recursive(buf, 26);
}
void helper_float_27_recursive(float *buf, int depth);
void helper_float_27_recursive(float *buf, int depth) {
  if (depth == 12) {
    for (int j = 0; j < 4096; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 4096) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 15) {
    helper_float_27_recursive(buf + 0, 12);
    helper_float_27_recursive(buf + 4096, 12);
    helper_float_27_recursive(buf + 8192, 12);
    helper_float_27_recursive(buf + 12288, 12);
    helper_float_27_recursive(buf + 16384, 12);
    helper_float_27_recursive(buf + 20480, 12);
    helper_float_27_recursive(buf + 24576, 12);
    helper_float_27_recursive(buf + 28672, 12);
    for (int j = 0; j < 32768; j += 32768) {
      for (int k = 0; k < 4096; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096), "r"(buf + j + k + 8192), "r"(buf + j + k + 12288), "r"(buf + j + k + 16384), "r"(buf + j + k + 20480), "r"(buf + j + k + 24576), "r"(buf + j + k + 28672) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 18) {
    helper_float_27_recursive(buf + 0, 15);
    helper_float_27_recursive(buf + 32768, 15);
    helper_float_27_recursive(buf + 65536, 15);
    helper_float_27_recursive(buf + 98304, 15);
    helper_float_27_recursive(buf + 131072, 15);
    helper_float_27_recursive(buf + 163840, 15);
    helper_float_27_recursive(buf + 196608, 15);
    helper_float_27_recursive(buf + 229376, 15);
    for (int j = 0; j < 262144; j += 262144) {
      for (int k = 0; k < 32768; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32768), "r"(buf + j + k + 65536), "r"(buf + j + k + 98304), "r"(buf + j + k + 131072), "r"(buf + j + k + 163840), "r"(buf + j + k + 196608), "r"(buf + j + k + 229376) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 21) {
    helper_float_27_recursive(buf + 0, 18);
    helper_float_27_recursive(buf + 262144, 18);
    helper_float_27_recursive(buf + 524288, 18);
    helper_float_27_recursive(buf + 786432, 18);
    helper_float_27_recursive(buf + 1048576, 18);
    helper_float_27_recursive(buf + 1310720, 18);
    helper_float_27_recursive(buf + 1572864, 18);
    helper_float_27_recursive(buf + 1835008, 18);
    for (int j = 0; j < 2097152; j += 2097152) {
      for (int k = 0; k < 262144; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 262144), "r"(buf + j + k + 524288), "r"(buf + j + k + 786432), "r"(buf + j + k + 1048576), "r"(buf + j + k + 1310720), "r"(buf + j + k + 1572864), "r"(buf + j + k + 1835008) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 24) {
    helper_float_27_recursive(buf + 0, 21);
    helper_float_27_recursive(buf + 2097152, 21);
    helper_float_27_recursive(buf + 4194304, 21);
    helper_float_27_recursive(buf + 6291456, 21);
    helper_float_27_recursive(buf + 8388608, 21);
    helper_float_27_recursive(buf + 10485760, 21);
    helper_float_27_recursive(buf + 12582912, 21);
    helper_float_27_recursive(buf + 14680064, 21);
    for (int j = 0; j < 16777216; j += 16777216) {
      for (int k = 0; k < 2097152; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2097152), "r"(buf + j + k + 4194304), "r"(buf + j + k + 6291456), "r"(buf + j + k + 8388608), "r"(buf + j + k + 10485760), "r"(buf + j + k + 12582912), "r"(buf + j + k + 14680064) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 27) {
    helper_float_27_recursive(buf + 0, 24);
    helper_float_27_recursive(buf + 16777216, 24);
    helper_float_27_recursive(buf + 33554432, 24);
    helper_float_27_recursive(buf + 50331648, 24);
    helper_float_27_recursive(buf + 67108864, 24);
    helper_float_27_recursive(buf + 83886080, 24);
    helper_float_27_recursive(buf + 100663296, 24);
    helper_float_27_recursive(buf + 117440512, 24);
    for (int j = 0; j < 134217728; j += 134217728) {
      for (int k = 0; k < 16777216; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 16777216), "r"(buf + j + k + 33554432), "r"(buf + j + k + 50331648), "r"(buf + j + k + 67108864), "r"(buf + j + k + 83886080), "r"(buf + j + k + 100663296), "r"(buf + j + k + 117440512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_27(float *buf);
void helper_float_27(float *buf) {
  helper_float_27_recursive(buf, 27);
}
void helper_float_28_recursive(float *buf, int depth);
void helper_float_28_recursive(float *buf, int depth) {
  if (depth == 13) {
    for (int j = 0; j < 8192; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 8192; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 8192; j += 4096) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 8192; j += 8192) {
      for (int k = 0; k < 4096; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 16) {
    helper_float_28_recursive(buf + 0, 13);
    helper_float_28_recursive(buf + 8192, 13);
    helper_float_28_recursive(buf + 16384, 13);
    helper_float_28_recursive(buf + 24576, 13);
    helper_float_28_recursive(buf + 32768, 13);
    helper_float_28_recursive(buf + 40960, 13);
    helper_float_28_recursive(buf + 49152, 13);
    helper_float_28_recursive(buf + 57344, 13);
    for (int j = 0; j < 65536; j += 65536) {
      for (int k = 0; k < 8192; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8192), "r"(buf + j + k + 16384), "r"(buf + j + k + 24576), "r"(buf + j + k + 32768), "r"(buf + j + k + 40960), "r"(buf + j + k + 49152), "r"(buf + j + k + 57344) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 19) {
    helper_float_28_recursive(buf + 0, 16);
    helper_float_28_recursive(buf + 65536, 16);
    helper_float_28_recursive(buf + 131072, 16);
    helper_float_28_recursive(buf + 196608, 16);
    helper_float_28_recursive(buf + 262144, 16);
    helper_float_28_recursive(buf + 327680, 16);
    helper_float_28_recursive(buf + 393216, 16);
    helper_float_28_recursive(buf + 458752, 16);
    for (int j = 0; j < 524288; j += 524288) {
      for (int k = 0; k < 65536; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 65536), "r"(buf + j + k + 131072), "r"(buf + j + k + 196608), "r"(buf + j + k + 262144), "r"(buf + j + k + 327680), "r"(buf + j + k + 393216), "r"(buf + j + k + 458752) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 22) {
    helper_float_28_recursive(buf + 0, 19);
    helper_float_28_recursive(buf + 524288, 19);
    helper_float_28_recursive(buf + 1048576, 19);
    helper_float_28_recursive(buf + 1572864, 19);
    helper_float_28_recursive(buf + 2097152, 19);
    helper_float_28_recursive(buf + 2621440, 19);
    helper_float_28_recursive(buf + 3145728, 19);
    helper_float_28_recursive(buf + 3670016, 19);
    for (int j = 0; j < 4194304; j += 4194304) {
      for (int k = 0; k < 524288; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 524288), "r"(buf + j + k + 1048576), "r"(buf + j + k + 1572864), "r"(buf + j + k + 2097152), "r"(buf + j + k + 2621440), "r"(buf + j + k + 3145728), "r"(buf + j + k + 3670016) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 25) {
    helper_float_28_recursive(buf + 0, 22);
    helper_float_28_recursive(buf + 4194304, 22);
    helper_float_28_recursive(buf + 8388608, 22);
    helper_float_28_recursive(buf + 12582912, 22);
    helper_float_28_recursive(buf + 16777216, 22);
    helper_float_28_recursive(buf + 20971520, 22);
    helper_float_28_recursive(buf + 25165824, 22);
    helper_float_28_recursive(buf + 29360128, 22);
    for (int j = 0; j < 33554432; j += 33554432) {
      for (int k = 0; k < 4194304; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4194304), "r"(buf + j + k + 8388608), "r"(buf + j + k + 12582912), "r"(buf + j + k + 16777216), "r"(buf + j + k + 20971520), "r"(buf + j + k + 25165824), "r"(buf + j + k + 29360128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 28) {
    helper_float_28_recursive(buf + 0, 25);
    helper_float_28_recursive(buf + 33554432, 25);
    helper_float_28_recursive(buf + 67108864, 25);
    helper_float_28_recursive(buf + 100663296, 25);
    helper_float_28_recursive(buf + 134217728, 25);
    helper_float_28_recursive(buf + 167772160, 25);
    helper_float_28_recursive(buf + 201326592, 25);
    helper_float_28_recursive(buf + 234881024, 25);
    for (int j = 0; j < 268435456; j += 268435456) {
      for (int k = 0; k < 33554432; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 33554432), "r"(buf + j + k + 67108864), "r"(buf + j + k + 100663296), "r"(buf + j + k + 134217728), "r"(buf + j + k + 167772160), "r"(buf + j + k + 201326592), "r"(buf + j + k + 234881024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_28(float *buf);
void helper_float_28(float *buf) {
  helper_float_28_recursive(buf, 28);
}
void helper_float_29_recursive(float *buf, int depth);
void helper_float_29_recursive(float *buf, int depth) {
  if (depth == 11) {
    for (int j = 0; j < 2048; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 2048) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vmovups %%ymm0, (%0)\n"
          "vmovups %%ymm1, (%1)\n"
          "vmovups %%ymm2, (%2)\n"
          "vmovups %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 14) {
    helper_float_29_recursive(buf + 0, 11);
    helper_float_29_recursive(buf + 2048, 11);
    helper_float_29_recursive(buf + 4096, 11);
    helper_float_29_recursive(buf + 6144, 11);
    helper_float_29_recursive(buf + 8192, 11);
    helper_float_29_recursive(buf + 10240, 11);
    helper_float_29_recursive(buf + 12288, 11);
    helper_float_29_recursive(buf + 14336, 11);
    for (int j = 0; j < 16384; j += 16384) {
      for (int k = 0; k < 2048; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2048), "r"(buf + j + k + 4096), "r"(buf + j + k + 6144), "r"(buf + j + k + 8192), "r"(buf + j + k + 10240), "r"(buf + j + k + 12288), "r"(buf + j + k + 14336) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 17) {
    helper_float_29_recursive(buf + 0, 14);
    helper_float_29_recursive(buf + 16384, 14);
    helper_float_29_recursive(buf + 32768, 14);
    helper_float_29_recursive(buf + 49152, 14);
    helper_float_29_recursive(buf + 65536, 14);
    helper_float_29_recursive(buf + 81920, 14);
    helper_float_29_recursive(buf + 98304, 14);
    helper_float_29_recursive(buf + 114688, 14);
    for (int j = 0; j < 131072; j += 131072) {
      for (int k = 0; k < 16384; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 16384), "r"(buf + j + k + 32768), "r"(buf + j + k + 49152), "r"(buf + j + k + 65536), "r"(buf + j + k + 81920), "r"(buf + j + k + 98304), "r"(buf + j + k + 114688) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 20) {
    helper_float_29_recursive(buf + 0, 17);
    helper_float_29_recursive(buf + 131072, 17);
    helper_float_29_recursive(buf + 262144, 17);
    helper_float_29_recursive(buf + 393216, 17);
    helper_float_29_recursive(buf + 524288, 17);
    helper_float_29_recursive(buf + 655360, 17);
    helper_float_29_recursive(buf + 786432, 17);
    helper_float_29_recursive(buf + 917504, 17);
    for (int j = 0; j < 1048576; j += 1048576) {
      for (int k = 0; k < 131072; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 131072), "r"(buf + j + k + 262144), "r"(buf + j + k + 393216), "r"(buf + j + k + 524288), "r"(buf + j + k + 655360), "r"(buf + j + k + 786432), "r"(buf + j + k + 917504) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 23) {
    helper_float_29_recursive(buf + 0, 20);
    helper_float_29_recursive(buf + 1048576, 20);
    helper_float_29_recursive(buf + 2097152, 20);
    helper_float_29_recursive(buf + 3145728, 20);
    helper_float_29_recursive(buf + 4194304, 20);
    helper_float_29_recursive(buf + 5242880, 20);
    helper_float_29_recursive(buf + 6291456, 20);
    helper_float_29_recursive(buf + 7340032, 20);
    for (int j = 0; j < 8388608; j += 8388608) {
      for (int k = 0; k < 1048576; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 1048576), "r"(buf + j + k + 2097152), "r"(buf + j + k + 3145728), "r"(buf + j + k + 4194304), "r"(buf + j + k + 5242880), "r"(buf + j + k + 6291456), "r"(buf + j + k + 7340032) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 26) {
    helper_float_29_recursive(buf + 0, 23);
    helper_float_29_recursive(buf + 8388608, 23);
    helper_float_29_recursive(buf + 16777216, 23);
    helper_float_29_recursive(buf + 25165824, 23);
    helper_float_29_recursive(buf + 33554432, 23);
    helper_float_29_recursive(buf + 41943040, 23);
    helper_float_29_recursive(buf + 50331648, 23);
    helper_float_29_recursive(buf + 58720256, 23);
    for (int j = 0; j < 67108864; j += 67108864) {
      for (int k = 0; k < 8388608; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8388608), "r"(buf + j + k + 16777216), "r"(buf + j + k + 25165824), "r"(buf + j + k + 33554432), "r"(buf + j + k + 41943040), "r"(buf + j + k + 50331648), "r"(buf + j + k + 58720256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 29) {
    helper_float_29_recursive(buf + 0, 26);
    helper_float_29_recursive(buf + 67108864, 26);
    helper_float_29_recursive(buf + 134217728, 26);
    helper_float_29_recursive(buf + 201326592, 26);
    helper_float_29_recursive(buf + 268435456, 26);
    helper_float_29_recursive(buf + 335544320, 26);
    helper_float_29_recursive(buf + 402653184, 26);
    helper_float_29_recursive(buf + 469762048, 26);
    for (int j = 0; j < 536870912; j += 536870912) {
      for (int k = 0; k < 67108864; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 67108864), "r"(buf + j + k + 134217728), "r"(buf + j + k + 201326592), "r"(buf + j + k + 268435456), "r"(buf + j + k + 335544320), "r"(buf + j + k + 402653184), "r"(buf + j + k + 469762048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_29(float *buf);
void helper_float_29(float *buf) {
  helper_float_29_recursive(buf, 29);
}
void helper_float_30_recursive(float *buf, int depth);
void helper_float_30_recursive(float *buf, int depth) {
  if (depth == 12) {
    for (int j = 0; j < 4096; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilps $160, %%ymm1, %%ymm8\n"
          "vpermilps $245, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilps $160, %%ymm2, %%ymm8\n"
          "vpermilps $245, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilps $160, %%ymm3, %%ymm8\n"
          "vpermilps $245, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilps $160, %%ymm4, %%ymm8\n"
          "vpermilps $245, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilps $160, %%ymm5, %%ymm8\n"
          "vpermilps $245, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilps $160, %%ymm6, %%ymm8\n"
          "vpermilps $245, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilps $160, %%ymm7, %%ymm8\n"
          "vpermilps $245, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubps %%ymm11, %%ymm8, %%ymm7\n"
          "vpermilps $68, %%ymm0, %%ymm8\n"
          "vpermilps $238, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm0\n"
          "vpermilps $68, %%ymm1, %%ymm8\n"
          "vpermilps $238, %%ymm1, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm1\n"
          "vpermilps $68, %%ymm2, %%ymm8\n"
          "vpermilps $238, %%ymm2, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm2\n"
          "vpermilps $68, %%ymm3, %%ymm8\n"
          "vpermilps $238, %%ymm3, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm3\n"
          "vpermilps $68, %%ymm4, %%ymm8\n"
          "vpermilps $238, %%ymm4, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm4\n"
          "vpermilps $68, %%ymm5, %%ymm8\n"
          "vpermilps $238, %%ymm5, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm5\n"
          "vpermilps $68, %%ymm6, %%ymm8\n"
          "vpermilps $238, %%ymm6, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm6\n"
          "vpermilps $68, %%ymm7, %%ymm8\n"
          "vpermilps $238, %%ymm7, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm11\n"
          "vblendps $204, %%ymm11, %%ymm9, %%ymm12\n"
          "vaddps %%ymm8, %%ymm12, %%ymm7\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm0, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm0, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm0\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm1, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm1, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm1\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm2, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm2, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm2\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm3, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm3, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm3\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm4, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm4, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm4\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm5, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm5, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm5\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm6, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm6, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm6\n"
          "vxorps %%ymm8, %%ymm8, %%ymm8\n"
          "vsubps %%ymm7, %%ymm8, %%ymm9\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm10\n"
          "vperm2f128 $49, %%ymm9, %%ymm7, %%ymm11\n"
          "vaddps %%ymm10, %%ymm11, %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8), "r"(buf + j + k + 16), "r"(buf + j + k + 24), "r"(buf + j + k + 32), "r"(buf + j + k + 40), "r"(buf + j + k + 48), "r"(buf + j + k + 56) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 512) {
      for (int k = 0; k < 64; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 64), "r"(buf + j + k + 128), "r"(buf + j + k + 192), "r"(buf + j + k + 256), "r"(buf + j + k + 320), "r"(buf + j + k + 384), "r"(buf + j + k + 448) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 4096) {
      for (int k = 0; k < 512; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 15) {
    helper_float_30_recursive(buf + 0, 12);
    helper_float_30_recursive(buf + 4096, 12);
    helper_float_30_recursive(buf + 8192, 12);
    helper_float_30_recursive(buf + 12288, 12);
    helper_float_30_recursive(buf + 16384, 12);
    helper_float_30_recursive(buf + 20480, 12);
    helper_float_30_recursive(buf + 24576, 12);
    helper_float_30_recursive(buf + 28672, 12);
    for (int j = 0; j < 32768; j += 32768) {
      for (int k = 0; k < 4096; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096), "r"(buf + j + k + 8192), "r"(buf + j + k + 12288), "r"(buf + j + k + 16384), "r"(buf + j + k + 20480), "r"(buf + j + k + 24576), "r"(buf + j + k + 28672) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 18) {
    helper_float_30_recursive(buf + 0, 15);
    helper_float_30_recursive(buf + 32768, 15);
    helper_float_30_recursive(buf + 65536, 15);
    helper_float_30_recursive(buf + 98304, 15);
    helper_float_30_recursive(buf + 131072, 15);
    helper_float_30_recursive(buf + 163840, 15);
    helper_float_30_recursive(buf + 196608, 15);
    helper_float_30_recursive(buf + 229376, 15);
    for (int j = 0; j < 262144; j += 262144) {
      for (int k = 0; k < 32768; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32768), "r"(buf + j + k + 65536), "r"(buf + j + k + 98304), "r"(buf + j + k + 131072), "r"(buf + j + k + 163840), "r"(buf + j + k + 196608), "r"(buf + j + k + 229376) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 21) {
    helper_float_30_recursive(buf + 0, 18);
    helper_float_30_recursive(buf + 262144, 18);
    helper_float_30_recursive(buf + 524288, 18);
    helper_float_30_recursive(buf + 786432, 18);
    helper_float_30_recursive(buf + 1048576, 18);
    helper_float_30_recursive(buf + 1310720, 18);
    helper_float_30_recursive(buf + 1572864, 18);
    helper_float_30_recursive(buf + 1835008, 18);
    for (int j = 0; j < 2097152; j += 2097152) {
      for (int k = 0; k < 262144; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 262144), "r"(buf + j + k + 524288), "r"(buf + j + k + 786432), "r"(buf + j + k + 1048576), "r"(buf + j + k + 1310720), "r"(buf + j + k + 1572864), "r"(buf + j + k + 1835008) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 24) {
    helper_float_30_recursive(buf + 0, 21);
    helper_float_30_recursive(buf + 2097152, 21);
    helper_float_30_recursive(buf + 4194304, 21);
    helper_float_30_recursive(buf + 6291456, 21);
    helper_float_30_recursive(buf + 8388608, 21);
    helper_float_30_recursive(buf + 10485760, 21);
    helper_float_30_recursive(buf + 12582912, 21);
    helper_float_30_recursive(buf + 14680064, 21);
    for (int j = 0; j < 16777216; j += 16777216) {
      for (int k = 0; k < 2097152; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2097152), "r"(buf + j + k + 4194304), "r"(buf + j + k + 6291456), "r"(buf + j + k + 8388608), "r"(buf + j + k + 10485760), "r"(buf + j + k + 12582912), "r"(buf + j + k + 14680064) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 27) {
    helper_float_30_recursive(buf + 0, 24);
    helper_float_30_recursive(buf + 16777216, 24);
    helper_float_30_recursive(buf + 33554432, 24);
    helper_float_30_recursive(buf + 50331648, 24);
    helper_float_30_recursive(buf + 67108864, 24);
    helper_float_30_recursive(buf + 83886080, 24);
    helper_float_30_recursive(buf + 100663296, 24);
    helper_float_30_recursive(buf + 117440512, 24);
    for (int j = 0; j < 134217728; j += 134217728) {
      for (int k = 0; k < 16777216; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 16777216), "r"(buf + j + k + 33554432), "r"(buf + j + k + 50331648), "r"(buf + j + k + 67108864), "r"(buf + j + k + 83886080), "r"(buf + j + k + 100663296), "r"(buf + j + k + 117440512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 30) {
    helper_float_30_recursive(buf + 0, 27);
    helper_float_30_recursive(buf + 134217728, 27);
    helper_float_30_recursive(buf + 268435456, 27);
    helper_float_30_recursive(buf + 402653184, 27);
    helper_float_30_recursive(buf + 536870912, 27);
    helper_float_30_recursive(buf + 671088640, 27);
    helper_float_30_recursive(buf + 805306368, 27);
    helper_float_30_recursive(buf + 939524096, 27);
    for (int j = 0; j < 1073741824; j += 1073741824) {
      for (int k = 0; k < 134217728; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vaddps %%ymm1, %%ymm0, %%ymm8\n"
          "vsubps %%ymm1, %%ymm0, %%ymm9\n"
          "vaddps %%ymm3, %%ymm2, %%ymm10\n"
          "vsubps %%ymm3, %%ymm2, %%ymm11\n"
          "vaddps %%ymm5, %%ymm4, %%ymm12\n"
          "vsubps %%ymm5, %%ymm4, %%ymm13\n"
          "vaddps %%ymm7, %%ymm6, %%ymm14\n"
          "vsubps %%ymm7, %%ymm6, %%ymm15\n"
          "vaddps %%ymm10, %%ymm8, %%ymm0\n"
          "vsubps %%ymm10, %%ymm8, %%ymm2\n"
          "vaddps %%ymm11, %%ymm9, %%ymm1\n"
          "vsubps %%ymm11, %%ymm9, %%ymm3\n"
          "vaddps %%ymm14, %%ymm12, %%ymm4\n"
          "vsubps %%ymm14, %%ymm12, %%ymm6\n"
          "vaddps %%ymm15, %%ymm13, %%ymm5\n"
          "vsubps %%ymm15, %%ymm13, %%ymm7\n"
          "vaddps %%ymm4, %%ymm0, %%ymm8\n"
          "vsubps %%ymm4, %%ymm0, %%ymm12\n"
          "vaddps %%ymm5, %%ymm1, %%ymm9\n"
          "vsubps %%ymm5, %%ymm1, %%ymm13\n"
          "vaddps %%ymm6, %%ymm2, %%ymm10\n"
          "vsubps %%ymm6, %%ymm2, %%ymm14\n"
          "vaddps %%ymm7, %%ymm3, %%ymm11\n"
          "vsubps %%ymm7, %%ymm3, %%ymm15\n"
          "vmovups %%ymm8, (%0)\n"
          "vmovups %%ymm9, (%1)\n"
          "vmovups %%ymm10, (%2)\n"
          "vmovups %%ymm11, (%3)\n"
          "vmovups %%ymm12, (%4)\n"
          "vmovups %%ymm13, (%5)\n"
          "vmovups %%ymm14, (%6)\n"
          "vmovups %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 134217728), "r"(buf + j + k + 268435456), "r"(buf + j + k + 402653184), "r"(buf + j + k + 536870912), "r"(buf + j + k + 671088640), "r"(buf + j + k + 805306368), "r"(buf + j + k + 939524096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_float_30(float *buf);
void helper_float_30(float *buf) {
  helper_float_30_recursive(buf, 30);
}
int fht_float(float *buf, int log_n) {
  if (log_n == 0) {
    return 0;
  }
  if (log_n == 1) {
    helper_float_1(buf);
    return 0;
  }
  if (log_n == 2) {
    helper_float_2(buf);
    return 0;
  }
  if (log_n == 3) {
    helper_float_3(buf);
    return 0;
  }
  if (log_n == 4) {
    helper_float_4(buf);
    return 0;
  }
  if (log_n == 5) {
    helper_float_5(buf);
    return 0;
  }
  if (log_n == 6) {
    helper_float_6(buf);
    return 0;
  }
  if (log_n == 7) {
    helper_float_7(buf);
    return 0;
  }
  if (log_n == 8) {
    helper_float_8(buf);
    return 0;
  }
  if (log_n == 9) {
    helper_float_9(buf);
    return 0;
  }
  if (log_n == 10) {
    helper_float_10(buf);
    return 0;
  }
  if (log_n == 11) {
    helper_float_11(buf);
    return 0;
  }
  if (log_n == 12) {
    helper_float_12(buf);
    return 0;
  }
  if (log_n == 13) {
    helper_float_13(buf);
    return 0;
  }
  if (log_n == 14) {
    helper_float_14(buf);
    return 0;
  }
  if (log_n == 15) {
    helper_float_15(buf);
    return 0;
  }
  if (log_n == 16) {
    helper_float_16(buf);
    return 0;
  }
  if (log_n == 17) {
    helper_float_17(buf);
    return 0;
  }
  if (log_n == 18) {
    helper_float_18(buf);
    return 0;
  }
  if (log_n == 19) {
    helper_float_19(buf);
    return 0;
  }
  if (log_n == 20) {
    helper_float_20(buf);
    return 0;
  }
  if (log_n == 21) {
    helper_float_21(buf);
    return 0;
  }
  if (log_n == 22) {
    helper_float_22(buf);
    return 0;
  }
  if (log_n == 23) {
    helper_float_23(buf);
    return 0;
  }
  if (log_n == 24) {
    helper_float_24(buf);
    return 0;
  }
  if (log_n == 25) {
    helper_float_25(buf);
    return 0;
  }
  if (log_n == 26) {
    helper_float_26(buf);
    return 0;
  }
  if (log_n == 27) {
    helper_float_27(buf);
    return 0;
  }
  if (log_n == 28) {
    helper_float_28(buf);
    return 0;
  }
  if (log_n == 29) {
    helper_float_29(buf);
    return 0;
  }
  if (log_n == 30) {
    helper_float_30(buf);
    return 0;
  }
  return 1;
}
inline void helper_double_1(double *buf);
inline void helper_double_1(double *buf) {
  for (int j = 0; j < 2; j += 2) {
    for (int k = 0; k < 1; ++k) {
      double u = buf[j + k];
      double v = buf[j + k + 1];
      buf[j + k] = u + v;
      buf[j + k + 1] = u - v;
    }
  }
}
void helper_double_2_recursive(double *buf, int depth);
void helper_double_2_recursive(double *buf, int depth) {
  if (depth == 2) {
    for (int j = 0; j < 4; j += 4) {
      __asm__ volatile (
        "vmovupd (%0), %%ymm0\n"
        "vpermilpd $0, %%ymm0, %%ymm8\n"
        "vpermilpd $15, %%ymm0, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
        "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
        "vmovupd %%ymm0, (%0)\n"
        :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
      );
    }
    return;
  }
}
void helper_double_2(double *buf);
void helper_double_2(double *buf) {
  helper_double_2_recursive(buf, 2);
}
inline void helper_double_3(double *buf);
inline void helper_double_3(double *buf) {
  for (int j = 0; j < 8; j += 8) {
    for (int k = 0; k < 4; k += 4) {
      __asm__ volatile (
        "vmovupd (%0), %%ymm0\n"
        "vmovupd (%1), %%ymm1\n"
        "vpermilpd $0, %%ymm0, %%ymm8\n"
        "vpermilpd $15, %%ymm0, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
        "vpermilpd $0, %%ymm1, %%ymm8\n"
        "vpermilpd $15, %%ymm1, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
        "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
        "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
        "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
        "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
        "vmovupd %%ymm8, (%0)\n"
        "vmovupd %%ymm9, (%1)\n"
        :: "r"(buf + j + k + 0), "r"(buf + j + k + 4) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
      );
    }
  }
}
void helper_double_4_recursive(double *buf, int depth);
void helper_double_4_recursive(double *buf, int depth) {
  if (depth == 4) {
    for (int j = 0; j < 16; j += 16) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vmovupd %%ymm0, (%0)\n"
          "vmovupd %%ymm1, (%1)\n"
          "vmovupd %%ymm2, (%2)\n"
          "vmovupd %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_4(double *buf);
void helper_double_4(double *buf) {
  helper_double_4_recursive(buf, 4);
}
inline void helper_double_5(double *buf);
inline void helper_double_5(double *buf) {
  for (int j = 0; j < 32; j += 32) {
    for (int k = 0; k < 4; k += 4) {
      __asm__ volatile (
        "vmovupd (%0), %%ymm0\n"
        "vmovupd (%1), %%ymm1\n"
        "vmovupd (%2), %%ymm2\n"
        "vmovupd (%3), %%ymm3\n"
        "vmovupd (%4), %%ymm4\n"
        "vmovupd (%5), %%ymm5\n"
        "vmovupd (%6), %%ymm6\n"
        "vmovupd (%7), %%ymm7\n"
        "vpermilpd $0, %%ymm0, %%ymm8\n"
        "vpermilpd $15, %%ymm0, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
        "vpermilpd $0, %%ymm1, %%ymm8\n"
        "vpermilpd $15, %%ymm1, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
        "vpermilpd $0, %%ymm2, %%ymm8\n"
        "vpermilpd $15, %%ymm2, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
        "vpermilpd $0, %%ymm3, %%ymm8\n"
        "vpermilpd $15, %%ymm3, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
        "vpermilpd $0, %%ymm4, %%ymm8\n"
        "vpermilpd $15, %%ymm4, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
        "vpermilpd $0, %%ymm5, %%ymm8\n"
        "vpermilpd $15, %%ymm5, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
        "vpermilpd $0, %%ymm6, %%ymm8\n"
        "vpermilpd $15, %%ymm6, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
        "vpermilpd $0, %%ymm7, %%ymm8\n"
        "vpermilpd $15, %%ymm7, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
        "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
        "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
        "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
        "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
        "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
        "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
        "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
        "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
        "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
        "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
        "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
        "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
        "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
        "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
        "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
        "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
        "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
        "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
        "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
        "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
        "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
        "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
        "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
        "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
        "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
        "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
        "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
        "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
        "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
        "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
        "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
        "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
        "vmovupd %%ymm8, (%0)\n"
        "vmovupd %%ymm9, (%1)\n"
        "vmovupd %%ymm10, (%2)\n"
        "vmovupd %%ymm11, (%3)\n"
        "vmovupd %%ymm12, (%4)\n"
        "vmovupd %%ymm13, (%5)\n"
        "vmovupd %%ymm14, (%6)\n"
        "vmovupd %%ymm15, (%7)\n"
        :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
      );
    }
  }
}
void helper_double_6_recursive(double *buf, int depth);
void helper_double_6_recursive(double *buf, int depth) {
  if (depth == 5) {
    for (int j = 0; j < 32; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 6) {
    helper_double_6_recursive(buf + 0, 5);
    helper_double_6_recursive(buf + 32, 5);
    for (int j = 0; j < 64; j += 64) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_6(double *buf);
void helper_double_6(double *buf) {
  helper_double_6_recursive(buf, 6);
}
void helper_double_7_recursive(double *buf, int depth);
void helper_double_7_recursive(double *buf, int depth) {
  if (depth == 5) {
    for (int j = 0; j < 32; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 7) {
    helper_double_7_recursive(buf + 0, 5);
    helper_double_7_recursive(buf + 32, 5);
    helper_double_7_recursive(buf + 64, 5);
    helper_double_7_recursive(buf + 96, 5);
    for (int j = 0; j < 128; j += 128) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vmovupd %%ymm0, (%0)\n"
          "vmovupd %%ymm1, (%1)\n"
          "vmovupd %%ymm2, (%2)\n"
          "vmovupd %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_7(double *buf);
void helper_double_7(double *buf) {
  helper_double_7_recursive(buf, 7);
}
void helper_double_8_recursive(double *buf, int depth);
void helper_double_8_recursive(double *buf, int depth) {
  if (depth == 5) {
    for (int j = 0; j < 32; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 8) {
    helper_double_8_recursive(buf + 0, 5);
    helper_double_8_recursive(buf + 32, 5);
    helper_double_8_recursive(buf + 64, 5);
    helper_double_8_recursive(buf + 96, 5);
    helper_double_8_recursive(buf + 128, 5);
    helper_double_8_recursive(buf + 160, 5);
    helper_double_8_recursive(buf + 192, 5);
    helper_double_8_recursive(buf + 224, 5);
    for (int j = 0; j < 256; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_8(double *buf);
void helper_double_8(double *buf) {
  helper_double_8_recursive(buf, 8);
}
inline void helper_double_9(double *buf);
inline void helper_double_9(double *buf) {
  for (int j = 0; j < 512; j += 32) {
    for (int k = 0; k < 4; k += 4) {
      __asm__ volatile (
        "vmovupd (%0), %%ymm0\n"
        "vmovupd (%1), %%ymm1\n"
        "vmovupd (%2), %%ymm2\n"
        "vmovupd (%3), %%ymm3\n"
        "vmovupd (%4), %%ymm4\n"
        "vmovupd (%5), %%ymm5\n"
        "vmovupd (%6), %%ymm6\n"
        "vmovupd (%7), %%ymm7\n"
        "vpermilpd $0, %%ymm0, %%ymm8\n"
        "vpermilpd $15, %%ymm0, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
        "vpermilpd $0, %%ymm1, %%ymm8\n"
        "vpermilpd $15, %%ymm1, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
        "vpermilpd $0, %%ymm2, %%ymm8\n"
        "vpermilpd $15, %%ymm2, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
        "vpermilpd $0, %%ymm3, %%ymm8\n"
        "vpermilpd $15, %%ymm3, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
        "vpermilpd $0, %%ymm4, %%ymm8\n"
        "vpermilpd $15, %%ymm4, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
        "vpermilpd $0, %%ymm5, %%ymm8\n"
        "vpermilpd $15, %%ymm5, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
        "vpermilpd $0, %%ymm6, %%ymm8\n"
        "vpermilpd $15, %%ymm6, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
        "vpermilpd $0, %%ymm7, %%ymm8\n"
        "vpermilpd $15, %%ymm7, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
        "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
        "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
        "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
        "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
        "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
        "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
        "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
        "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
        "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
        "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
        "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
        "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
        "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
        "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
        "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
        "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
        "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
        "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
        "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
        "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
        "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
        "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
        "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
        "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
        "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
        "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
        "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
        "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
        "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
        "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
        "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
        "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
        "vmovupd %%ymm8, (%0)\n"
        "vmovupd %%ymm9, (%1)\n"
        "vmovupd %%ymm10, (%2)\n"
        "vmovupd %%ymm11, (%3)\n"
        "vmovupd %%ymm12, (%4)\n"
        "vmovupd %%ymm13, (%5)\n"
        "vmovupd %%ymm14, (%6)\n"
        "vmovupd %%ymm15, (%7)\n"
        :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
      );
    }
  }
  for (int j = 0; j < 512; j += 256) {
    for (int k = 0; k < 32; k += 4) {
      __asm__ volatile (
        "vmovupd (%0), %%ymm0\n"
        "vmovupd (%1), %%ymm1\n"
        "vmovupd (%2), %%ymm2\n"
        "vmovupd (%3), %%ymm3\n"
        "vmovupd (%4), %%ymm4\n"
        "vmovupd (%5), %%ymm5\n"
        "vmovupd (%6), %%ymm6\n"
        "vmovupd (%7), %%ymm7\n"
        "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
        "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
        "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
        "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
        "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
        "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
        "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
        "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
        "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
        "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
        "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
        "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
        "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
        "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
        "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
        "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
        "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
        "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
        "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
        "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
        "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
        "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
        "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
        "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
        "vmovupd %%ymm8, (%0)\n"
        "vmovupd %%ymm9, (%1)\n"
        "vmovupd %%ymm10, (%2)\n"
        "vmovupd %%ymm11, (%3)\n"
        "vmovupd %%ymm12, (%4)\n"
        "vmovupd %%ymm13, (%5)\n"
        "vmovupd %%ymm14, (%6)\n"
        "vmovupd %%ymm15, (%7)\n"
        :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
      );
    }
  }
  for (int j = 0; j < 512; j += 512) {
    for (int k = 0; k < 256; k += 4) {
      __asm__ volatile (
        "vmovupd (%0), %%ymm0\n"
        "vmovupd (%1), %%ymm1\n"
        "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
        "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
        "vmovupd %%ymm8, (%0)\n"
        "vmovupd %%ymm9, (%1)\n"
        :: "r"(buf + j + k + 0), "r"(buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
      );
    }
  }
}
void helper_double_10_recursive(double *buf, int depth);
void helper_double_10_recursive(double *buf, int depth) {
  if (depth == 10) {
    for (int j = 0; j < 1024; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 1024; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 1024; j += 1024) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vmovupd %%ymm0, (%0)\n"
          "vmovupd %%ymm1, (%1)\n"
          "vmovupd %%ymm2, (%2)\n"
          "vmovupd %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256), "r"(buf + j + k + 512), "r"(buf + j + k + 768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_10(double *buf);
void helper_double_10(double *buf) {
  helper_double_10_recursive(buf, 10);
}
inline void helper_double_11(double *buf);
inline void helper_double_11(double *buf) {
  for (int j = 0; j < 2048; j += 32) {
    for (int k = 0; k < 4; k += 4) {
      __asm__ volatile (
        "vmovupd (%0), %%ymm0\n"
        "vmovupd (%1), %%ymm1\n"
        "vmovupd (%2), %%ymm2\n"
        "vmovupd (%3), %%ymm3\n"
        "vmovupd (%4), %%ymm4\n"
        "vmovupd (%5), %%ymm5\n"
        "vmovupd (%6), %%ymm6\n"
        "vmovupd (%7), %%ymm7\n"
        "vpermilpd $0, %%ymm0, %%ymm8\n"
        "vpermilpd $15, %%ymm0, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
        "vpermilpd $0, %%ymm1, %%ymm8\n"
        "vpermilpd $15, %%ymm1, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
        "vpermilpd $0, %%ymm2, %%ymm8\n"
        "vpermilpd $15, %%ymm2, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
        "vpermilpd $0, %%ymm3, %%ymm8\n"
        "vpermilpd $15, %%ymm3, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
        "vpermilpd $0, %%ymm4, %%ymm8\n"
        "vpermilpd $15, %%ymm4, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
        "vpermilpd $0, %%ymm5, %%ymm8\n"
        "vpermilpd $15, %%ymm5, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
        "vpermilpd $0, %%ymm6, %%ymm8\n"
        "vpermilpd $15, %%ymm6, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
        "vpermilpd $0, %%ymm7, %%ymm8\n"
        "vpermilpd $15, %%ymm7, %%ymm9\n"
        "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
        "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
        "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
        "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
        "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
        "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
        "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
        "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
        "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
        "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
        "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
        "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
        "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
        "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
        "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
        "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
        "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
        "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
        "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
        "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
        "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
        "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
        "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
        "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
        "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
        "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
        "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
        "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
        "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
        "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
        "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
        "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
        "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
        "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
        "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
        "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
        "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
        "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
        "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
        "vmovupd %%ymm8, (%0)\n"
        "vmovupd %%ymm9, (%1)\n"
        "vmovupd %%ymm10, (%2)\n"
        "vmovupd %%ymm11, (%3)\n"
        "vmovupd %%ymm12, (%4)\n"
        "vmovupd %%ymm13, (%5)\n"
        "vmovupd %%ymm14, (%6)\n"
        "vmovupd %%ymm15, (%7)\n"
        :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
      );
    }
  }
  for (int j = 0; j < 2048; j += 256) {
    for (int k = 0; k < 32; k += 4) {
      __asm__ volatile (
        "vmovupd (%0), %%ymm0\n"
        "vmovupd (%1), %%ymm1\n"
        "vmovupd (%2), %%ymm2\n"
        "vmovupd (%3), %%ymm3\n"
        "vmovupd (%4), %%ymm4\n"
        "vmovupd (%5), %%ymm5\n"
        "vmovupd (%6), %%ymm6\n"
        "vmovupd (%7), %%ymm7\n"
        "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
        "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
        "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
        "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
        "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
        "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
        "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
        "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
        "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
        "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
        "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
        "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
        "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
        "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
        "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
        "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
        "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
        "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
        "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
        "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
        "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
        "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
        "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
        "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
        "vmovupd %%ymm8, (%0)\n"
        "vmovupd %%ymm9, (%1)\n"
        "vmovupd %%ymm10, (%2)\n"
        "vmovupd %%ymm11, (%3)\n"
        "vmovupd %%ymm12, (%4)\n"
        "vmovupd %%ymm13, (%5)\n"
        "vmovupd %%ymm14, (%6)\n"
        "vmovupd %%ymm15, (%7)\n"
        :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
      );
    }
  }
  for (int j = 0; j < 2048; j += 2048) {
    for (int k = 0; k < 256; k += 4) {
      __asm__ volatile (
        "vmovupd (%0), %%ymm0\n"
        "vmovupd (%1), %%ymm1\n"
        "vmovupd (%2), %%ymm2\n"
        "vmovupd (%3), %%ymm3\n"
        "vmovupd (%4), %%ymm4\n"
        "vmovupd (%5), %%ymm5\n"
        "vmovupd (%6), %%ymm6\n"
        "vmovupd (%7), %%ymm7\n"
        "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
        "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
        "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
        "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
        "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
        "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
        "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
        "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
        "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
        "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
        "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
        "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
        "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
        "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
        "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
        "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
        "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
        "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
        "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
        "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
        "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
        "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
        "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
        "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
        "vmovupd %%ymm8, (%0)\n"
        "vmovupd %%ymm9, (%1)\n"
        "vmovupd %%ymm10, (%2)\n"
        "vmovupd %%ymm11, (%3)\n"
        "vmovupd %%ymm12, (%4)\n"
        "vmovupd %%ymm13, (%5)\n"
        "vmovupd %%ymm14, (%6)\n"
        "vmovupd %%ymm15, (%7)\n"
        :: "r"(buf + j + k + 0), "r"(buf + j + k + 256), "r"(buf + j + k + 512), "r"(buf + j + k + 768), "r"(buf + j + k + 1024), "r"(buf + j + k + 1280), "r"(buf + j + k + 1536), "r"(buf + j + k + 1792) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
      );
    }
  }
}
void helper_double_12_recursive(double *buf, int depth);
void helper_double_12_recursive(double *buf, int depth) {
  if (depth == 10) {
    for (int j = 0; j < 1024; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 1024; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 1024; j += 1024) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vmovupd %%ymm0, (%0)\n"
          "vmovupd %%ymm1, (%1)\n"
          "vmovupd %%ymm2, (%2)\n"
          "vmovupd %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256), "r"(buf + j + k + 512), "r"(buf + j + k + 768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 12) {
    helper_double_12_recursive(buf + 0, 10);
    helper_double_12_recursive(buf + 1024, 10);
    helper_double_12_recursive(buf + 2048, 10);
    helper_double_12_recursive(buf + 3072, 10);
    for (int j = 0; j < 4096; j += 4096) {
      for (int k = 0; k < 1024; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vmovupd %%ymm0, (%0)\n"
          "vmovupd %%ymm1, (%1)\n"
          "vmovupd %%ymm2, (%2)\n"
          "vmovupd %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 1024), "r"(buf + j + k + 2048), "r"(buf + j + k + 3072) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_12(double *buf);
void helper_double_12(double *buf) {
  helper_double_12_recursive(buf, 12);
}
void helper_double_13_recursive(double *buf, int depth);
void helper_double_13_recursive(double *buf, int depth) {
  if (depth == 11) {
    for (int j = 0; j < 2048; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 2048) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256), "r"(buf + j + k + 512), "r"(buf + j + k + 768), "r"(buf + j + k + 1024), "r"(buf + j + k + 1280), "r"(buf + j + k + 1536), "r"(buf + j + k + 1792) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 13) {
    helper_double_13_recursive(buf + 0, 11);
    helper_double_13_recursive(buf + 2048, 11);
    helper_double_13_recursive(buf + 4096, 11);
    helper_double_13_recursive(buf + 6144, 11);
    for (int j = 0; j < 8192; j += 8192) {
      for (int k = 0; k < 2048; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vmovupd %%ymm0, (%0)\n"
          "vmovupd %%ymm1, (%1)\n"
          "vmovupd %%ymm2, (%2)\n"
          "vmovupd %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2048), "r"(buf + j + k + 4096), "r"(buf + j + k + 6144) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_13(double *buf);
void helper_double_13(double *buf) {
  helper_double_13_recursive(buf, 13);
}
void helper_double_14_recursive(double *buf, int depth);
void helper_double_14_recursive(double *buf, int depth) {
  if (depth == 9) {
    for (int j = 0; j < 512; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 512; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 512; j += 512) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 12) {
    helper_double_14_recursive(buf + 0, 9);
    helper_double_14_recursive(buf + 512, 9);
    helper_double_14_recursive(buf + 1024, 9);
    helper_double_14_recursive(buf + 1536, 9);
    helper_double_14_recursive(buf + 2048, 9);
    helper_double_14_recursive(buf + 2560, 9);
    helper_double_14_recursive(buf + 3072, 9);
    helper_double_14_recursive(buf + 3584, 9);
    for (int j = 0; j < 4096; j += 4096) {
      for (int k = 0; k < 512; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 14) {
    helper_double_14_recursive(buf + 0, 12);
    helper_double_14_recursive(buf + 4096, 12);
    helper_double_14_recursive(buf + 8192, 12);
    helper_double_14_recursive(buf + 12288, 12);
    for (int j = 0; j < 16384; j += 16384) {
      for (int k = 0; k < 4096; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vmovupd %%ymm0, (%0)\n"
          "vmovupd %%ymm1, (%1)\n"
          "vmovupd %%ymm2, (%2)\n"
          "vmovupd %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096), "r"(buf + j + k + 8192), "r"(buf + j + k + 12288) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_14(double *buf);
void helper_double_14(double *buf) {
  helper_double_14_recursive(buf, 14);
}
void helper_double_15_recursive(double *buf, int depth);
void helper_double_15_recursive(double *buf, int depth) {
  if (depth == 12) {
    for (int j = 0; j < 4096; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 2048) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256), "r"(buf + j + k + 512), "r"(buf + j + k + 768), "r"(buf + j + k + 1024), "r"(buf + j + k + 1280), "r"(buf + j + k + 1536), "r"(buf + j + k + 1792) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 4096) {
      for (int k = 0; k < 2048; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 15) {
    helper_double_15_recursive(buf + 0, 12);
    helper_double_15_recursive(buf + 4096, 12);
    helper_double_15_recursive(buf + 8192, 12);
    helper_double_15_recursive(buf + 12288, 12);
    helper_double_15_recursive(buf + 16384, 12);
    helper_double_15_recursive(buf + 20480, 12);
    helper_double_15_recursive(buf + 24576, 12);
    helper_double_15_recursive(buf + 28672, 12);
    for (int j = 0; j < 32768; j += 32768) {
      for (int k = 0; k < 4096; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096), "r"(buf + j + k + 8192), "r"(buf + j + k + 12288), "r"(buf + j + k + 16384), "r"(buf + j + k + 20480), "r"(buf + j + k + 24576), "r"(buf + j + k + 28672) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_15(double *buf);
void helper_double_15(double *buf) {
  helper_double_15_recursive(buf, 15);
}
void helper_double_16_recursive(double *buf, int depth);
void helper_double_16_recursive(double *buf, int depth) {
  if (depth == 11) {
    for (int j = 0; j < 2048; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 2048) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256), "r"(buf + j + k + 512), "r"(buf + j + k + 768), "r"(buf + j + k + 1024), "r"(buf + j + k + 1280), "r"(buf + j + k + 1536), "r"(buf + j + k + 1792) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 14) {
    helper_double_16_recursive(buf + 0, 11);
    helper_double_16_recursive(buf + 2048, 11);
    helper_double_16_recursive(buf + 4096, 11);
    helper_double_16_recursive(buf + 6144, 11);
    helper_double_16_recursive(buf + 8192, 11);
    helper_double_16_recursive(buf + 10240, 11);
    helper_double_16_recursive(buf + 12288, 11);
    helper_double_16_recursive(buf + 14336, 11);
    for (int j = 0; j < 16384; j += 16384) {
      for (int k = 0; k < 2048; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2048), "r"(buf + j + k + 4096), "r"(buf + j + k + 6144), "r"(buf + j + k + 8192), "r"(buf + j + k + 10240), "r"(buf + j + k + 12288), "r"(buf + j + k + 14336) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 16) {
    helper_double_16_recursive(buf + 0, 14);
    helper_double_16_recursive(buf + 16384, 14);
    helper_double_16_recursive(buf + 32768, 14);
    helper_double_16_recursive(buf + 49152, 14);
    for (int j = 0; j < 65536; j += 65536) {
      for (int k = 0; k < 16384; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vmovupd %%ymm0, (%0)\n"
          "vmovupd %%ymm1, (%1)\n"
          "vmovupd %%ymm2, (%2)\n"
          "vmovupd %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 16384), "r"(buf + j + k + 32768), "r"(buf + j + k + 49152) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_16(double *buf);
void helper_double_16(double *buf) {
  helper_double_16_recursive(buf, 16);
}
void helper_double_17_recursive(double *buf, int depth);
void helper_double_17_recursive(double *buf, int depth) {
  if (depth == 11) {
    for (int j = 0; j < 2048; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 2048) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256), "r"(buf + j + k + 512), "r"(buf + j + k + 768), "r"(buf + j + k + 1024), "r"(buf + j + k + 1280), "r"(buf + j + k + 1536), "r"(buf + j + k + 1792) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 14) {
    helper_double_17_recursive(buf + 0, 11);
    helper_double_17_recursive(buf + 2048, 11);
    helper_double_17_recursive(buf + 4096, 11);
    helper_double_17_recursive(buf + 6144, 11);
    helper_double_17_recursive(buf + 8192, 11);
    helper_double_17_recursive(buf + 10240, 11);
    helper_double_17_recursive(buf + 12288, 11);
    helper_double_17_recursive(buf + 14336, 11);
    for (int j = 0; j < 16384; j += 16384) {
      for (int k = 0; k < 2048; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2048), "r"(buf + j + k + 4096), "r"(buf + j + k + 6144), "r"(buf + j + k + 8192), "r"(buf + j + k + 10240), "r"(buf + j + k + 12288), "r"(buf + j + k + 14336) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 17) {
    helper_double_17_recursive(buf + 0, 14);
    helper_double_17_recursive(buf + 16384, 14);
    helper_double_17_recursive(buf + 32768, 14);
    helper_double_17_recursive(buf + 49152, 14);
    helper_double_17_recursive(buf + 65536, 14);
    helper_double_17_recursive(buf + 81920, 14);
    helper_double_17_recursive(buf + 98304, 14);
    helper_double_17_recursive(buf + 114688, 14);
    for (int j = 0; j < 131072; j += 131072) {
      for (int k = 0; k < 16384; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 16384), "r"(buf + j + k + 32768), "r"(buf + j + k + 49152), "r"(buf + j + k + 65536), "r"(buf + j + k + 81920), "r"(buf + j + k + 98304), "r"(buf + j + k + 114688) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_17(double *buf);
void helper_double_17(double *buf) {
  helper_double_17_recursive(buf, 17);
}
void helper_double_18_recursive(double *buf, int depth);
void helper_double_18_recursive(double *buf, int depth) {
  if (depth == 12) {
    for (int j = 0; j < 4096; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 2048) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256), "r"(buf + j + k + 512), "r"(buf + j + k + 768), "r"(buf + j + k + 1024), "r"(buf + j + k + 1280), "r"(buf + j + k + 1536), "r"(buf + j + k + 1792) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 4096) {
      for (int k = 0; k < 2048; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 15) {
    helper_double_18_recursive(buf + 0, 12);
    helper_double_18_recursive(buf + 4096, 12);
    helper_double_18_recursive(buf + 8192, 12);
    helper_double_18_recursive(buf + 12288, 12);
    helper_double_18_recursive(buf + 16384, 12);
    helper_double_18_recursive(buf + 20480, 12);
    helper_double_18_recursive(buf + 24576, 12);
    helper_double_18_recursive(buf + 28672, 12);
    for (int j = 0; j < 32768; j += 32768) {
      for (int k = 0; k < 4096; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096), "r"(buf + j + k + 8192), "r"(buf + j + k + 12288), "r"(buf + j + k + 16384), "r"(buf + j + k + 20480), "r"(buf + j + k + 24576), "r"(buf + j + k + 28672) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 18) {
    helper_double_18_recursive(buf + 0, 15);
    helper_double_18_recursive(buf + 32768, 15);
    helper_double_18_recursive(buf + 65536, 15);
    helper_double_18_recursive(buf + 98304, 15);
    helper_double_18_recursive(buf + 131072, 15);
    helper_double_18_recursive(buf + 163840, 15);
    helper_double_18_recursive(buf + 196608, 15);
    helper_double_18_recursive(buf + 229376, 15);
    for (int j = 0; j < 262144; j += 262144) {
      for (int k = 0; k < 32768; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32768), "r"(buf + j + k + 65536), "r"(buf + j + k + 98304), "r"(buf + j + k + 131072), "r"(buf + j + k + 163840), "r"(buf + j + k + 196608), "r"(buf + j + k + 229376) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_18(double *buf);
void helper_double_18(double *buf) {
  helper_double_18_recursive(buf, 18);
}
void helper_double_19_recursive(double *buf, int depth);
void helper_double_19_recursive(double *buf, int depth) {
  if (depth == 11) {
    for (int j = 0; j < 2048; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 2048) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256), "r"(buf + j + k + 512), "r"(buf + j + k + 768), "r"(buf + j + k + 1024), "r"(buf + j + k + 1280), "r"(buf + j + k + 1536), "r"(buf + j + k + 1792) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 14) {
    helper_double_19_recursive(buf + 0, 11);
    helper_double_19_recursive(buf + 2048, 11);
    helper_double_19_recursive(buf + 4096, 11);
    helper_double_19_recursive(buf + 6144, 11);
    helper_double_19_recursive(buf + 8192, 11);
    helper_double_19_recursive(buf + 10240, 11);
    helper_double_19_recursive(buf + 12288, 11);
    helper_double_19_recursive(buf + 14336, 11);
    for (int j = 0; j < 16384; j += 16384) {
      for (int k = 0; k < 2048; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2048), "r"(buf + j + k + 4096), "r"(buf + j + k + 6144), "r"(buf + j + k + 8192), "r"(buf + j + k + 10240), "r"(buf + j + k + 12288), "r"(buf + j + k + 14336) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 17) {
    helper_double_19_recursive(buf + 0, 14);
    helper_double_19_recursive(buf + 16384, 14);
    helper_double_19_recursive(buf + 32768, 14);
    helper_double_19_recursive(buf + 49152, 14);
    helper_double_19_recursive(buf + 65536, 14);
    helper_double_19_recursive(buf + 81920, 14);
    helper_double_19_recursive(buf + 98304, 14);
    helper_double_19_recursive(buf + 114688, 14);
    for (int j = 0; j < 131072; j += 131072) {
      for (int k = 0; k < 16384; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 16384), "r"(buf + j + k + 32768), "r"(buf + j + k + 49152), "r"(buf + j + k + 65536), "r"(buf + j + k + 81920), "r"(buf + j + k + 98304), "r"(buf + j + k + 114688) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 19) {
    helper_double_19_recursive(buf + 0, 17);
    helper_double_19_recursive(buf + 131072, 17);
    helper_double_19_recursive(buf + 262144, 17);
    helper_double_19_recursive(buf + 393216, 17);
    for (int j = 0; j < 524288; j += 524288) {
      for (int k = 0; k < 131072; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vmovupd %%ymm0, (%0)\n"
          "vmovupd %%ymm1, (%1)\n"
          "vmovupd %%ymm2, (%2)\n"
          "vmovupd %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 131072), "r"(buf + j + k + 262144), "r"(buf + j + k + 393216) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_19(double *buf);
void helper_double_19(double *buf) {
  helper_double_19_recursive(buf, 19);
}
void helper_double_20_recursive(double *buf, int depth);
void helper_double_20_recursive(double *buf, int depth) {
  if (depth == 12) {
    for (int j = 0; j < 4096; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 2048) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256), "r"(buf + j + k + 512), "r"(buf + j + k + 768), "r"(buf + j + k + 1024), "r"(buf + j + k + 1280), "r"(buf + j + k + 1536), "r"(buf + j + k + 1792) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 4096; j += 4096) {
      for (int k = 0; k < 2048; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 15) {
    helper_double_20_recursive(buf + 0, 12);
    helper_double_20_recursive(buf + 4096, 12);
    helper_double_20_recursive(buf + 8192, 12);
    helper_double_20_recursive(buf + 12288, 12);
    helper_double_20_recursive(buf + 16384, 12);
    helper_double_20_recursive(buf + 20480, 12);
    helper_double_20_recursive(buf + 24576, 12);
    helper_double_20_recursive(buf + 28672, 12);
    for (int j = 0; j < 32768; j += 32768) {
      for (int k = 0; k < 4096; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096), "r"(buf + j + k + 8192), "r"(buf + j + k + 12288), "r"(buf + j + k + 16384), "r"(buf + j + k + 20480), "r"(buf + j + k + 24576), "r"(buf + j + k + 28672) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 18) {
    helper_double_20_recursive(buf + 0, 15);
    helper_double_20_recursive(buf + 32768, 15);
    helper_double_20_recursive(buf + 65536, 15);
    helper_double_20_recursive(buf + 98304, 15);
    helper_double_20_recursive(buf + 131072, 15);
    helper_double_20_recursive(buf + 163840, 15);
    helper_double_20_recursive(buf + 196608, 15);
    helper_double_20_recursive(buf + 229376, 15);
    for (int j = 0; j < 262144; j += 262144) {
      for (int k = 0; k < 32768; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32768), "r"(buf + j + k + 65536), "r"(buf + j + k + 98304), "r"(buf + j + k + 131072), "r"(buf + j + k + 163840), "r"(buf + j + k + 196608), "r"(buf + j + k + 229376) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 20) {
    helper_double_20_recursive(buf + 0, 18);
    helper_double_20_recursive(buf + 262144, 18);
    helper_double_20_recursive(buf + 524288, 18);
    helper_double_20_recursive(buf + 786432, 18);
    for (int j = 0; j < 1048576; j += 1048576) {
      for (int k = 0; k < 262144; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vmovupd %%ymm0, (%0)\n"
          "vmovupd %%ymm1, (%1)\n"
          "vmovupd %%ymm2, (%2)\n"
          "vmovupd %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 262144), "r"(buf + j + k + 524288), "r"(buf + j + k + 786432) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_20(double *buf);
void helper_double_20(double *buf) {
  helper_double_20_recursive(buf, 20);
}
void helper_double_21_recursive(double *buf, int depth);
void helper_double_21_recursive(double *buf, int depth) {
  if (depth == 7) {
    for (int j = 0; j < 128; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 128; j += 128) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vmovupd %%ymm0, (%0)\n"
          "vmovupd %%ymm1, (%1)\n"
          "vmovupd %%ymm2, (%2)\n"
          "vmovupd %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 10) {
    helper_double_21_recursive(buf + 0, 7);
    helper_double_21_recursive(buf + 128, 7);
    helper_double_21_recursive(buf + 256, 7);
    helper_double_21_recursive(buf + 384, 7);
    helper_double_21_recursive(buf + 512, 7);
    helper_double_21_recursive(buf + 640, 7);
    helper_double_21_recursive(buf + 768, 7);
    helper_double_21_recursive(buf + 896, 7);
    for (int j = 0; j < 1024; j += 1024) {
      for (int k = 0; k < 128; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 128), "r"(buf + j + k + 256), "r"(buf + j + k + 384), "r"(buf + j + k + 512), "r"(buf + j + k + 640), "r"(buf + j + k + 768), "r"(buf + j + k + 896) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 13) {
    helper_double_21_recursive(buf + 0, 10);
    helper_double_21_recursive(buf + 1024, 10);
    helper_double_21_recursive(buf + 2048, 10);
    helper_double_21_recursive(buf + 3072, 10);
    helper_double_21_recursive(buf + 4096, 10);
    helper_double_21_recursive(buf + 5120, 10);
    helper_double_21_recursive(buf + 6144, 10);
    helper_double_21_recursive(buf + 7168, 10);
    for (int j = 0; j < 8192; j += 8192) {
      for (int k = 0; k < 1024; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 1024), "r"(buf + j + k + 2048), "r"(buf + j + k + 3072), "r"(buf + j + k + 4096), "r"(buf + j + k + 5120), "r"(buf + j + k + 6144), "r"(buf + j + k + 7168) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 16) {
    helper_double_21_recursive(buf + 0, 13);
    helper_double_21_recursive(buf + 8192, 13);
    helper_double_21_recursive(buf + 16384, 13);
    helper_double_21_recursive(buf + 24576, 13);
    helper_double_21_recursive(buf + 32768, 13);
    helper_double_21_recursive(buf + 40960, 13);
    helper_double_21_recursive(buf + 49152, 13);
    helper_double_21_recursive(buf + 57344, 13);
    for (int j = 0; j < 65536; j += 65536) {
      for (int k = 0; k < 8192; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8192), "r"(buf + j + k + 16384), "r"(buf + j + k + 24576), "r"(buf + j + k + 32768), "r"(buf + j + k + 40960), "r"(buf + j + k + 49152), "r"(buf + j + k + 57344) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 19) {
    helper_double_21_recursive(buf + 0, 16);
    helper_double_21_recursive(buf + 65536, 16);
    helper_double_21_recursive(buf + 131072, 16);
    helper_double_21_recursive(buf + 196608, 16);
    helper_double_21_recursive(buf + 262144, 16);
    helper_double_21_recursive(buf + 327680, 16);
    helper_double_21_recursive(buf + 393216, 16);
    helper_double_21_recursive(buf + 458752, 16);
    for (int j = 0; j < 524288; j += 524288) {
      for (int k = 0; k < 65536; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 65536), "r"(buf + j + k + 131072), "r"(buf + j + k + 196608), "r"(buf + j + k + 262144), "r"(buf + j + k + 327680), "r"(buf + j + k + 393216), "r"(buf + j + k + 458752) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 21) {
    helper_double_21_recursive(buf + 0, 19);
    helper_double_21_recursive(buf + 524288, 19);
    helper_double_21_recursive(buf + 1048576, 19);
    helper_double_21_recursive(buf + 1572864, 19);
    for (int j = 0; j < 2097152; j += 2097152) {
      for (int k = 0; k < 524288; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vmovupd %%ymm0, (%0)\n"
          "vmovupd %%ymm1, (%1)\n"
          "vmovupd %%ymm2, (%2)\n"
          "vmovupd %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 524288), "r"(buf + j + k + 1048576), "r"(buf + j + k + 1572864) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_21(double *buf);
void helper_double_21(double *buf) {
  helper_double_21_recursive(buf, 21);
}
void helper_double_22_recursive(double *buf, int depth);
void helper_double_22_recursive(double *buf, int depth) {
  if (depth == 11) {
    for (int j = 0; j < 2048; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 2048) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256), "r"(buf + j + k + 512), "r"(buf + j + k + 768), "r"(buf + j + k + 1024), "r"(buf + j + k + 1280), "r"(buf + j + k + 1536), "r"(buf + j + k + 1792) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 14) {
    helper_double_22_recursive(buf + 0, 11);
    helper_double_22_recursive(buf + 2048, 11);
    helper_double_22_recursive(buf + 4096, 11);
    helper_double_22_recursive(buf + 6144, 11);
    helper_double_22_recursive(buf + 8192, 11);
    helper_double_22_recursive(buf + 10240, 11);
    helper_double_22_recursive(buf + 12288, 11);
    helper_double_22_recursive(buf + 14336, 11);
    for (int j = 0; j < 16384; j += 16384) {
      for (int k = 0; k < 2048; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2048), "r"(buf + j + k + 4096), "r"(buf + j + k + 6144), "r"(buf + j + k + 8192), "r"(buf + j + k + 10240), "r"(buf + j + k + 12288), "r"(buf + j + k + 14336) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 17) {
    helper_double_22_recursive(buf + 0, 14);
    helper_double_22_recursive(buf + 16384, 14);
    helper_double_22_recursive(buf + 32768, 14);
    helper_double_22_recursive(buf + 49152, 14);
    helper_double_22_recursive(buf + 65536, 14);
    helper_double_22_recursive(buf + 81920, 14);
    helper_double_22_recursive(buf + 98304, 14);
    helper_double_22_recursive(buf + 114688, 14);
    for (int j = 0; j < 131072; j += 131072) {
      for (int k = 0; k < 16384; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 16384), "r"(buf + j + k + 32768), "r"(buf + j + k + 49152), "r"(buf + j + k + 65536), "r"(buf + j + k + 81920), "r"(buf + j + k + 98304), "r"(buf + j + k + 114688) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 20) {
    helper_double_22_recursive(buf + 0, 17);
    helper_double_22_recursive(buf + 131072, 17);
    helper_double_22_recursive(buf + 262144, 17);
    helper_double_22_recursive(buf + 393216, 17);
    helper_double_22_recursive(buf + 524288, 17);
    helper_double_22_recursive(buf + 655360, 17);
    helper_double_22_recursive(buf + 786432, 17);
    helper_double_22_recursive(buf + 917504, 17);
    for (int j = 0; j < 1048576; j += 1048576) {
      for (int k = 0; k < 131072; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 131072), "r"(buf + j + k + 262144), "r"(buf + j + k + 393216), "r"(buf + j + k + 524288), "r"(buf + j + k + 655360), "r"(buf + j + k + 786432), "r"(buf + j + k + 917504) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 22) {
    helper_double_22_recursive(buf + 0, 20);
    helper_double_22_recursive(buf + 1048576, 20);
    helper_double_22_recursive(buf + 2097152, 20);
    helper_double_22_recursive(buf + 3145728, 20);
    for (int j = 0; j < 4194304; j += 4194304) {
      for (int k = 0; k < 1048576; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vmovupd %%ymm0, (%0)\n"
          "vmovupd %%ymm1, (%1)\n"
          "vmovupd %%ymm2, (%2)\n"
          "vmovupd %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 1048576), "r"(buf + j + k + 2097152), "r"(buf + j + k + 3145728) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_22(double *buf);
void helper_double_22(double *buf) {
  helper_double_22_recursive(buf, 22);
}
void helper_double_23_recursive(double *buf, int depth);
void helper_double_23_recursive(double *buf, int depth) {
  if (depth == 8) {
    for (int j = 0; j < 256; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 256; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 11) {
    helper_double_23_recursive(buf + 0, 8);
    helper_double_23_recursive(buf + 256, 8);
    helper_double_23_recursive(buf + 512, 8);
    helper_double_23_recursive(buf + 768, 8);
    helper_double_23_recursive(buf + 1024, 8);
    helper_double_23_recursive(buf + 1280, 8);
    helper_double_23_recursive(buf + 1536, 8);
    helper_double_23_recursive(buf + 1792, 8);
    for (int j = 0; j < 2048; j += 2048) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256), "r"(buf + j + k + 512), "r"(buf + j + k + 768), "r"(buf + j + k + 1024), "r"(buf + j + k + 1280), "r"(buf + j + k + 1536), "r"(buf + j + k + 1792) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 14) {
    helper_double_23_recursive(buf + 0, 11);
    helper_double_23_recursive(buf + 2048, 11);
    helper_double_23_recursive(buf + 4096, 11);
    helper_double_23_recursive(buf + 6144, 11);
    helper_double_23_recursive(buf + 8192, 11);
    helper_double_23_recursive(buf + 10240, 11);
    helper_double_23_recursive(buf + 12288, 11);
    helper_double_23_recursive(buf + 14336, 11);
    for (int j = 0; j < 16384; j += 16384) {
      for (int k = 0; k < 2048; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2048), "r"(buf + j + k + 4096), "r"(buf + j + k + 6144), "r"(buf + j + k + 8192), "r"(buf + j + k + 10240), "r"(buf + j + k + 12288), "r"(buf + j + k + 14336) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 17) {
    helper_double_23_recursive(buf + 0, 14);
    helper_double_23_recursive(buf + 16384, 14);
    helper_double_23_recursive(buf + 32768, 14);
    helper_double_23_recursive(buf + 49152, 14);
    helper_double_23_recursive(buf + 65536, 14);
    helper_double_23_recursive(buf + 81920, 14);
    helper_double_23_recursive(buf + 98304, 14);
    helper_double_23_recursive(buf + 114688, 14);
    for (int j = 0; j < 131072; j += 131072) {
      for (int k = 0; k < 16384; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 16384), "r"(buf + j + k + 32768), "r"(buf + j + k + 49152), "r"(buf + j + k + 65536), "r"(buf + j + k + 81920), "r"(buf + j + k + 98304), "r"(buf + j + k + 114688) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 20) {
    helper_double_23_recursive(buf + 0, 17);
    helper_double_23_recursive(buf + 131072, 17);
    helper_double_23_recursive(buf + 262144, 17);
    helper_double_23_recursive(buf + 393216, 17);
    helper_double_23_recursive(buf + 524288, 17);
    helper_double_23_recursive(buf + 655360, 17);
    helper_double_23_recursive(buf + 786432, 17);
    helper_double_23_recursive(buf + 917504, 17);
    for (int j = 0; j < 1048576; j += 1048576) {
      for (int k = 0; k < 131072; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 131072), "r"(buf + j + k + 262144), "r"(buf + j + k + 393216), "r"(buf + j + k + 524288), "r"(buf + j + k + 655360), "r"(buf + j + k + 786432), "r"(buf + j + k + 917504) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 23) {
    helper_double_23_recursive(buf + 0, 20);
    helper_double_23_recursive(buf + 1048576, 20);
    helper_double_23_recursive(buf + 2097152, 20);
    helper_double_23_recursive(buf + 3145728, 20);
    helper_double_23_recursive(buf + 4194304, 20);
    helper_double_23_recursive(buf + 5242880, 20);
    helper_double_23_recursive(buf + 6291456, 20);
    helper_double_23_recursive(buf + 7340032, 20);
    for (int j = 0; j < 8388608; j += 8388608) {
      for (int k = 0; k < 1048576; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 1048576), "r"(buf + j + k + 2097152), "r"(buf + j + k + 3145728), "r"(buf + j + k + 4194304), "r"(buf + j + k + 5242880), "r"(buf + j + k + 6291456), "r"(buf + j + k + 7340032) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_23(double *buf);
void helper_double_23(double *buf) {
  helper_double_23_recursive(buf, 23);
}
void helper_double_24_recursive(double *buf, int depth);
void helper_double_24_recursive(double *buf, int depth) {
  if (depth == 9) {
    for (int j = 0; j < 512; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 512; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 512; j += 512) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 12) {
    helper_double_24_recursive(buf + 0, 9);
    helper_double_24_recursive(buf + 512, 9);
    helper_double_24_recursive(buf + 1024, 9);
    helper_double_24_recursive(buf + 1536, 9);
    helper_double_24_recursive(buf + 2048, 9);
    helper_double_24_recursive(buf + 2560, 9);
    helper_double_24_recursive(buf + 3072, 9);
    helper_double_24_recursive(buf + 3584, 9);
    for (int j = 0; j < 4096; j += 4096) {
      for (int k = 0; k < 512; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 15) {
    helper_double_24_recursive(buf + 0, 12);
    helper_double_24_recursive(buf + 4096, 12);
    helper_double_24_recursive(buf + 8192, 12);
    helper_double_24_recursive(buf + 12288, 12);
    helper_double_24_recursive(buf + 16384, 12);
    helper_double_24_recursive(buf + 20480, 12);
    helper_double_24_recursive(buf + 24576, 12);
    helper_double_24_recursive(buf + 28672, 12);
    for (int j = 0; j < 32768; j += 32768) {
      for (int k = 0; k < 4096; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096), "r"(buf + j + k + 8192), "r"(buf + j + k + 12288), "r"(buf + j + k + 16384), "r"(buf + j + k + 20480), "r"(buf + j + k + 24576), "r"(buf + j + k + 28672) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 18) {
    helper_double_24_recursive(buf + 0, 15);
    helper_double_24_recursive(buf + 32768, 15);
    helper_double_24_recursive(buf + 65536, 15);
    helper_double_24_recursive(buf + 98304, 15);
    helper_double_24_recursive(buf + 131072, 15);
    helper_double_24_recursive(buf + 163840, 15);
    helper_double_24_recursive(buf + 196608, 15);
    helper_double_24_recursive(buf + 229376, 15);
    for (int j = 0; j < 262144; j += 262144) {
      for (int k = 0; k < 32768; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32768), "r"(buf + j + k + 65536), "r"(buf + j + k + 98304), "r"(buf + j + k + 131072), "r"(buf + j + k + 163840), "r"(buf + j + k + 196608), "r"(buf + j + k + 229376) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 21) {
    helper_double_24_recursive(buf + 0, 18);
    helper_double_24_recursive(buf + 262144, 18);
    helper_double_24_recursive(buf + 524288, 18);
    helper_double_24_recursive(buf + 786432, 18);
    helper_double_24_recursive(buf + 1048576, 18);
    helper_double_24_recursive(buf + 1310720, 18);
    helper_double_24_recursive(buf + 1572864, 18);
    helper_double_24_recursive(buf + 1835008, 18);
    for (int j = 0; j < 2097152; j += 2097152) {
      for (int k = 0; k < 262144; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 262144), "r"(buf + j + k + 524288), "r"(buf + j + k + 786432), "r"(buf + j + k + 1048576), "r"(buf + j + k + 1310720), "r"(buf + j + k + 1572864), "r"(buf + j + k + 1835008) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 24) {
    helper_double_24_recursive(buf + 0, 21);
    helper_double_24_recursive(buf + 2097152, 21);
    helper_double_24_recursive(buf + 4194304, 21);
    helper_double_24_recursive(buf + 6291456, 21);
    helper_double_24_recursive(buf + 8388608, 21);
    helper_double_24_recursive(buf + 10485760, 21);
    helper_double_24_recursive(buf + 12582912, 21);
    helper_double_24_recursive(buf + 14680064, 21);
    for (int j = 0; j < 16777216; j += 16777216) {
      for (int k = 0; k < 2097152; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2097152), "r"(buf + j + k + 4194304), "r"(buf + j + k + 6291456), "r"(buf + j + k + 8388608), "r"(buf + j + k + 10485760), "r"(buf + j + k + 12582912), "r"(buf + j + k + 14680064) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_24(double *buf);
void helper_double_24(double *buf) {
  helper_double_24_recursive(buf, 24);
}
void helper_double_25_recursive(double *buf, int depth);
void helper_double_25_recursive(double *buf, int depth) {
  if (depth == 10) {
    for (int j = 0; j < 1024; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 1024; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 1024; j += 1024) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vmovupd %%ymm0, (%0)\n"
          "vmovupd %%ymm1, (%1)\n"
          "vmovupd %%ymm2, (%2)\n"
          "vmovupd %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256), "r"(buf + j + k + 512), "r"(buf + j + k + 768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 13) {
    helper_double_25_recursive(buf + 0, 10);
    helper_double_25_recursive(buf + 1024, 10);
    helper_double_25_recursive(buf + 2048, 10);
    helper_double_25_recursive(buf + 3072, 10);
    helper_double_25_recursive(buf + 4096, 10);
    helper_double_25_recursive(buf + 5120, 10);
    helper_double_25_recursive(buf + 6144, 10);
    helper_double_25_recursive(buf + 7168, 10);
    for (int j = 0; j < 8192; j += 8192) {
      for (int k = 0; k < 1024; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 1024), "r"(buf + j + k + 2048), "r"(buf + j + k + 3072), "r"(buf + j + k + 4096), "r"(buf + j + k + 5120), "r"(buf + j + k + 6144), "r"(buf + j + k + 7168) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 16) {
    helper_double_25_recursive(buf + 0, 13);
    helper_double_25_recursive(buf + 8192, 13);
    helper_double_25_recursive(buf + 16384, 13);
    helper_double_25_recursive(buf + 24576, 13);
    helper_double_25_recursive(buf + 32768, 13);
    helper_double_25_recursive(buf + 40960, 13);
    helper_double_25_recursive(buf + 49152, 13);
    helper_double_25_recursive(buf + 57344, 13);
    for (int j = 0; j < 65536; j += 65536) {
      for (int k = 0; k < 8192; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8192), "r"(buf + j + k + 16384), "r"(buf + j + k + 24576), "r"(buf + j + k + 32768), "r"(buf + j + k + 40960), "r"(buf + j + k + 49152), "r"(buf + j + k + 57344) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 19) {
    helper_double_25_recursive(buf + 0, 16);
    helper_double_25_recursive(buf + 65536, 16);
    helper_double_25_recursive(buf + 131072, 16);
    helper_double_25_recursive(buf + 196608, 16);
    helper_double_25_recursive(buf + 262144, 16);
    helper_double_25_recursive(buf + 327680, 16);
    helper_double_25_recursive(buf + 393216, 16);
    helper_double_25_recursive(buf + 458752, 16);
    for (int j = 0; j < 524288; j += 524288) {
      for (int k = 0; k < 65536; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 65536), "r"(buf + j + k + 131072), "r"(buf + j + k + 196608), "r"(buf + j + k + 262144), "r"(buf + j + k + 327680), "r"(buf + j + k + 393216), "r"(buf + j + k + 458752) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 22) {
    helper_double_25_recursive(buf + 0, 19);
    helper_double_25_recursive(buf + 524288, 19);
    helper_double_25_recursive(buf + 1048576, 19);
    helper_double_25_recursive(buf + 1572864, 19);
    helper_double_25_recursive(buf + 2097152, 19);
    helper_double_25_recursive(buf + 2621440, 19);
    helper_double_25_recursive(buf + 3145728, 19);
    helper_double_25_recursive(buf + 3670016, 19);
    for (int j = 0; j < 4194304; j += 4194304) {
      for (int k = 0; k < 524288; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 524288), "r"(buf + j + k + 1048576), "r"(buf + j + k + 1572864), "r"(buf + j + k + 2097152), "r"(buf + j + k + 2621440), "r"(buf + j + k + 3145728), "r"(buf + j + k + 3670016) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 25) {
    helper_double_25_recursive(buf + 0, 22);
    helper_double_25_recursive(buf + 4194304, 22);
    helper_double_25_recursive(buf + 8388608, 22);
    helper_double_25_recursive(buf + 12582912, 22);
    helper_double_25_recursive(buf + 16777216, 22);
    helper_double_25_recursive(buf + 20971520, 22);
    helper_double_25_recursive(buf + 25165824, 22);
    helper_double_25_recursive(buf + 29360128, 22);
    for (int j = 0; j < 33554432; j += 33554432) {
      for (int k = 0; k < 4194304; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4194304), "r"(buf + j + k + 8388608), "r"(buf + j + k + 12582912), "r"(buf + j + k + 16777216), "r"(buf + j + k + 20971520), "r"(buf + j + k + 25165824), "r"(buf + j + k + 29360128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_25(double *buf);
void helper_double_25(double *buf) {
  helper_double_25_recursive(buf, 25);
}
void helper_double_26_recursive(double *buf, int depth);
void helper_double_26_recursive(double *buf, int depth) {
  if (depth == 11) {
    for (int j = 0; j < 2048; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 2048) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256), "r"(buf + j + k + 512), "r"(buf + j + k + 768), "r"(buf + j + k + 1024), "r"(buf + j + k + 1280), "r"(buf + j + k + 1536), "r"(buf + j + k + 1792) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 14) {
    helper_double_26_recursive(buf + 0, 11);
    helper_double_26_recursive(buf + 2048, 11);
    helper_double_26_recursive(buf + 4096, 11);
    helper_double_26_recursive(buf + 6144, 11);
    helper_double_26_recursive(buf + 8192, 11);
    helper_double_26_recursive(buf + 10240, 11);
    helper_double_26_recursive(buf + 12288, 11);
    helper_double_26_recursive(buf + 14336, 11);
    for (int j = 0; j < 16384; j += 16384) {
      for (int k = 0; k < 2048; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2048), "r"(buf + j + k + 4096), "r"(buf + j + k + 6144), "r"(buf + j + k + 8192), "r"(buf + j + k + 10240), "r"(buf + j + k + 12288), "r"(buf + j + k + 14336) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 17) {
    helper_double_26_recursive(buf + 0, 14);
    helper_double_26_recursive(buf + 16384, 14);
    helper_double_26_recursive(buf + 32768, 14);
    helper_double_26_recursive(buf + 49152, 14);
    helper_double_26_recursive(buf + 65536, 14);
    helper_double_26_recursive(buf + 81920, 14);
    helper_double_26_recursive(buf + 98304, 14);
    helper_double_26_recursive(buf + 114688, 14);
    for (int j = 0; j < 131072; j += 131072) {
      for (int k = 0; k < 16384; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 16384), "r"(buf + j + k + 32768), "r"(buf + j + k + 49152), "r"(buf + j + k + 65536), "r"(buf + j + k + 81920), "r"(buf + j + k + 98304), "r"(buf + j + k + 114688) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 20) {
    helper_double_26_recursive(buf + 0, 17);
    helper_double_26_recursive(buf + 131072, 17);
    helper_double_26_recursive(buf + 262144, 17);
    helper_double_26_recursive(buf + 393216, 17);
    helper_double_26_recursive(buf + 524288, 17);
    helper_double_26_recursive(buf + 655360, 17);
    helper_double_26_recursive(buf + 786432, 17);
    helper_double_26_recursive(buf + 917504, 17);
    for (int j = 0; j < 1048576; j += 1048576) {
      for (int k = 0; k < 131072; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 131072), "r"(buf + j + k + 262144), "r"(buf + j + k + 393216), "r"(buf + j + k + 524288), "r"(buf + j + k + 655360), "r"(buf + j + k + 786432), "r"(buf + j + k + 917504) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 23) {
    helper_double_26_recursive(buf + 0, 20);
    helper_double_26_recursive(buf + 1048576, 20);
    helper_double_26_recursive(buf + 2097152, 20);
    helper_double_26_recursive(buf + 3145728, 20);
    helper_double_26_recursive(buf + 4194304, 20);
    helper_double_26_recursive(buf + 5242880, 20);
    helper_double_26_recursive(buf + 6291456, 20);
    helper_double_26_recursive(buf + 7340032, 20);
    for (int j = 0; j < 8388608; j += 8388608) {
      for (int k = 0; k < 1048576; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 1048576), "r"(buf + j + k + 2097152), "r"(buf + j + k + 3145728), "r"(buf + j + k + 4194304), "r"(buf + j + k + 5242880), "r"(buf + j + k + 6291456), "r"(buf + j + k + 7340032) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 26) {
    helper_double_26_recursive(buf + 0, 23);
    helper_double_26_recursive(buf + 8388608, 23);
    helper_double_26_recursive(buf + 16777216, 23);
    helper_double_26_recursive(buf + 25165824, 23);
    helper_double_26_recursive(buf + 33554432, 23);
    helper_double_26_recursive(buf + 41943040, 23);
    helper_double_26_recursive(buf + 50331648, 23);
    helper_double_26_recursive(buf + 58720256, 23);
    for (int j = 0; j < 67108864; j += 67108864) {
      for (int k = 0; k < 8388608; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8388608), "r"(buf + j + k + 16777216), "r"(buf + j + k + 25165824), "r"(buf + j + k + 33554432), "r"(buf + j + k + 41943040), "r"(buf + j + k + 50331648), "r"(buf + j + k + 58720256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_26(double *buf);
void helper_double_26(double *buf) {
  helper_double_26_recursive(buf, 26);
}
void helper_double_27_recursive(double *buf, int depth);
void helper_double_27_recursive(double *buf, int depth) {
  if (depth == 9) {
    for (int j = 0; j < 512; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 512; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 512; j += 512) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 12) {
    helper_double_27_recursive(buf + 0, 9);
    helper_double_27_recursive(buf + 512, 9);
    helper_double_27_recursive(buf + 1024, 9);
    helper_double_27_recursive(buf + 1536, 9);
    helper_double_27_recursive(buf + 2048, 9);
    helper_double_27_recursive(buf + 2560, 9);
    helper_double_27_recursive(buf + 3072, 9);
    helper_double_27_recursive(buf + 3584, 9);
    for (int j = 0; j < 4096; j += 4096) {
      for (int k = 0; k < 512; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 15) {
    helper_double_27_recursive(buf + 0, 12);
    helper_double_27_recursive(buf + 4096, 12);
    helper_double_27_recursive(buf + 8192, 12);
    helper_double_27_recursive(buf + 12288, 12);
    helper_double_27_recursive(buf + 16384, 12);
    helper_double_27_recursive(buf + 20480, 12);
    helper_double_27_recursive(buf + 24576, 12);
    helper_double_27_recursive(buf + 28672, 12);
    for (int j = 0; j < 32768; j += 32768) {
      for (int k = 0; k < 4096; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096), "r"(buf + j + k + 8192), "r"(buf + j + k + 12288), "r"(buf + j + k + 16384), "r"(buf + j + k + 20480), "r"(buf + j + k + 24576), "r"(buf + j + k + 28672) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 18) {
    helper_double_27_recursive(buf + 0, 15);
    helper_double_27_recursive(buf + 32768, 15);
    helper_double_27_recursive(buf + 65536, 15);
    helper_double_27_recursive(buf + 98304, 15);
    helper_double_27_recursive(buf + 131072, 15);
    helper_double_27_recursive(buf + 163840, 15);
    helper_double_27_recursive(buf + 196608, 15);
    helper_double_27_recursive(buf + 229376, 15);
    for (int j = 0; j < 262144; j += 262144) {
      for (int k = 0; k < 32768; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32768), "r"(buf + j + k + 65536), "r"(buf + j + k + 98304), "r"(buf + j + k + 131072), "r"(buf + j + k + 163840), "r"(buf + j + k + 196608), "r"(buf + j + k + 229376) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 21) {
    helper_double_27_recursive(buf + 0, 18);
    helper_double_27_recursive(buf + 262144, 18);
    helper_double_27_recursive(buf + 524288, 18);
    helper_double_27_recursive(buf + 786432, 18);
    helper_double_27_recursive(buf + 1048576, 18);
    helper_double_27_recursive(buf + 1310720, 18);
    helper_double_27_recursive(buf + 1572864, 18);
    helper_double_27_recursive(buf + 1835008, 18);
    for (int j = 0; j < 2097152; j += 2097152) {
      for (int k = 0; k < 262144; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 262144), "r"(buf + j + k + 524288), "r"(buf + j + k + 786432), "r"(buf + j + k + 1048576), "r"(buf + j + k + 1310720), "r"(buf + j + k + 1572864), "r"(buf + j + k + 1835008) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 24) {
    helper_double_27_recursive(buf + 0, 21);
    helper_double_27_recursive(buf + 2097152, 21);
    helper_double_27_recursive(buf + 4194304, 21);
    helper_double_27_recursive(buf + 6291456, 21);
    helper_double_27_recursive(buf + 8388608, 21);
    helper_double_27_recursive(buf + 10485760, 21);
    helper_double_27_recursive(buf + 12582912, 21);
    helper_double_27_recursive(buf + 14680064, 21);
    for (int j = 0; j < 16777216; j += 16777216) {
      for (int k = 0; k < 2097152; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2097152), "r"(buf + j + k + 4194304), "r"(buf + j + k + 6291456), "r"(buf + j + k + 8388608), "r"(buf + j + k + 10485760), "r"(buf + j + k + 12582912), "r"(buf + j + k + 14680064) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 27) {
    helper_double_27_recursive(buf + 0, 24);
    helper_double_27_recursive(buf + 16777216, 24);
    helper_double_27_recursive(buf + 33554432, 24);
    helper_double_27_recursive(buf + 50331648, 24);
    helper_double_27_recursive(buf + 67108864, 24);
    helper_double_27_recursive(buf + 83886080, 24);
    helper_double_27_recursive(buf + 100663296, 24);
    helper_double_27_recursive(buf + 117440512, 24);
    for (int j = 0; j < 134217728; j += 134217728) {
      for (int k = 0; k < 16777216; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 16777216), "r"(buf + j + k + 33554432), "r"(buf + j + k + 50331648), "r"(buf + j + k + 67108864), "r"(buf + j + k + 83886080), "r"(buf + j + k + 100663296), "r"(buf + j + k + 117440512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_27(double *buf);
void helper_double_27(double *buf) {
  helper_double_27_recursive(buf, 27);
}
void helper_double_28_recursive(double *buf, int depth);
void helper_double_28_recursive(double *buf, int depth) {
  if (depth == 10) {
    for (int j = 0; j < 1024; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 1024; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 1024; j += 1024) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vmovupd %%ymm0, (%0)\n"
          "vmovupd %%ymm1, (%1)\n"
          "vmovupd %%ymm2, (%2)\n"
          "vmovupd %%ymm3, (%3)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256), "r"(buf + j + k + 512), "r"(buf + j + k + 768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 13) {
    helper_double_28_recursive(buf + 0, 10);
    helper_double_28_recursive(buf + 1024, 10);
    helper_double_28_recursive(buf + 2048, 10);
    helper_double_28_recursive(buf + 3072, 10);
    helper_double_28_recursive(buf + 4096, 10);
    helper_double_28_recursive(buf + 5120, 10);
    helper_double_28_recursive(buf + 6144, 10);
    helper_double_28_recursive(buf + 7168, 10);
    for (int j = 0; j < 8192; j += 8192) {
      for (int k = 0; k < 1024; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 1024), "r"(buf + j + k + 2048), "r"(buf + j + k + 3072), "r"(buf + j + k + 4096), "r"(buf + j + k + 5120), "r"(buf + j + k + 6144), "r"(buf + j + k + 7168) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 16) {
    helper_double_28_recursive(buf + 0, 13);
    helper_double_28_recursive(buf + 8192, 13);
    helper_double_28_recursive(buf + 16384, 13);
    helper_double_28_recursive(buf + 24576, 13);
    helper_double_28_recursive(buf + 32768, 13);
    helper_double_28_recursive(buf + 40960, 13);
    helper_double_28_recursive(buf + 49152, 13);
    helper_double_28_recursive(buf + 57344, 13);
    for (int j = 0; j < 65536; j += 65536) {
      for (int k = 0; k < 8192; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8192), "r"(buf + j + k + 16384), "r"(buf + j + k + 24576), "r"(buf + j + k + 32768), "r"(buf + j + k + 40960), "r"(buf + j + k + 49152), "r"(buf + j + k + 57344) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 19) {
    helper_double_28_recursive(buf + 0, 16);
    helper_double_28_recursive(buf + 65536, 16);
    helper_double_28_recursive(buf + 131072, 16);
    helper_double_28_recursive(buf + 196608, 16);
    helper_double_28_recursive(buf + 262144, 16);
    helper_double_28_recursive(buf + 327680, 16);
    helper_double_28_recursive(buf + 393216, 16);
    helper_double_28_recursive(buf + 458752, 16);
    for (int j = 0; j < 524288; j += 524288) {
      for (int k = 0; k < 65536; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 65536), "r"(buf + j + k + 131072), "r"(buf + j + k + 196608), "r"(buf + j + k + 262144), "r"(buf + j + k + 327680), "r"(buf + j + k + 393216), "r"(buf + j + k + 458752) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 22) {
    helper_double_28_recursive(buf + 0, 19);
    helper_double_28_recursive(buf + 524288, 19);
    helper_double_28_recursive(buf + 1048576, 19);
    helper_double_28_recursive(buf + 1572864, 19);
    helper_double_28_recursive(buf + 2097152, 19);
    helper_double_28_recursive(buf + 2621440, 19);
    helper_double_28_recursive(buf + 3145728, 19);
    helper_double_28_recursive(buf + 3670016, 19);
    for (int j = 0; j < 4194304; j += 4194304) {
      for (int k = 0; k < 524288; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 524288), "r"(buf + j + k + 1048576), "r"(buf + j + k + 1572864), "r"(buf + j + k + 2097152), "r"(buf + j + k + 2621440), "r"(buf + j + k + 3145728), "r"(buf + j + k + 3670016) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 25) {
    helper_double_28_recursive(buf + 0, 22);
    helper_double_28_recursive(buf + 4194304, 22);
    helper_double_28_recursive(buf + 8388608, 22);
    helper_double_28_recursive(buf + 12582912, 22);
    helper_double_28_recursive(buf + 16777216, 22);
    helper_double_28_recursive(buf + 20971520, 22);
    helper_double_28_recursive(buf + 25165824, 22);
    helper_double_28_recursive(buf + 29360128, 22);
    for (int j = 0; j < 33554432; j += 33554432) {
      for (int k = 0; k < 4194304; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4194304), "r"(buf + j + k + 8388608), "r"(buf + j + k + 12582912), "r"(buf + j + k + 16777216), "r"(buf + j + k + 20971520), "r"(buf + j + k + 25165824), "r"(buf + j + k + 29360128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 28) {
    helper_double_28_recursive(buf + 0, 25);
    helper_double_28_recursive(buf + 33554432, 25);
    helper_double_28_recursive(buf + 67108864, 25);
    helper_double_28_recursive(buf + 100663296, 25);
    helper_double_28_recursive(buf + 134217728, 25);
    helper_double_28_recursive(buf + 167772160, 25);
    helper_double_28_recursive(buf + 201326592, 25);
    helper_double_28_recursive(buf + 234881024, 25);
    for (int j = 0; j < 268435456; j += 268435456) {
      for (int k = 0; k < 33554432; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 33554432), "r"(buf + j + k + 67108864), "r"(buf + j + k + 100663296), "r"(buf + j + k + 134217728), "r"(buf + j + k + 167772160), "r"(buf + j + k + 201326592), "r"(buf + j + k + 234881024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_28(double *buf);
void helper_double_28(double *buf) {
  helper_double_28_recursive(buf, 28);
}
void helper_double_29_recursive(double *buf, int depth);
void helper_double_29_recursive(double *buf, int depth) {
  if (depth == 11) {
    for (int j = 0; j < 2048; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 2048; j += 2048) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256), "r"(buf + j + k + 512), "r"(buf + j + k + 768), "r"(buf + j + k + 1024), "r"(buf + j + k + 1280), "r"(buf + j + k + 1536), "r"(buf + j + k + 1792) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 14) {
    helper_double_29_recursive(buf + 0, 11);
    helper_double_29_recursive(buf + 2048, 11);
    helper_double_29_recursive(buf + 4096, 11);
    helper_double_29_recursive(buf + 6144, 11);
    helper_double_29_recursive(buf + 8192, 11);
    helper_double_29_recursive(buf + 10240, 11);
    helper_double_29_recursive(buf + 12288, 11);
    helper_double_29_recursive(buf + 14336, 11);
    for (int j = 0; j < 16384; j += 16384) {
      for (int k = 0; k < 2048; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2048), "r"(buf + j + k + 4096), "r"(buf + j + k + 6144), "r"(buf + j + k + 8192), "r"(buf + j + k + 10240), "r"(buf + j + k + 12288), "r"(buf + j + k + 14336) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 17) {
    helper_double_29_recursive(buf + 0, 14);
    helper_double_29_recursive(buf + 16384, 14);
    helper_double_29_recursive(buf + 32768, 14);
    helper_double_29_recursive(buf + 49152, 14);
    helper_double_29_recursive(buf + 65536, 14);
    helper_double_29_recursive(buf + 81920, 14);
    helper_double_29_recursive(buf + 98304, 14);
    helper_double_29_recursive(buf + 114688, 14);
    for (int j = 0; j < 131072; j += 131072) {
      for (int k = 0; k < 16384; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 16384), "r"(buf + j + k + 32768), "r"(buf + j + k + 49152), "r"(buf + j + k + 65536), "r"(buf + j + k + 81920), "r"(buf + j + k + 98304), "r"(buf + j + k + 114688) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 20) {
    helper_double_29_recursive(buf + 0, 17);
    helper_double_29_recursive(buf + 131072, 17);
    helper_double_29_recursive(buf + 262144, 17);
    helper_double_29_recursive(buf + 393216, 17);
    helper_double_29_recursive(buf + 524288, 17);
    helper_double_29_recursive(buf + 655360, 17);
    helper_double_29_recursive(buf + 786432, 17);
    helper_double_29_recursive(buf + 917504, 17);
    for (int j = 0; j < 1048576; j += 1048576) {
      for (int k = 0; k < 131072; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 131072), "r"(buf + j + k + 262144), "r"(buf + j + k + 393216), "r"(buf + j + k + 524288), "r"(buf + j + k + 655360), "r"(buf + j + k + 786432), "r"(buf + j + k + 917504) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 23) {
    helper_double_29_recursive(buf + 0, 20);
    helper_double_29_recursive(buf + 1048576, 20);
    helper_double_29_recursive(buf + 2097152, 20);
    helper_double_29_recursive(buf + 3145728, 20);
    helper_double_29_recursive(buf + 4194304, 20);
    helper_double_29_recursive(buf + 5242880, 20);
    helper_double_29_recursive(buf + 6291456, 20);
    helper_double_29_recursive(buf + 7340032, 20);
    for (int j = 0; j < 8388608; j += 8388608) {
      for (int k = 0; k < 1048576; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 1048576), "r"(buf + j + k + 2097152), "r"(buf + j + k + 3145728), "r"(buf + j + k + 4194304), "r"(buf + j + k + 5242880), "r"(buf + j + k + 6291456), "r"(buf + j + k + 7340032) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 26) {
    helper_double_29_recursive(buf + 0, 23);
    helper_double_29_recursive(buf + 8388608, 23);
    helper_double_29_recursive(buf + 16777216, 23);
    helper_double_29_recursive(buf + 25165824, 23);
    helper_double_29_recursive(buf + 33554432, 23);
    helper_double_29_recursive(buf + 41943040, 23);
    helper_double_29_recursive(buf + 50331648, 23);
    helper_double_29_recursive(buf + 58720256, 23);
    for (int j = 0; j < 67108864; j += 67108864) {
      for (int k = 0; k < 8388608; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 8388608), "r"(buf + j + k + 16777216), "r"(buf + j + k + 25165824), "r"(buf + j + k + 33554432), "r"(buf + j + k + 41943040), "r"(buf + j + k + 50331648), "r"(buf + j + k + 58720256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 29) {
    helper_double_29_recursive(buf + 0, 26);
    helper_double_29_recursive(buf + 67108864, 26);
    helper_double_29_recursive(buf + 134217728, 26);
    helper_double_29_recursive(buf + 201326592, 26);
    helper_double_29_recursive(buf + 268435456, 26);
    helper_double_29_recursive(buf + 335544320, 26);
    helper_double_29_recursive(buf + 402653184, 26);
    helper_double_29_recursive(buf + 469762048, 26);
    for (int j = 0; j < 536870912; j += 536870912) {
      for (int k = 0; k < 67108864; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 67108864), "r"(buf + j + k + 134217728), "r"(buf + j + k + 201326592), "r"(buf + j + k + 268435456), "r"(buf + j + k + 335544320), "r"(buf + j + k + 402653184), "r"(buf + j + k + 469762048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_29(double *buf);
void helper_double_29(double *buf) {
  helper_double_29_recursive(buf, 29);
}
void helper_double_30_recursive(double *buf, int depth);
void helper_double_30_recursive(double *buf, int depth) {
  if (depth == 9) {
    for (int j = 0; j < 512; j += 32) {
      for (int k = 0; k < 4; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vpermilpd $0, %%ymm0, %%ymm8\n"
          "vpermilpd $15, %%ymm0, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm0\n"
          "vpermilpd $0, %%ymm1, %%ymm8\n"
          "vpermilpd $15, %%ymm1, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm1\n"
          "vpermilpd $0, %%ymm2, %%ymm8\n"
          "vpermilpd $15, %%ymm2, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm2\n"
          "vpermilpd $0, %%ymm3, %%ymm8\n"
          "vpermilpd $15, %%ymm3, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm3\n"
          "vpermilpd $0, %%ymm4, %%ymm8\n"
          "vpermilpd $15, %%ymm4, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm4\n"
          "vpermilpd $0, %%ymm5, %%ymm8\n"
          "vpermilpd $15, %%ymm5, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm5\n"
          "vpermilpd $0, %%ymm6, %%ymm8\n"
          "vpermilpd $15, %%ymm6, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm6\n"
          "vpermilpd $0, %%ymm7, %%ymm8\n"
          "vpermilpd $15, %%ymm7, %%ymm9\n"
          "vxorpd %%ymm10, %%ymm10, %%ymm10\n"
          "vsubpd %%ymm9, %%ymm10, %%ymm11\n"
          "vaddsubpd %%ymm11, %%ymm8, %%ymm7\n"
          "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm0, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm0, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm0\n"
          "vperm2f128 $0, %%ymm1, %%ymm1, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm1, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm1, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm1\n"
          "vperm2f128 $0, %%ymm2, %%ymm2, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm2, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm2\n"
          "vperm2f128 $0, %%ymm3, %%ymm3, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm3, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm3, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm3\n"
          "vperm2f128 $0, %%ymm4, %%ymm4, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm4, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm4, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm4\n"
          "vperm2f128 $0, %%ymm5, %%ymm5, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm5, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm5\n"
          "vperm2f128 $0, %%ymm6, %%ymm6, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm6, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm6, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm6\n"
          "vperm2f128 $0, %%ymm7, %%ymm7, %%ymm8\n"
          "vxorpd %%ymm9, %%ymm9, %%ymm9\n"
          "vsubpd %%ymm7, %%ymm9, %%ymm10\n"
          "vperm2f128 $49, %%ymm10, %%ymm7, %%ymm11\n"
          "vaddpd %%ymm11, %%ymm8, %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4), "r"(buf + j + k + 8), "r"(buf + j + k + 12), "r"(buf + j + k + 16), "r"(buf + j + k + 20), "r"(buf + j + k + 24), "r"(buf + j + k + 28) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 512; j += 256) {
      for (int k = 0; k < 32; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32), "r"(buf + j + k + 64), "r"(buf + j + k + 96), "r"(buf + j + k + 128), "r"(buf + j + k + 160), "r"(buf + j + k + 192), "r"(buf + j + k + 224) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    for (int j = 0; j < 512; j += 512) {
      for (int k = 0; k < 256; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 12) {
    helper_double_30_recursive(buf + 0, 9);
    helper_double_30_recursive(buf + 512, 9);
    helper_double_30_recursive(buf + 1024, 9);
    helper_double_30_recursive(buf + 1536, 9);
    helper_double_30_recursive(buf + 2048, 9);
    helper_double_30_recursive(buf + 2560, 9);
    helper_double_30_recursive(buf + 3072, 9);
    helper_double_30_recursive(buf + 3584, 9);
    for (int j = 0; j < 4096; j += 4096) {
      for (int k = 0; k < 512; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 512), "r"(buf + j + k + 1024), "r"(buf + j + k + 1536), "r"(buf + j + k + 2048), "r"(buf + j + k + 2560), "r"(buf + j + k + 3072), "r"(buf + j + k + 3584) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 15) {
    helper_double_30_recursive(buf + 0, 12);
    helper_double_30_recursive(buf + 4096, 12);
    helper_double_30_recursive(buf + 8192, 12);
    helper_double_30_recursive(buf + 12288, 12);
    helper_double_30_recursive(buf + 16384, 12);
    helper_double_30_recursive(buf + 20480, 12);
    helper_double_30_recursive(buf + 24576, 12);
    helper_double_30_recursive(buf + 28672, 12);
    for (int j = 0; j < 32768; j += 32768) {
      for (int k = 0; k < 4096; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 4096), "r"(buf + j + k + 8192), "r"(buf + j + k + 12288), "r"(buf + j + k + 16384), "r"(buf + j + k + 20480), "r"(buf + j + k + 24576), "r"(buf + j + k + 28672) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 18) {
    helper_double_30_recursive(buf + 0, 15);
    helper_double_30_recursive(buf + 32768, 15);
    helper_double_30_recursive(buf + 65536, 15);
    helper_double_30_recursive(buf + 98304, 15);
    helper_double_30_recursive(buf + 131072, 15);
    helper_double_30_recursive(buf + 163840, 15);
    helper_double_30_recursive(buf + 196608, 15);
    helper_double_30_recursive(buf + 229376, 15);
    for (int j = 0; j < 262144; j += 262144) {
      for (int k = 0; k < 32768; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 32768), "r"(buf + j + k + 65536), "r"(buf + j + k + 98304), "r"(buf + j + k + 131072), "r"(buf + j + k + 163840), "r"(buf + j + k + 196608), "r"(buf + j + k + 229376) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 21) {
    helper_double_30_recursive(buf + 0, 18);
    helper_double_30_recursive(buf + 262144, 18);
    helper_double_30_recursive(buf + 524288, 18);
    helper_double_30_recursive(buf + 786432, 18);
    helper_double_30_recursive(buf + 1048576, 18);
    helper_double_30_recursive(buf + 1310720, 18);
    helper_double_30_recursive(buf + 1572864, 18);
    helper_double_30_recursive(buf + 1835008, 18);
    for (int j = 0; j < 2097152; j += 2097152) {
      for (int k = 0; k < 262144; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 262144), "r"(buf + j + k + 524288), "r"(buf + j + k + 786432), "r"(buf + j + k + 1048576), "r"(buf + j + k + 1310720), "r"(buf + j + k + 1572864), "r"(buf + j + k + 1835008) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 24) {
    helper_double_30_recursive(buf + 0, 21);
    helper_double_30_recursive(buf + 2097152, 21);
    helper_double_30_recursive(buf + 4194304, 21);
    helper_double_30_recursive(buf + 6291456, 21);
    helper_double_30_recursive(buf + 8388608, 21);
    helper_double_30_recursive(buf + 10485760, 21);
    helper_double_30_recursive(buf + 12582912, 21);
    helper_double_30_recursive(buf + 14680064, 21);
    for (int j = 0; j < 16777216; j += 16777216) {
      for (int k = 0; k < 2097152; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 2097152), "r"(buf + j + k + 4194304), "r"(buf + j + k + 6291456), "r"(buf + j + k + 8388608), "r"(buf + j + k + 10485760), "r"(buf + j + k + 12582912), "r"(buf + j + k + 14680064) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 27) {
    helper_double_30_recursive(buf + 0, 24);
    helper_double_30_recursive(buf + 16777216, 24);
    helper_double_30_recursive(buf + 33554432, 24);
    helper_double_30_recursive(buf + 50331648, 24);
    helper_double_30_recursive(buf + 67108864, 24);
    helper_double_30_recursive(buf + 83886080, 24);
    helper_double_30_recursive(buf + 100663296, 24);
    helper_double_30_recursive(buf + 117440512, 24);
    for (int j = 0; j < 134217728; j += 134217728) {
      for (int k = 0; k < 16777216; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 16777216), "r"(buf + j + k + 33554432), "r"(buf + j + k + 50331648), "r"(buf + j + k + 67108864), "r"(buf + j + k + 83886080), "r"(buf + j + k + 100663296), "r"(buf + j + k + 117440512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
  if (depth == 30) {
    helper_double_30_recursive(buf + 0, 27);
    helper_double_30_recursive(buf + 134217728, 27);
    helper_double_30_recursive(buf + 268435456, 27);
    helper_double_30_recursive(buf + 402653184, 27);
    helper_double_30_recursive(buf + 536870912, 27);
    helper_double_30_recursive(buf + 671088640, 27);
    helper_double_30_recursive(buf + 805306368, 27);
    helper_double_30_recursive(buf + 939524096, 27);
    for (int j = 0; j < 1073741824; j += 1073741824) {
      for (int k = 0; k < 134217728; k += 4) {
        __asm__ volatile (
          "vmovupd (%0), %%ymm0\n"
          "vmovupd (%1), %%ymm1\n"
          "vmovupd (%2), %%ymm2\n"
          "vmovupd (%3), %%ymm3\n"
          "vmovupd (%4), %%ymm4\n"
          "vmovupd (%5), %%ymm5\n"
          "vmovupd (%6), %%ymm6\n"
          "vmovupd (%7), %%ymm7\n"
          "vaddpd %%ymm1, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm1, %%ymm0, %%ymm9\n"
          "vaddpd %%ymm3, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm3, %%ymm2, %%ymm11\n"
          "vaddpd %%ymm5, %%ymm4, %%ymm12\n"
          "vsubpd %%ymm5, %%ymm4, %%ymm13\n"
          "vaddpd %%ymm7, %%ymm6, %%ymm14\n"
          "vsubpd %%ymm7, %%ymm6, %%ymm15\n"
          "vaddpd %%ymm10, %%ymm8, %%ymm0\n"
          "vsubpd %%ymm10, %%ymm8, %%ymm2\n"
          "vaddpd %%ymm11, %%ymm9, %%ymm1\n"
          "vsubpd %%ymm11, %%ymm9, %%ymm3\n"
          "vaddpd %%ymm14, %%ymm12, %%ymm4\n"
          "vsubpd %%ymm14, %%ymm12, %%ymm6\n"
          "vaddpd %%ymm15, %%ymm13, %%ymm5\n"
          "vsubpd %%ymm15, %%ymm13, %%ymm7\n"
          "vaddpd %%ymm4, %%ymm0, %%ymm8\n"
          "vsubpd %%ymm4, %%ymm0, %%ymm12\n"
          "vaddpd %%ymm5, %%ymm1, %%ymm9\n"
          "vsubpd %%ymm5, %%ymm1, %%ymm13\n"
          "vaddpd %%ymm6, %%ymm2, %%ymm10\n"
          "vsubpd %%ymm6, %%ymm2, %%ymm14\n"
          "vaddpd %%ymm7, %%ymm3, %%ymm11\n"
          "vsubpd %%ymm7, %%ymm3, %%ymm15\n"
          "vmovupd %%ymm8, (%0)\n"
          "vmovupd %%ymm9, (%1)\n"
          "vmovupd %%ymm10, (%2)\n"
          "vmovupd %%ymm11, (%3)\n"
          "vmovupd %%ymm12, (%4)\n"
          "vmovupd %%ymm13, (%5)\n"
          "vmovupd %%ymm14, (%6)\n"
          "vmovupd %%ymm15, (%7)\n"
          :: "r"(buf + j + k + 0), "r"(buf + j + k + 134217728), "r"(buf + j + k + 268435456), "r"(buf + j + k + 402653184), "r"(buf + j + k + 536870912), "r"(buf + j + k + 671088640), "r"(buf + j + k + 805306368), "r"(buf + j + k + 939524096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7", "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "memory"
        );
      }
    }
    return;
  }
}
void helper_double_30(double *buf);
void helper_double_30(double *buf) {
  helper_double_30_recursive(buf, 30);
}
int fht_double(double *buf, int log_n) {
  if (log_n == 0) {
    return 0;
  }
  if (log_n == 1) {
    helper_double_1(buf);
    return 0;
  }
  if (log_n == 2) {
    helper_double_2(buf);
    return 0;
  }
  if (log_n == 3) {
    helper_double_3(buf);
    return 0;
  }
  if (log_n == 4) {
    helper_double_4(buf);
    return 0;
  }
  if (log_n == 5) {
    helper_double_5(buf);
    return 0;
  }
  if (log_n == 6) {
    helper_double_6(buf);
    return 0;
  }
  if (log_n == 7) {
    helper_double_7(buf);
    return 0;
  }
  if (log_n == 8) {
    helper_double_8(buf);
    return 0;
  }
  if (log_n == 9) {
    helper_double_9(buf);
    return 0;
  }
  if (log_n == 10) {
    helper_double_10(buf);
    return 0;
  }
  if (log_n == 11) {
    helper_double_11(buf);
    return 0;
  }
  if (log_n == 12) {
    helper_double_12(buf);
    return 0;
  }
  if (log_n == 13) {
    helper_double_13(buf);
    return 0;
  }
  if (log_n == 14) {
    helper_double_14(buf);
    return 0;
  }
  if (log_n == 15) {
    helper_double_15(buf);
    return 0;
  }
  if (log_n == 16) {
    helper_double_16(buf);
    return 0;
  }
  if (log_n == 17) {
    helper_double_17(buf);
    return 0;
  }
  if (log_n == 18) {
    helper_double_18(buf);
    return 0;
  }
  if (log_n == 19) {
    helper_double_19(buf);
    return 0;
  }
  if (log_n == 20) {
    helper_double_20(buf);
    return 0;
  }
  if (log_n == 21) {
    helper_double_21(buf);
    return 0;
  }
  if (log_n == 22) {
    helper_double_22(buf);
    return 0;
  }
  if (log_n == 23) {
    helper_double_23(buf);
    return 0;
  }
  if (log_n == 24) {
    helper_double_24(buf);
    return 0;
  }
  if (log_n == 25) {
    helper_double_25(buf);
    return 0;
  }
  if (log_n == 26) {
    helper_double_26(buf);
    return 0;
  }
  if (log_n == 27) {
    helper_double_27(buf);
    return 0;
  }
  if (log_n == 28) {
    helper_double_28(buf);
    return 0;
  }
  if (log_n == 29) {
    helper_double_29(buf);
    return 0;
  }
  if (log_n == 30) {
    helper_double_30(buf);
    return 0;
  }
  return 1;
}
