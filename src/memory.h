#pragma once

#include <array>

const int kMemoryMaxSize = 65536;

struct Memory {
  std::array<uint8_t, kMemoryMaxSize> bytes;

  void set8(uint16_t address, uint8_t val) {
    bytes[address] = val;
  }

  uint8_t get8(uint8_t address) const {
    return bytes[address];
  }

  uint8_t& at(uint8_t address) {
    return bytes[address];
  }

  void set16(uint16_t address, uint16_t val) {
    bytes[address] = val >> 8;
    bytes[address + 1] = val & 0xff;
  }
};
