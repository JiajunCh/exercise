#include "uart.h"
#include "clk.h"
#include "wdg.h"
#include "led.h"
#include "s3c2440_soc.h"

int main(void){
	char temp_char = 0;
	clk_config();
	wdg_config();
	uart_config();
	led_config();

	while(1){
		temp_char = get_char();
		if(-1 != temp_char){
			put_char(temp_char);
			set_led(LED1, LED_REV);

			if('\n' == temp_char)
				set_led(LED2, LED_REV);

			if('\r' == temp_char)
				set_led(LED4, LED_REV);
		}
	}
	return 0;
}



