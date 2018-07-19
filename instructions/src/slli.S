#include "init.S"

  li a1, 15
  nop
  nop			//This 2 nops are needed to print the correct values when a trap occurs
  slli a3, a1, 3

#include "exit.S"
