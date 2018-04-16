  .section .init
  .globl _start
  .type _start,@function
_start:
  .option push
  .option norelax
  la gp, __global_pointer$
  .option pop
  la sp, _sp

	/* Clear bss section */
	la a0, __bss_start
	la a1, _end
	bgeu a0, a1, 2f
1:
	sw zero, (a0)
	addi a0, a0, 4
	bltu a0, a1, 1b
2:

	auipc ra, 0
	addi sp, sp, -16
	sw ra, 8(sp)

  // We don't support argv or argc. So they are zeroed at the start
  li a0, 0
  li a1, 0
  call main
  tail __exit

  // When program is done loop indefinitely
loop:
  j loop
