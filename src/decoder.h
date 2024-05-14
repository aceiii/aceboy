#pragma once

#include "instructions.h"
#include "registers.h"
#include <expected>

using decode_result = std::expected<Instruction, std::string>;

class Decoder {
public:
  Decode(const uint8_t* memory, const Registers* registers);

  decode_result decode();
};
