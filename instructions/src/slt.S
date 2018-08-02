#include "init.S"

  li a0, 10
  li a1, 20
  nop
  nop			         //These 2 nops are needed to print the correct values when a trap occurs
  slt t1, a0, a1   //Check if 10 < 20
  slt t2, a1, a0   //Check if 20 < 10
  nop
  nop
  li a2, -30
  slt t3, a0, a2   //Check if 10 < -30
  slt t4, a2, a0   //Check if -30 < 10

#include "exit.S"
