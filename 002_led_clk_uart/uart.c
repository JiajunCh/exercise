#include "uart.h"
#include "s3c2440_soc.h"

void uart_config(void){
	/* 初始化pin脚 rx=GPH3，tx=GPH2     */
	GPHCON &= ~((0x03<<4) | (0x03<<6));
	GPHCON |= ((0x02<<4) | (0x02<<6));
	GPHUP |= ((0x01<<2) | (0x01<<3));

	/* 设置波特率 */
	/* UBRDIVn = (int)(UART_clk / (buadrate x 16)) – 1 */
	UBRDIV0 = 26;

	ULCON0 = 0x11;	/*  8N1 */
	UCON0 = ((0x1<<2) | 0x01);
}

int put_char(int c){
	while(!(UTRSTAT0&(0x01<<2)))
		UTXH0 = (unsigned char)c;
	return 0;
}

int get_char(void){
	if(UTRSTAT0&0x01)
		return (int)URXH0;
	else
		return -1;
}




