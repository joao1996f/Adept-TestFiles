#include "init.S"

  li a0, 16
  li a1, 2
  nop
  nop			         //These 2 nops are needed to print the correct values when a trap occurs
  sll t1, a0, a1

#include "exit.S"
