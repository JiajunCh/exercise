
#define rWTCON (*(volatile unsigned int *)0x53000000)

#define rGPFCON (*(volatile unsigned int *)0x56000050)
#define rGPFDAT (*(volatile unsigned int *)0x56000054)
#define rGPFUP  (*(volatile unsigned int *)0x56000058)

#define rGPGCON (*(volatile unsigned int *)0x56000060)
#define rGPGDAT (*(volatile unsigned int *)0x56000064)
#define rGPGUP  (*(volatile unsigned int *)0x56000068)

#define get_Key2() (rGPFDAT&0x01)
#define get_Key3() (rGPFDAT&0x04)
#define get_Key4() (rGPGDAT&0x08)

#define LED1_ON() (rGPFDAT &= ~0x10)
#define LED1_OFF() (rGPFDAT |= 0x10)
#define LED2_ON() (rGPFDAT &= ~0x20)
#define LED2_OFF() (rGPFDAT |= 0x20)
#define LED3_ON() (rGPFDAT &= ~0x40)
#define LED3_OFF() (rGPFDAT |= 0x40)

void delay(int tick){
	while(--tick > 0);
}

int main(void){
    unsigned int i=0;
	
	rWTCON &= ~(0x20);	/* 关闭看门狗 */
	
    rGPFCON |= 0x1500;	/* GPF_456输出*/
	rGPFCON &= ~0x33;	/* GPF_02输入*/
    rGPFUP &= ~0x75;	/* GPF_02456上拉*/
	rGPFDAT |= 0x70;	/* GPF_456输出1 */
	
	rGPGCON &= ~0xC0;	/* GPG_3输入*/
    rGPGUP &= ~0x08;	/* GPG_3上拉*/
    
    while(1){
		if(get_Key2())	/* 如果按键弹起 */
			LED1_OFF();	/* 则关闭LED1 */
		else
			LED1_ON();	/* 否则打开LED1 */
		
		if(get_Key3())
			LED2_OFF();
		else
			LED2_ON();
		
		if(get_Key4())
			LED3_OFF();
		else
			LED3_ON();
    }
    return 0;
}
