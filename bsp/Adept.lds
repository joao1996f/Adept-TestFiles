/* Whem implementing software the programmer must select the intended memory
positions without overwriting the program.*/

OUTPUT_ARCH ( "riscv" )

ENTRY ( _start )

MEMORY
{
  rom (r!wxai) : ORIGIN = 0x10000000, LENGTH = 4K
  ram (wxa!ri) : ORIGIN = 0x80000000, LENGTH = 32K
}

SECTIONS
{
  __stack_size = 4K;

  . = 0x10000;
  .init : {
    KEEP (*(SORT_NONE(.init)))
  } >rom

  .text : {
    *(.text .text.*)
  } >rom

  .fini : {
    KEEP (*(SORT_NONE(.fini)))
  } >rom

  PROVIDE ( __etext = . );
  PROVIDE ( _etext = . );
  PROVIDE ( etext = . );

  .rodata : {
    *(.rdata)
    *(.rodata .rodata.*)
  } >rom

  .data : {
    *(.data .data.*)
    *(.sdata .sdata.*)
    PROVIDE( __global_pointer$ = . );
  } >ram

  PROVIDE ( _fbss = . );
  PROVIDE ( __bss_start = . );
  .bss : {
    *(.sbss)
    *(.bss .bss.*)
    *(COMMON)
  } >ram

  PROVIDE ( _end = . );
  PROVIDE ( end = . );

  .stack ORIGIN(ram) + LENGTH(ram) - __stack_size : {
    PROVIDE ( _heap_end = . );
    . = __stack_size;
    PROVIDE( _sp = . );
  } >ram
}
