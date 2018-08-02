#include "init.S"

  li a0, 10
  li a1, 20
  nop
  nop			         //These 2 nops are needed to print the correct values when a trap occurs
  slt t1, a0, a1
  slt t2, a1, a0

#include "exit.S"
