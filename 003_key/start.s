
.text
.global _start

_start:
    ldr sp,=0x1000
    bl main

_halt:
    b _halt
	