#include "print.h"
#include "uart.h"
#include "wdg.h"
#include "led.h"
#include "s3c2440_soc.h"

int main(void){
	wdg_config();
	uart_config();
	led_config();
	set_led(LED1, LED_ON);
	set_led(LED2, LED_ON);
	set_led(LED4, LED_ON);

	printf("hello wold!\r\n");
	printf("char    : %c\r\n", 'A');
	printf("string  : %s\r\n", "abc");
	
	printf("dec     : %d\r\n", 123);
	printf("dec 020 : %d\r\n", 020);
	printf("dec 8   : %8d\r\n", 123);
	printf("dec 08  : %08d\r\n", 123);
	printf("dec -   : %d\r\n", -123);
	printf("dec -8  : %8d\r\n", -123);
	printf("dec -08 : %08d\r\n", -123);
	printf("dec 8   : %8d\r\n", 123456789);
	printf("dec 08  : %08d\r\n", 123456789);
	
	printf("oct     : %o\r\n", 1234);
	printf("oct 020 : %o\r\n", 020);
	printf("oct 8   : %8o\r\n", 1234);
	printf("oct 08  : %08o\r\n", 1234);
	
	printf("hex     : %x\r\n", 12345);
	printf("hex 8   : %8x\r\n", 12345);
	printf("hex 08  : %08x\r\n", 12345);
	
	printf("usd     : %u\r\n", 123456);
	printf("usd 8   : %8u\r\n", 123456);
	printf("usd 08  : %08u\r\n", 123456);
		
	while(1);
	return 0;
}



