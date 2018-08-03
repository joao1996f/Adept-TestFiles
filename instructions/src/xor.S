#include "init.S"

  li a0, 222
  li a1, 121
  nop
  nop                   //These 2 nops are needed to print the correct values when a trap occurs
  xor t1, a0, a1

#include "exit.S"
