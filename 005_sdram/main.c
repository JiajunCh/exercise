#include "sdram.h"
#include "uart.h"
#include "wdg.h"
#include "led.h"
#include "s3c2440_soc.h"

int main(void){
	wdg_config();
	uart_config();
	led_config();
	sdram_init();
	
	set_led(LED1, LED_ON);
	set_led(LED2, LED_OFF);
	set_led(LED4, LED_ON);

	if(0 == sdram_test())
		puts("sdram test ok\r\n");
	else
		puts("sdram test fail\r\n");
		
	while(1);
	return 0;
}



