unsigned int *TERMINATE_SIM_ADDRESS = 0x00000000;

void __exit(void) { *TERMINATE_SIM_ADDRESS = 0xdead0000; }
