#include "led.h"
#include "s3c2440_soc.h"

void led_config(void){
	GPFCON &= ~0x3f00;
	GPFCON |= 0x1500;

	GPFUP |= 0x70;

	GPFDAT |= 0x70;
}

void set_led(int led, int val){
	if(led!=LED1 && led!=LED2 && led!=LED4) return;
	if(val!=LED_ON && val!=LED_OFF && val!=LED_REV) return;
	switch(val){
		case LED_ON:{
			GPFDAT &= ~(0x01<<led);
			break;
		}
		case LED_OFF:{
			GPFDAT |= (0x01<<led);
			break;
		}
		case LED_REV:{
			GPFDAT ^= (0x01<<led);
			break;
		}
		default:break;
	}
}

