#pragma once

#include <optional>
#include <string_view>


enum Cond {
  kCondNZ,
  kCondZ,
  kCondNC,
  kCondC,
};

struct Instruction {
  std::string_view mnemonic;
  size_t cycles;
  size_t bytes;
};
