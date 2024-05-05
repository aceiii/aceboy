#pragma once

#include "registers.h"

#include <memory>

class CPU {
public:
  CPU(Registers &regs);

  void execute();
  void run();

public:
  Registers &regs;
};
