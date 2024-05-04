#pragma once

#include <cstdint>

struct Registers {
  uint16_t af;
  uint16_t bc;
  uint16_t de;
  uint16_t hl;
  uint16_t pc;
  uint16_t sp;

  inline void reset() {
    af = 0;
    bc = 0;
    de = 0;
    hl = 0;
    pc = 0;
    sp = 0;
  }

  static inline uint16_t high(uint16_t val) {
    return val >> 8;
  }

  static inline uint16_t low(uint16_t val) {
    return val & 0xff;
  }

  inline uint16_t a() const {
    return high(af);
  }

  inline uint16_t f() const {
    return low(af);
  }

  inline uint16_t b() const {
    return high(bc);
  }

  inline uint16_t c() const {
    return low(bc);
  }

  inline uint16_t d() const {
    return high(de);
  }

  inline uint16_t e() const {
    return low(de);
  }

  inline uint16_t h() const {
    return high(hl);
  }

  inline uint16_t l() const {
    return low(hl);
  }

  inline uint16_t flag_c() const {
    return (af >> 4) & 1;
  }

  inline uint16_t flag_h() const {
    return (af >> 5) & 1;
  }

  inline uint16_t flag_n() const {
    return (af >> 6) & 1;
  }

  inline uint16_t flag_z() const {
    return (af >> 7) & 1;
  }
};
