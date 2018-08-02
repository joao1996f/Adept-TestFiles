#include "init.S"

  li a0, 10
  li a1, 20
  nop
  nop               //These 2 nops are needed to print the correct values when a trap occurs
  sltu t1, a0, a1   //Check if 10 < 20
  sltu t2, a1, a0   //Check if 20 < 10

#include "exit.S"
