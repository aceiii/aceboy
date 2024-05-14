#pragma once

#include "opcodes.h"

#include <optional>
#include <string_view>

enum Cond {
  kCondNZ,
  kCondZ,
  kCondNC,
  kCondC,
};

struct Instruction {
  Opcode opcode;
  size_t cycles;
  size_t bytes;
};
