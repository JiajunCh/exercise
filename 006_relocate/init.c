#include "init.h"
#include "s3c2440_soc.h"

void sdram_init(void){
	BWSCON &= ~0x3000000;
	BWSCON = 0x2000000;
	BANKCON6 = 0x18001;
	REFRESH = 0x8404F5;
	BANKSIZE = 0xB1;
	MRSRB6 = 0x20;
}

void wdg_config(void){
	WTCON = 0;
}

void cpy_data2sdram(void){
	extern int __code_start, __bss_start;
	volatile unsigned int *src = (volatile unsigned int *)0;
	volatile unsigned int *dest = (volatile unsigned int *)__code_start;
	volatile unsigned int *end = (volatile unsigned int *)__bss_start;
	
	while(dest < end)
		*dest++ = *src++;
}

void clr_bss(void){
	extern int __bss_start, __end;
	volatile unsigned int *start = (volatile unsigned int *)__bss_start;
	volatile unsigned int *end = (volatile unsigned int *)__end;

	while(start <= end)
		*start++ = 0;
}


