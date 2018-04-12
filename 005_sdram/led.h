#ifndef _LED_H
#define _LED_H

#define LED_ON		(0)
#define LED_OFF		(1)
#define LED_REV		(2)

#define	LED1		(4)
#define	LED2		(5)
#define	LED4		(6)

void led_config(void);
void set_led(int led, int val);

#endif


