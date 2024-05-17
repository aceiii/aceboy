#include "cpu.h"

#include <variant>

template <class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

void instr_add8(uint8_t &dst, uint8_t &src, Flags &f) {
  dst = dst + src;
  f.set(Flag::Z, dst == 0);
  f.set(Flag::N, 0);
}

void CPU::execute() {
  Instruction instr = decoder.decode(&memory, regs.pc);

  uint8_t *dst_ptr = nullptr;
  uint8_t *src_ptr = nullptr;

  bool has_operands = instr.operands.has_value();
  if (has_operands) {
    auto operands = instr.operands.value();

    std::visit(overloaded {
        [&, dst=operands.dst] (const Reg8 &reg) {
          if (dst.immediate) {
            dst_ptr = &regs.at(reg);
          } else {
            dst_ptr = &memory.at(regs.get(reg));
          }
        },
        [] (auto&) {}
    }, operands.dst.op);
  }

  switch (instr.opcode) {
  case Opcode::LD: instr_add8(*dst_ptr, *src_ptr, regs.flags);  break;
  default:
    break;
  }
}

void CPU::run() {
}
