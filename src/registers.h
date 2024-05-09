#pragma once

#include <cstdint>
#include <array>

enum Flag {
  kFlagC = 4,
  kFlagH = 5,
  kFlagN = 6,
  kFlagZ = 7,
};

enum Register8 {
  kRegA = 0,
  kRegF,
  kRegB,
  kRegC,
  kRegD,
  kRegE,
  kRegH,
  kRegL,
  kRegCount,
};

enum Register16 {
  kRegAF = 0,
  kRegBC = 2,
  kRegDE = 4,
  kRegHL = 6,
};

struct Flags {
  uint8_t &val;

  inline uint8_t get(Flag flag) const {
    return (val >> static_cast<int>(flag)) & 1;
  }

  inline void set(Flag flag, uint8_t bit) {
    val = (val & ~(1 << static_cast<int>(flag))) | ((bit & 1) << static_cast<int>(flag));
  }
};

struct Registers {
  std::array<uint8_t, kRegCount> vals;
  uint16_t pc;
  uint16_t sp;

  Flags flags = { vals[kRegF] };

  inline uint8_t get8(Register8 reg) const {
    return vals[reg];
  }

  inline void set8(Register8 reg, uint8_t val) {
    vals[reg] = val & (reg == kRegF ? 0xf0 : 0xff);
  }

  inline uint16_t get16(Register16 reg) const {
    return (vals[reg] << 8) | vals[reg + 1];
  }

  inline void set16(Register16 reg, uint16_t val) {
    vals[reg] = val >> 8;
    vals[reg + 1] = val & (reg == kRegAF ? 0xf0 : 0xff);
  }

  inline void reset() {
    vals.fill(0);
  }
};
