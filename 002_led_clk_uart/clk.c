#include "clk.h"
#include "s3c2440_soc.h"

void clk_config(void){
	LOCKTIME = 0xffffffff;
	CLKDIVN = (0x10<<1 | 0x1);	//Hdivn[2:1] Pdivn[0]
	MPLLCON = (0x5c<<12 | 0x1<<4 | 0x1);	//Mdiv[19:12] Pdiv[9:4] Sdiv[1:0]
}

