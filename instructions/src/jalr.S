#include "init.S"

// Test instructions here
  lui a1, 0x10000
  addi a1, a1, 0x7c
// Should jump to exit
  jalr t0, a1, 0x18
  addi t1, t1, 1
  addi t1, t1, 1
  addi t1, t1, 1
  addi t2, t2, 2

#include "exit.S"
