OUTPUT_ARCH("riscv")
OUTPUT_FORMAT("elf32-littleriscv")

ENTRY(_head)

MEMORY
{
  ROM (rxai!w)    : ORIGIN = 0x0,         LENGTH = 0x8000
  EFLASH (rxai!w) : ORIGIN = 0x400000,    LENGTH = 0x40000
  RAM (wxa!ri)    : ORIGIN = 0x800000,    LENGTH = 0x200000
  FLASH (rxai!w)  : ORIGIN = 0x20000000,  LENGTH = 0x200000
}

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0xF000;    /* 4 KiB*/
_Min_Stack_Size = 0xF000;   /* 4 KiB*/

SECTIONS
{
  /* The program code */
  .head : {
    . = ALIGN(4);
    *( .text.init )
    . = ALIGN(4);
  } >FLASH

  .text : {
    . = ALIGN(4);
    _stext = . ;
    *( .text )
    *( .text* )

    KEEP (*( .init ))
    KEEP (*( .fini ))

    . = ALIGN(4);
    _etext = . ;
  } >RAM AT>FLASH
  _sitext = LOADADDR(.text); /* LMA start of data section */

  /* Constant data */
  .rodata : {
    . = ALIGN(4);
    _srodata = . ;
    *( .rodata .rodata* )
    *( .srodata .srodata* )
    . = ALIGN(4);
    _erodata = . ;
  } >RAM AT>FLASH
  _sirodata = LOADADDR(.rodata); /* LMA start of data section */

  /* Initialized data sections */
  .data : {
    . = ALIGN(4);
    _sdata = .;

    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);

    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);

    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);

    *( .data .data* )
    . = ALIGN(4);
    PROVIDE( __global_pointer$ = . + 0x800 );
    *( .sdata .sdata* )
    . = ALIGN(4);
    _edata = .;
  } >RAM AT>FLASH
  _sidata = LOADADDR(.data); /* LMA start of data section */

  /* Unitialized data section */
  . = ALIGN(4);
  .bss : {
    _sbss = .;
    *( .sbss .sbss* )
    *( .bss .bss* )
    *( COMMON )
    . = ALIGN(4);
    _ebss = .;
  } >RAM

  /* User heap stack section, used to check that there is enough RAM left*/
  ._user_heap_stack : {
    . = ALIGN(4);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(4);
  } >RAM

  /* Remove information from the standard libraries 
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }
  */
}
