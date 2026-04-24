SECTIONS
{
	. = 0x00556AD0;
	.text : { *(.text) }
	.rodata : { *(.rodata) }
	.data : { *(.data) }
	_gp = ALIGN(16) + 0x7ff0;
}