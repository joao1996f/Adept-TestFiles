  .section .text
  .globl _start
  .type _start,@function
_start:
  // Initialize registers with 0
  call main
