// This 3 nops are necessary so that the final instructions of the program in 
// the pipeline are execute before the end of the simulation
nop
nop
nop
// This instruction should kill the simulation running in Adept  
lui a4, 0xdead0

loop:
  j loop
