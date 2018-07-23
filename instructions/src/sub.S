#include "init.S"

  lui a0, 0x9C
  lui a1, 0x01
  nop
  nop
  sub t1, a0, a1

#include "exit.S"
