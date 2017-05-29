inline void steps_1_0_1(float *buf) {
  for (int j = 0; j < 2; j += 2) {
    for (int k = 0; k < 1; ++k) {
      float u = buf[j + k];
      float v = buf[j + k + 1];
      buf[j + k] = u + v;
      buf[j + k + 1] = u - v;
    }
  }
}

inline void steps_2_0_2(float *buf) {
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

inline void steps_3_0_3(float *buf) {
  for (int j = 0; j < 8; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 8; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 8; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
}

inline void steps_4_0_4(float *buf) {
  for (int j = 0; j < 16; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 16; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 16; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 16; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_5_0_5(float *buf) {
  for (int j = 0; j < 32; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 32; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 32; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 32; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 32; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_6_0_6(float *buf) {
  for (int j = 0; j < 64; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 64; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 64; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 64; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 64; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 64; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_7_0_7(float *buf) {
  for (int j = 0; j < 128; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 128; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 128; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 128; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 128; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 128; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 128; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_8_0_8(float *buf) {
  for (int j = 0; j < 256; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 256; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 256; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 256; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 256; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 256; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 256; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 256; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_9_0_9(float *buf) {
  for (int j = 0; j < 512; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 512; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 512; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 512; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 512; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 512; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 512; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 512; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 512; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_10_0_10(float *buf) {
  for (int j = 0; j < 1024; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 1024; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 1024; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 1024; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1024; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1024; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1024; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1024; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1024; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1024; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_11_0_11(float *buf) {
  for (int j = 0; j < 2048; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 2048; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 2048; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 2048; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2048; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2048; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2048; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2048; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2048; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2048; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2048; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_12_0_12(float *buf) {
  for (int j = 0; j < 4096; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 4096; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 4096; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 4096; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4096; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4096; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4096; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4096; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4096; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4096; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4096; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4096; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_13_0_13(float *buf) {
  for (int j = 0; j < 8192; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 8192; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 8192; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 8192; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8192; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8192; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8192; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8192; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8192; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8192; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8192; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8192; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8192; j += 8192) {
    for (int k = 0; k < 4096; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_14_0_14(float *buf) {
  for (int j = 0; j < 16384; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 16384; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 16384; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 16384; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16384; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16384; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16384; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16384; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16384; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16384; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16384; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16384; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16384; j += 8192) {
    for (int k = 0; k < 4096; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16384; j += 16384) {
    for (int k = 0; k < 8192; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8192) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_15_0_15(float *buf) {
  for (int j = 0; j < 32768; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 32768; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 32768; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 32768; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 32768; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 32768; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 32768; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 32768; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 32768; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 32768; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 32768; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 32768; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 32768; j += 8192) {
    for (int k = 0; k < 4096; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 32768; j += 16384) {
    for (int k = 0; k < 8192; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8192) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 32768; j += 32768) {
    for (int k = 0; k < 16384; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16384) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_16_0_16(float *buf) {
  for (int j = 0; j < 65536; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 65536; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 65536; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 65536; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 65536; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 65536; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 65536; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 65536; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 65536; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 65536; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 65536; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 65536; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 65536; j += 8192) {
    for (int k = 0; k < 4096; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 65536; j += 16384) {
    for (int k = 0; k < 8192; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8192) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 65536; j += 32768) {
    for (int k = 0; k < 16384; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16384) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 65536; j += 65536) {
    for (int k = 0; k < 32768; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_17_0_17(float *buf) {
  for (int j = 0; j < 131072; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 131072; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 131072; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 131072; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 131072; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 131072; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 131072; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 131072; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 131072; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 131072; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 131072; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 131072; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 131072; j += 8192) {
    for (int k = 0; k < 4096; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 131072; j += 16384) {
    for (int k = 0; k < 8192; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8192) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 131072; j += 32768) {
    for (int k = 0; k < 16384; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16384) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 131072; j += 65536) {
    for (int k = 0; k < 32768; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 131072; j += 131072) {
    for (int k = 0; k < 65536; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 65536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_18_0_18(float *buf) {
  for (int j = 0; j < 262144; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 262144; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 262144; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 262144; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 262144; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 262144; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 262144; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 262144; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 262144; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 262144; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 262144; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 262144; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 262144; j += 8192) {
    for (int k = 0; k < 4096; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 262144; j += 16384) {
    for (int k = 0; k < 8192; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8192) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 262144; j += 32768) {
    for (int k = 0; k < 16384; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16384) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 262144; j += 65536) {
    for (int k = 0; k < 32768; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 262144; j += 131072) {
    for (int k = 0; k < 65536; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 65536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 262144; j += 262144) {
    for (int k = 0; k < 131072; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 131072) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_19_0_19(float *buf) {
  for (int j = 0; j < 524288; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 524288; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 524288; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 524288; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 524288; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 524288; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 524288; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 524288; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 524288; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 524288; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 524288; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 524288; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 524288; j += 8192) {
    for (int k = 0; k < 4096; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 524288; j += 16384) {
    for (int k = 0; k < 8192; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8192) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 524288; j += 32768) {
    for (int k = 0; k < 16384; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16384) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 524288; j += 65536) {
    for (int k = 0; k < 32768; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 524288; j += 131072) {
    for (int k = 0; k < 65536; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 65536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 524288; j += 262144) {
    for (int k = 0; k < 131072; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 131072) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 524288; j += 524288) {
    for (int k = 0; k < 262144; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 262144) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_20_0_20(float *buf) {
  for (int j = 0; j < 1048576; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 1048576; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 1048576; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 1048576; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1048576; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1048576; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1048576; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1048576; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1048576; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1048576; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1048576; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1048576; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1048576; j += 8192) {
    for (int k = 0; k < 4096; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1048576; j += 16384) {
    for (int k = 0; k < 8192; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8192) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1048576; j += 32768) {
    for (int k = 0; k < 16384; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16384) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1048576; j += 65536) {
    for (int k = 0; k < 32768; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1048576; j += 131072) {
    for (int k = 0; k < 65536; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 65536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1048576; j += 262144) {
    for (int k = 0; k < 131072; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 131072) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1048576; j += 524288) {
    for (int k = 0; k < 262144; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 262144) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1048576; j += 1048576) {
    for (int k = 0; k < 524288; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 524288) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_21_0_21(float *buf) {
  for (int j = 0; j < 2097152; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 2097152; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 2097152; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 2097152; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2097152; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2097152; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2097152; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2097152; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2097152; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2097152; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2097152; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2097152; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2097152; j += 8192) {
    for (int k = 0; k < 4096; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2097152; j += 16384) {
    for (int k = 0; k < 8192; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8192) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2097152; j += 32768) {
    for (int k = 0; k < 16384; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16384) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2097152; j += 65536) {
    for (int k = 0; k < 32768; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2097152; j += 131072) {
    for (int k = 0; k < 65536; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 65536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2097152; j += 262144) {
    for (int k = 0; k < 131072; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 131072) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2097152; j += 524288) {
    for (int k = 0; k < 262144; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 262144) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2097152; j += 1048576) {
    for (int k = 0; k < 524288; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 524288) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 2097152; j += 2097152) {
    for (int k = 0; k < 1048576; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1048576) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_22_0_22(float *buf) {
  for (int j = 0; j < 4194304; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 4194304; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 4194304; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 4194304; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4194304; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4194304; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4194304; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4194304; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4194304; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4194304; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4194304; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4194304; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4194304; j += 8192) {
    for (int k = 0; k < 4096; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4194304; j += 16384) {
    for (int k = 0; k < 8192; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8192) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4194304; j += 32768) {
    for (int k = 0; k < 16384; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16384) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4194304; j += 65536) {
    for (int k = 0; k < 32768; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4194304; j += 131072) {
    for (int k = 0; k < 65536; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 65536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4194304; j += 262144) {
    for (int k = 0; k < 131072; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 131072) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4194304; j += 524288) {
    for (int k = 0; k < 262144; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 262144) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4194304; j += 1048576) {
    for (int k = 0; k < 524288; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 524288) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4194304; j += 2097152) {
    for (int k = 0; k < 1048576; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1048576) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 4194304; j += 4194304) {
    for (int k = 0; k < 2097152; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2097152) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_23_0_23(float *buf) {
  for (int j = 0; j < 8388608; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 8388608; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 8388608; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 8388608; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 8192) {
    for (int k = 0; k < 4096; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 16384) {
    for (int k = 0; k < 8192; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8192) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 32768) {
    for (int k = 0; k < 16384; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16384) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 65536) {
    for (int k = 0; k < 32768; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 131072) {
    for (int k = 0; k < 65536; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 65536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 262144) {
    for (int k = 0; k < 131072; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 131072) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 524288) {
    for (int k = 0; k < 262144; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 262144) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 1048576) {
    for (int k = 0; k < 524288; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 524288) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 2097152) {
    for (int k = 0; k < 1048576; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1048576) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 4194304) {
    for (int k = 0; k < 2097152; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2097152) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 8388608; j += 8388608) {
    for (int k = 0; k < 4194304; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4194304) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_24_0_24(float *buf) {
  for (int j = 0; j < 16777216; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 16777216; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 16777216; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 16777216; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 8192) {
    for (int k = 0; k < 4096; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 16384) {
    for (int k = 0; k < 8192; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8192) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 32768) {
    for (int k = 0; k < 16384; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16384) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 65536) {
    for (int k = 0; k < 32768; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 131072) {
    for (int k = 0; k < 65536; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 65536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 262144) {
    for (int k = 0; k < 131072; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 131072) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 524288) {
    for (int k = 0; k < 262144; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 262144) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 1048576) {
    for (int k = 0; k < 524288; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 524288) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 2097152) {
    for (int k = 0; k < 1048576; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1048576) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 4194304) {
    for (int k = 0; k < 2097152; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2097152) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 8388608) {
    for (int k = 0; k < 4194304; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4194304) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 16777216; j += 16777216) {
    for (int k = 0; k < 8388608; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8388608) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_25_0_25(float *buf) {
  for (int j = 0; j < 33554432; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 33554432; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 33554432; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 33554432; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 8192) {
    for (int k = 0; k < 4096; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 16384) {
    for (int k = 0; k < 8192; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8192) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 32768) {
    for (int k = 0; k < 16384; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16384) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 65536) {
    for (int k = 0; k < 32768; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 131072) {
    for (int k = 0; k < 65536; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 65536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 262144) {
    for (int k = 0; k < 131072; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 131072) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 524288) {
    for (int k = 0; k < 262144; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 262144) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 1048576) {
    for (int k = 0; k < 524288; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 524288) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 2097152) {
    for (int k = 0; k < 1048576; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1048576) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 4194304) {
    for (int k = 0; k < 2097152; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2097152) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 8388608) {
    for (int k = 0; k < 4194304; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4194304) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 16777216) {
    for (int k = 0; k < 8388608; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8388608) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 33554432; j += 33554432) {
    for (int k = 0; k < 16777216; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16777216) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_26_0_26(float *buf) {
  for (int j = 0; j < 67108864; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 67108864; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 67108864; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 67108864; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 8192) {
    for (int k = 0; k < 4096; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 16384) {
    for (int k = 0; k < 8192; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8192) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 32768) {
    for (int k = 0; k < 16384; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16384) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 65536) {
    for (int k = 0; k < 32768; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 131072) {
    for (int k = 0; k < 65536; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 65536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 262144) {
    for (int k = 0; k < 131072; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 131072) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 524288) {
    for (int k = 0; k < 262144; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 262144) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 1048576) {
    for (int k = 0; k < 524288; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 524288) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 2097152) {
    for (int k = 0; k < 1048576; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1048576) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 4194304) {
    for (int k = 0; k < 2097152; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2097152) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 8388608) {
    for (int k = 0; k < 4194304; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4194304) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 16777216) {
    for (int k = 0; k < 8388608; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8388608) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 33554432) {
    for (int k = 0; k < 16777216; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16777216) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 67108864; j += 67108864) {
    for (int k = 0; k < 33554432; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 33554432) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_27_0_27(float *buf) {
  for (int j = 0; j < 134217728; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 134217728; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 134217728; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 134217728; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 8192) {
    for (int k = 0; k < 4096; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 16384) {
    for (int k = 0; k < 8192; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8192) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 32768) {
    for (int k = 0; k < 16384; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16384) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 65536) {
    for (int k = 0; k < 32768; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 131072) {
    for (int k = 0; k < 65536; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 65536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 262144) {
    for (int k = 0; k < 131072; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 131072) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 524288) {
    for (int k = 0; k < 262144; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 262144) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 1048576) {
    for (int k = 0; k < 524288; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 524288) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 2097152) {
    for (int k = 0; k < 1048576; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1048576) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 4194304) {
    for (int k = 0; k < 2097152; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2097152) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 8388608) {
    for (int k = 0; k < 4194304; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4194304) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 16777216) {
    for (int k = 0; k < 8388608; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8388608) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 33554432) {
    for (int k = 0; k < 16777216; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16777216) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 67108864) {
    for (int k = 0; k < 33554432; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 33554432) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 134217728; j += 134217728) {
    for (int k = 0; k < 67108864; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 67108864) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_28_0_28(float *buf) {
  for (int j = 0; j < 268435456; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 268435456; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 268435456; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 268435456; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 8192) {
    for (int k = 0; k < 4096; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 16384) {
    for (int k = 0; k < 8192; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8192) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 32768) {
    for (int k = 0; k < 16384; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16384) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 65536) {
    for (int k = 0; k < 32768; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 131072) {
    for (int k = 0; k < 65536; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 65536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 262144) {
    for (int k = 0; k < 131072; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 131072) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 524288) {
    for (int k = 0; k < 262144; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 262144) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 1048576) {
    for (int k = 0; k < 524288; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 524288) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 2097152) {
    for (int k = 0; k < 1048576; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1048576) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 4194304) {
    for (int k = 0; k < 2097152; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2097152) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 8388608) {
    for (int k = 0; k < 4194304; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4194304) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 16777216) {
    for (int k = 0; k < 8388608; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8388608) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 33554432) {
    for (int k = 0; k < 16777216; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16777216) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 67108864) {
    for (int k = 0; k < 33554432; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 33554432) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 134217728) {
    for (int k = 0; k < 67108864; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 67108864) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 268435456; j += 268435456) {
    for (int k = 0; k < 134217728; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 134217728) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_29_0_29(float *buf) {
  for (int j = 0; j < 536870912; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 536870912; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 536870912; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 536870912; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 8192) {
    for (int k = 0; k < 4096; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 16384) {
    for (int k = 0; k < 8192; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8192) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 32768) {
    for (int k = 0; k < 16384; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16384) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 65536) {
    for (int k = 0; k < 32768; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 131072) {
    for (int k = 0; k < 65536; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 65536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 262144) {
    for (int k = 0; k < 131072; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 131072) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 524288) {
    for (int k = 0; k < 262144; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 262144) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 1048576) {
    for (int k = 0; k < 524288; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 524288) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 2097152) {
    for (int k = 0; k < 1048576; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1048576) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 4194304) {
    for (int k = 0; k < 2097152; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2097152) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 8388608) {
    for (int k = 0; k < 4194304; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4194304) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 16777216) {
    for (int k = 0; k < 8388608; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8388608) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 33554432) {
    for (int k = 0; k < 16777216; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16777216) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 67108864) {
    for (int k = 0; k < 33554432; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 33554432) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 134217728) {
    for (int k = 0; k < 67108864; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 67108864) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 268435456) {
    for (int k = 0; k < 134217728; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 134217728) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 536870912; j += 536870912) {
    for (int k = 0; k < 268435456; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 268435456) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

inline void steps_30_0_30(float *buf) {
  for (int j = 0; j < 1073741824; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $160, %%ymm0, %%ymm1\n"
      "vpermilps $245, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vaddsubps %%ymm4, %%ymm1, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 1073741824; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vpermilps $68, %%ymm0, %%ymm1\n"
      "vpermilps $238, %%ymm0, %%ymm2\n"
      "vxorps %%ymm3, %%ymm3, %%ymm3\n"
      "vsubps %%ymm2, %%ymm3, %%ymm4\n"
      "vblendps $204, %%ymm4, %%ymm2, %%ymm5\n"
      "vaddps %%ymm1, %%ymm5, %%ymm6\n"
      "vmovups %%ymm6, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "memory"
    );
  }
  for (int j = 0; j < 1073741824; j += 8) {
    __asm__ volatile (
      "vmovups (%0), %%ymm0\n"
      "vxorps %%ymm1, %%ymm1, %%ymm1\n"
      "vsubps %%ymm0, %%ymm1, %%ymm2\n"
      "vperm2f128 $0, %%ymm0, %%ymm0, %%ymm3\n"
      "vperm2f128 $49, %%ymm2, %%ymm0, %%ymm4\n"
      "vaddps %%ymm3, %%ymm4, %%ymm5\n"
      "vmovups %%ymm5, (%0)\n"
      :: "r"(buf + j) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "memory"
    );
  }
  for (int j = 0; j < 1073741824; j += 16) {
    for (int k = 0; k < 8; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 32) {
    for (int k = 0; k < 16; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 64) {
    for (int k = 0; k < 32; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 128) {
    for (int k = 0; k < 64; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 64) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 256) {
    for (int k = 0; k < 128; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 128) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 512) {
    for (int k = 0; k < 256; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 256) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 1024) {
    for (int k = 0; k < 512; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 512) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 2048) {
    for (int k = 0; k < 1024; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1024) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 4096) {
    for (int k = 0; k < 2048; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2048) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 8192) {
    for (int k = 0; k < 4096; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4096) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 16384) {
    for (int k = 0; k < 8192; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8192) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 32768) {
    for (int k = 0; k < 16384; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16384) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 65536) {
    for (int k = 0; k < 32768; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 32768) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 131072) {
    for (int k = 0; k < 65536; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 65536) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 262144) {
    for (int k = 0; k < 131072; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 131072) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 524288) {
    for (int k = 0; k < 262144; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 262144) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 1048576) {
    for (int k = 0; k < 524288; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 524288) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 2097152) {
    for (int k = 0; k < 1048576; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 1048576) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 4194304) {
    for (int k = 0; k < 2097152; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 2097152) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 8388608) {
    for (int k = 0; k < 4194304; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 4194304) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 16777216) {
    for (int k = 0; k < 8388608; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 8388608) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 33554432) {
    for (int k = 0; k < 16777216; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 16777216) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 67108864) {
    for (int k = 0; k < 33554432; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 33554432) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 134217728) {
    for (int k = 0; k < 67108864; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 67108864) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 268435456) {
    for (int k = 0; k < 134217728; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 134217728) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 536870912) {
    for (int k = 0; k < 268435456; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 268435456) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
  for (int j = 0; j < 1073741824; j += 1073741824) {
    for (int k = 0; k < 536870912; k += 8) {
      __asm__ volatile (
        "vmovups (%0), %%ymm0\n"
        "vmovups (%1), %%ymm1\n"
        "vaddps %%ymm1, %%ymm0, %%ymm2\n"
        "vsubps %%ymm1, %%ymm0, %%ymm3\n"
        "vmovups %%ymm2, (%0)\n"
        "vmovups %%ymm3, (%1)\n"
        :: "r" (buf + j + k), "r" (buf + j + k + 536870912) : "%ymm0", "%ymm1", "%ymm2", "%ymm3", "memory"
      );
    }
  }
}

void fht(float *buf, int log_n) {
  if (log_n == 0) {
  }
  else if (log_n == 1) {
    steps_1_0_1(buf);
  }
  else if (log_n == 2) {
    steps_2_0_2(buf);
  }
  else if (log_n == 3) {
    steps_3_0_3(buf);
  }
  else if (log_n == 4) {
    steps_4_0_4(buf);
  }
  else if (log_n == 5) {
    steps_5_0_5(buf);
  }
  else if (log_n == 6) {
    steps_6_0_6(buf);
  }
  else if (log_n == 7) {
    steps_7_0_7(buf);
  }
  else if (log_n == 8) {
    steps_8_0_8(buf);
  }
  else if (log_n == 9) {
    steps_9_0_9(buf);
  }
  else if (log_n == 10) {
    steps_10_0_10(buf);
  }
  else if (log_n == 11) {
    steps_11_0_11(buf);
  }
  else if (log_n == 12) {
    steps_12_0_12(buf);
  }
  else if (log_n == 13) {
    steps_13_0_13(buf);
  }
  else if (log_n == 14) {
    steps_14_0_14(buf);
  }
  else if (log_n == 15) {
    steps_15_0_15(buf);
  }
  else if (log_n == 16) {
    steps_16_0_16(buf);
  }
  else if (log_n == 17) {
    steps_17_0_17(buf);
  }
  else if (log_n == 18) {
    steps_18_0_18(buf);
  }
  else if (log_n == 19) {
    steps_19_0_19(buf);
  }
  else if (log_n == 20) {
    steps_20_0_20(buf);
  }
  else if (log_n == 21) {
    steps_21_0_21(buf);
  }
  else if (log_n == 22) {
    steps_22_0_22(buf);
  }
  else if (log_n == 23) {
    steps_23_0_23(buf);
  }
  else if (log_n == 24) {
    steps_24_0_24(buf);
  }
  else if (log_n == 25) {
    steps_25_0_25(buf);
  }
  else if (log_n == 26) {
    steps_26_0_26(buf);
  }
  else if (log_n == 27) {
    steps_27_0_27(buf);
  }
  else if (log_n == 28) {
    steps_28_0_28(buf);
  }
  else if (log_n == 29) {
    steps_29_0_29(buf);
  }
  else if (log_n == 30) {
    steps_30_0_30(buf);
  }
  else {
  }
}

