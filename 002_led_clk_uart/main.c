#include "uart.h"
#include "wdg.h"
#include "led.h"
#include "s3c2440_soc.h"

int main(void){
	int temp_char = 0;
	wdg_config();
	uart_config();
	led_config();

	set_led(LED1, LED_ON);
	set_led(LED2, LED_ON);
	set_led(LED4, LED_ON);
	puts("hello world!\r\n");

	while(1){
		temp_char = get_char();
		put_char(temp_char);
		set_led(LED1, LED_REV);

		if('\n' == temp_char)
			set_led(LED2, LED_REV);

		if('\r' == temp_char)
			set_led(LED4, LED_REV);
	}
	return 0;
}



