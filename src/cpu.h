#pragma once

#include "registers.h"

#include <memory>

class CPU {
public:
  void execute();
  void run();

  Registers* registers();

public:
  Registers regs;
};
