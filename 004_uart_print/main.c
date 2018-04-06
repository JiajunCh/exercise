#include "print.h"
#include "uart.h"
#include "wdg.h"
#include "s3c2440_soc.h"

int main(void){
	wdg_config();
	uart_config();

	printf("hello wold!\n");
	printf("char    : %c\n", 'A');
	printf("string  : %s\n", "abc");
	
	printf("dec     : %d\n", 123);
	printf("dec 020 : %d\n", 020);
	printf("dec 8   : %8d\n", 123);
	printf("dec 08  : %08d\n", 123);
	printf("dec -   : %d\n", -123);
	printf("dec -8  : %8d\n", -123);
	printf("dec -08 : %08d\n", -123);
	printf("dec 8   : %8d\n", 123456789);
	printf("dec 08  : %08d\n", 123456789);
	
	printf("oct     : %o\n", 1234);
	printf("oct 020 : %o\n", 020);
	printf("oct 8   : %8o\n", 1234);
	printf("oct 08  : %08o\n", 1234);
	
	printf("hex     : %x\n", 12345);
	printf("hex 8   : %8x\n", 12345);
	printf("hex 08  : %08x\n", 12345);
	
	printf("usd     : %u\n", 123456);
	printf("usd 8   : %8u\n", 123456);
	printf("usd 08  : %08u\n", 123456);
		
	while(1);
	return 0;
}



