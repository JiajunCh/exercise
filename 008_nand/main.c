#include "print.h"
#include "nand.h"
#include "uart.h"
#include "init.h"
#include "s3c2440_soc.h"

int main(void)
{
	uart0_init();
	get_nand_id();

	while (1)
	{
		
	}

	
	return 0;
}



