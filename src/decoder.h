#pragma once

#include "instructions.h"
#include "registers.h"
#include "opcodes.h"

#include <expected>
#include <string>

class Decoder {
public:
  Instruction decode(uint8_t *memory);
};
