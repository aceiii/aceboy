#pragma once

#include "decoder.h"
#include "registers.h"
#include "memory.h"

#include <memory>

struct State {
  bool ime;
  bool halt;
  bool hard_lock;
};

class CPU {
public:
  void execute();
  void run();

public:
  Memory memory;
  Registers regs;
  State state;
  Decoder decoder;
};
