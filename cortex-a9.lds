ENTRY(main)

SECTIONS {
	 . = 0x83000000;
	 .text : { * (.text); }
	 .data : { * (.data); }
}
