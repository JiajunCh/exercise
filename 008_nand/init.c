#include "nand.h"
#include "s3c2440_soc.h"

static unsigned int is_norboot(void);

void sdram_init(void)
{
	BWSCON = 0x22000000;

	BANKCON6 = 0x18001;
	BANKCON7 = 0x18001;

	REFRESH  = 0x8404f5;

	BANKSIZE = 0xb1;

	MRSRB6   = 0x20;
	MRSRB7   = 0x20;
}

int sdram_test(void)
{
	volatile unsigned char *p = (volatile unsigned char *)0x30000000;
	int i;

	// write sdram
	for (i = 0; i < 1000; i++)
		p[i] = 0x55;

	// read sdram
	for (i = 0; i < 1000; i++)
		if (p[i] != 0x55)
			return -1;

	return 0;
}

void copy2sdram(void)
{
	/* 要从lds文件中获得 __code_start, __bss_start
	 * 然后从0地址把数据复制到__code_start
	 */

	extern int __code_start, __bss_start;

	volatile unsigned int *dest = (volatile unsigned int *)&__code_start;
	volatile unsigned int *end = (volatile unsigned int *)&__bss_start;
	volatile unsigned int *src = (volatile unsigned int *)0;

	if(is_norboot()){
		while (dest < end)
		{
			*dest++ = *src++;
		}
	}
	else{
		unsigned int len = (int)(&__bss_start) - (int)(&__code_start);
		nand_init();
		nand_read((unsigned int)src, (unsigned char *)dest, len);
	}
}


void clean_bss(void)
{
	/* 要从lds文件中获得 __bss_start, _end
	 */
	extern int _end, __bss_start;

	volatile unsigned int *start = (volatile unsigned int *)&__bss_start;
	volatile unsigned int *end = (volatile unsigned int *)&_end;


	while (start <= end)
	{
		*start++ = 0;
	}
}

unsigned int is_norboot(void){
	volatile unsigned int *p = (unsigned int *)0;
	
	*p = 0x55AAAA55;
	if(*p == 0x55AAAA55)
		return 1;
	else
		return 0;
}


