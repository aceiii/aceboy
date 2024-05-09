#pragma once

#include "registers.h"

#include <memory>

struct State {
  bool ime;
};

class CPU {
public:
  void execute();
  void run();

  Registers* registers();

public:
  Registers regs;
  State state;
};
