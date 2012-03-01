ENTRY(ResetISR)

MEMORY
{
    SRAM (rwx) : ORIGIN = 0x00000000, LENGTH = 1M
}

SECTIONS
{
	.text : 
	{ 
	  KEEP(*(.isr_vector));
	  * (.text*);
	  * (.rodata*);
	  * (.init*);
	  * (.fini*);
	} > SRAM

	.data : AT (ADDR(.text) + SIZEOF(.text))
	{
	  * (.data);
	  * (.bss);
	} > SRAM

	.resource_size :
	{
	  KEEP(*(.resource_size));
	} > SRAM

	.resource_table :
	{
	  KEEP(*(.resource_table));
	} > SRAM
}
