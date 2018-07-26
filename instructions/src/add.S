#include "init.S"

  li a0, 0x9C
  li a1, 0x01
  nop
  nop			         //This 2 nops are needed to print the correct values when a trap occurs
  add t1, a0, a1

#include "exit.S"
