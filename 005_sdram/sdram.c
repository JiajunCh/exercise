#include "sdram.h"
#include "s3c2440_soc.h"

void sdram_init(void){
	BWSCON &= ~0x3000000;
	BWSCON = 0x2000000;
	BANKCON6 = 0x18001;
	REFRESH = 0x8404F5;
	BANKSIZE = 0xB1;
	MRSRB6 = 0x20;
}

int sdram_test(void){
	volatile char *p = (volatile char *)0x30000000;
	int i = 0;

	for(i=0; i<1024; i++){
		p[i] = 0x55;
	}

	for(i=0; i<1024; i++){
		if(p[i] != 0x55)
			return -1;
	}
	return 0;
}


