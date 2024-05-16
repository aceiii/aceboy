#include "decoder.h"
#include "instructions.h"
#include "opcodes.h"

#include <optional>
#include <unordered_map>

Instruction Decoder::decode(uint8_t* memory) {
  uint8_t op = *memory;
  uint8_t n8 = *(memory + 1);
  uint8_t hi = *(memory + 2);
  uint16_t n16 = (hi << 8) | n8;
  int8_t e8 = static_cast<int8_t>(n8);

  bool prefixed = false;

  switch (op)
  {
    case 0x00: return { Opcode::NOP, 1, 4, std::nullopt };
    case 0x01: return { Opcode::LD, 3, 12, Operands { { Reg8::A, true }, { Immediate16 { n16 }, true } } };
    case 0x02: return { Opcode::LD, 1, 8, Operands { { Reg16::BC, false }, { Reg8::A, true } } };
    case 0x03: return { Opcode::INC, 1, 8, Operands { { Reg16::BC, true } } };
    case 0x04: return { Opcode::INC, 1, 4, Operands { { Reg8::B, true } } };
    case 0x05: return { Opcode::DEC, 1, 4, Operands { { Reg8::B, true } } };
    case 0x06: return { Opcode::LD, 2, 8, Operands { { Reg8::B, true }, { Immediate8 { n8 }, true } } };
    case 0x07: return { Opcode::RLCA, 1, 4, std::nullopt };
    case 0x08: return { Opcode::LD, 3, 20, Operands { { Immediate16 { n16 }, false }, { StackPointer {}, true } } };
    case 0x09: return { Opcode::ADD, 1, 8, Operands { { Reg16::HL, true }, { Reg16::BC, true } } };
    case 0x0A: return { Opcode::LD, 1, 8, Operands { { Reg8::A, true }, { Reg16::BC, false } } };
    case 0x0B: return { Opcode::DEC, 1, 8, Operands { { Reg16::BC, true } } };
    case 0x0C: return { Opcode::INC, 1, 4, Operands { { Reg8::C, true } } };
    case 0x0D: return { Opcode::DEC, 1, 4, Operands { { Reg8::C, true } } };
    case 0x0E: return { Opcode::LD, 2, 8, Operands { { Reg8::C, true }, { Immediate8 { n8 }, true } } };
    case 0x0F: return { Opcode::RRCA, 1, 4, std::nullopt };
    case 0x10: return { Opcode::STOP, 2, 4, Operands { { Immediate8 { n8 }, true } } };
    case 0x11: return { Opcode::LD, 3, 12, Operands { { Reg16::DE, true }, { Immediate16 { n16 }, true } } };
    case 0x12: return { Opcode::LD, 1, 8, Operands { { Reg16::DE, false }, { Reg8::A, true } } };
    case 0x13: return { Opcode::INC, 1, 8, Operands { { Reg16::DE, true } } };
    case 0x14: return { Opcode::INC, 1, 4, Operands { { Reg8::D, true } } };
    case 0x15: return { Opcode::DEC, 1, 4, Operands { { Reg8::D, true } } };
    case 0x16: return { Opcode::LD, 2, 8, Operands { { Reg8::D, true }, { Immediate8 { n8 }, true } } };
    case 0x17: return { Opcode::RLA, 1, 4, std::nullopt };
    case 0x18: return { Opcode::JR, 2, 12, Operands { { ImmediateS8 { e8 }, true } } };
    case 0x19: return { Opcode::ADD, 1, 8, Operands { { Reg16::HL, true }, { Reg16::DE, true } } };
    case 0x1A: return { Opcode::LD, 1, 8, Operands { { Reg8::A, true}, { Reg16::DE, false } } };
    case 0x1B: return { Opcode::DEC, 1, 8, Operands { { Reg16::DE, true } } };
    case 0x1C: return { Opcode::INC, 1, 4, Operands { { Reg8::E, true } } };
    case 0x1D: return { Opcode::DEC, 1, 4, Operands { { Reg8::E, true } } };
    case 0x1E: return { Opcode::LD, 2, 8, Operands { { Reg8::E, true }, { Immediate8 { n8 }, true } } };
    case 0x1F: return { Opcode::RRA, 1, 4, std::nullopt };
    case 0x20: return { Opcode::JR, 2, { 12, 8 }, Operands { { Cond::NZ, true }, { ImmediateS8 { e8 }, true } } };
    case 0x21: return { Opcode::LD, 3, 12, Operands { { Reg16::HL, true }, { Immediate16 { n16 }, true } } };
    case 0x22: return { Opcode::LD, 1, 8, Operands { { Reg16::HL, false, true }, { Reg8::A, true } } };
    case 0x23: return { Opcode::INC, 1, 8, Operands { { Reg16::HL, true } } };
    case 0x24: return { Opcode::INC, 1, 4, Operands { { Reg8::H, true } } };
    case 0x25: return { Opcode::DEC, 1, 4, Operands { { Reg8::H, true } } };
    case 0x26: return { Opcode::LD, 2, 8, Operands { { Reg8::H, true }, { Immediate8 { n8 }, true } } };
    case 0x27: return { Opcode::DAA, 1, 4, std::nullopt };
    case 0x28: return { Opcode::JR, 2, { 12, 8 }, Operands { { Cond::Z, true }, { ImmediateS8 { e8 }, true } } };
    case 0x29: return { Opcode::ADD, 1, 8, Operands { { Reg16::HL, true }, { Reg16::HL, true } } };
    case 0x2A: return { Opcode::LD, 1, 8, Operands { { Reg8::A, true }, { Reg16::HL, false, true } } };
    case 0x2B: return { Opcode::DEC, 1, 8, Operands { { Reg16::HL, true } } };
    case 0x2C: return { Opcode::INC, 1, 4, Operands { { Reg8::L, true } } };
    case 0x2D: return { Opcode::DEC, 1, 4, Operands { { Reg8::L, true } } };
    case 0x2E: return { Opcode::LD, 2, 8, Operands { { Reg8::L, true }, { Immediate8 { n8 }, true } } };
    case 0x2F: return { Opcode::CPL, 1, 4, std::nullopt };
    case 0x30: return { Opcode::JR, 2, { 12, 8 }, Operands { { Cond::NC, true }, { ImmediateS8 { e8 }, true } } };
    case 0x31: return { Opcode::LD, 3, 12, Operands { { StackPointer {}, true }, { Immediate16 { n16 }, true } } };
    case 0x32: return { Opcode::LD, 1, 8, Operands { { Reg16::HL, false, false }, { Reg8::A, true } } };
    case 0x33: return { Opcode::INC, 1, 8, Operands { { StackPointer {}, true } } };
    case 0x34: return { Opcode::INC, 1, 12, Operands { { Reg16::HL, false } } };
    case 0x35: return { Opcode::DEC, 1, 12, Operands { { Reg16::HL, false } } };
    case 0x36: return { Opcode::LD, 2, 12, Operands { { Reg16::HL, false }, { Immediate8 {n8}, true } } };
    case 0x37: return { Opcode::SCF, 1, 4, std::nullopt };
    case 0x38: return { Opcode::JR, 2, { 12, 8 }, Operands { { Reg8::C, true }, { ImmediateS8 {e8}, true } } };
    case 0x39: return { Opcode::ADD, 1, 8, Operands { { Reg16::HL, true }, { StackPointer {}, true  } } };
    case 0x3A: return { Opcode::LD, 1, 8, Operands { { Reg8::A, true }, { Reg16::HL, false, false } } };
    case 0x3B: return { Opcode::DEC, 1, 8, Operands { { StackPointer {}, true } } };
    case 0x3C: return { Opcode::INC, 1, 4, Operands { { Reg8::A, true } } };
    case 0x3D: return { Opcode::DEC, 1, 4, Operands { { Reg8::A, true } } };
    case 0x3E: return { Opcode::LD, 2, 8, Operands { { Reg8::A, true }, { Immediate8 {n8}, true } } };
    case 0x3F: return { Opcode::CCF, 1, 4, std::nullopt };
    case 0x40: return { Opcode::LD, 1, 4, Operands { { Reg8::B, true }, { Reg8::B, true } } };
    case 0x41: return { Opcode::LD, 1, 4, Operands { { Reg8::B, true }, { Reg8::C, true } } };
    case 0x42: return { Opcode::LD, 1, 4, Operands { { Reg8::B, true }, { Reg8::D, true } } };
    case 0x43: return { Opcode::LD, 1, 4, Operands { { Reg8::B, true }, { Reg8::E, true } } };
    case 0x44: return { Opcode::LD, 1, 4, Operands { { Reg8::B, true }, { Reg8::H, true } } };
    case 0x45: return { Opcode::LD, 1, 4, Operands { { Reg8::B, true }, { Reg8::L, true } } };
    case 0x46: return { Opcode::LD, 1, 8, Operands { { Reg8::B, true }, { Reg16::HL, false } } };
    case 0x47: return { Opcode::LD, 1, 4, Operands { { Reg8::B, true }, { Reg8::A, true } } };
    case 0x48: return { Opcode::LD, 1, 4, Operands { { Reg8::C, true }, { Reg8::B, true } } };
    case 0x49: return { Opcode::LD, 1, 4, Operands { { Reg8::C, true }, { Reg8::C, true } } };
    case 0x4A: return { Opcode::LD, 1, 4, Operands { { Reg8::C, true }, { Reg8::D, true } } };
    case 0x4B: return { Opcode::LD, 1, 4, Operands { { Reg8::C, true }, { Reg8::E, true } } };
    case 0x4C: return { Opcode::LD, 1, 4, Operands { { Reg8::C, true }, { Reg8::H, true } } };
    case 0x4D: return { Opcode::LD,1 , 4, Operands { { Reg8::C, true }, { Reg8::L, true } } };
    case 0x4E: return { Opcode::LD, 1, 8, Operands { { Reg8::C, true }, { Reg16::HL, false } } };
    case 0x4F: return { Opcode::LD, 1, 4, Operands { { Reg8::C, true }, { Reg8::A, true } } };
    case 0x50: return { Opcode::LD, 1, 4, Operands { { Reg8::D, true }, { Reg8::B, true } } };
    case 0x51: return { Opcode::LD, 1, 4, Operands { { Reg8::D, true }, { Reg8::C, true } } };
    case 0x52: return { Opcode::LD, 1, 4, Operands { { Reg8::D, true }, { Reg8::D, true } } };
    case 0x53: return { Opcode::LD, 1, 4, Operands { { Reg8::D, true }, { Reg8::E, true } } };
    case 0x54: return { Opcode::LD, 1, 4, Operands { { Reg8::D, true }, { Reg8::H, true } } };
    case 0x55: return { Opcode::LD, 1, 4, Operands { { Reg8::D, true }, { Reg8::L, true } } };
    case 0x56: return { Opcode::LD, 1, 8, Operands { { Reg8::D, true }, { Reg16::HL, false } } };
    case 0x57: return { Opcode::LD, 1, 4, Operands { { Reg8::D, true }, { Reg8::A, true } } };
    case 0x58: return { Opcode::LD, 1, 4, Operands { { Reg8::E, true }, { Reg8::B, true } } };
    case 0x59: return { Opcode::LD, 1, 4, Operands { { Reg8::E, true }, { Reg8::C, true } } };
  }
  return { Opcode::Invalid, 1, 4, std::nullopt };
}
