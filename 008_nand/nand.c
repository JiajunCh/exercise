#include "nand.h"
#include "printf.h"
#include "s3c2440_soc.h"

#define TACLS	0	/* NFCON[13:12] */
#define TWRPH0	1	/* NFCON[10:8] */
#define TWRPH1	0	/* NFCON[6:4] */

void nand_init(void){
	/*设置NAND FLASH的时序*/
	NFCONF &= ~((0x3<<12)|(0x7<<8)|(0x7<<4));
	NFCONF |= ((TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4));
	/*使能NAND FLASH控制器,初始化ECC，禁止片选*/
	NFCONT = (1<<4) | (1<<1) | (1<<0);
}

void nand_select(void){
	/*使能片选*/
	NFCONT &= ~(0x1<<1);
}

void nand_deselect(void){
	/*禁止片选*/
	NFCONT |= (0x1<<1);
}

void wait_ready(void){
	while (!(NFSTAT & 0x1));
}

void get_nand_id(void){
	unsigned char nand_id[5]={0};
	unsigned char i = 0;
	nand_select();
	NFCMD = 0x90;
	NFADDR = 0x00;
	
	for(i=0; i<5; i++)
		nand_id[i] = (unsigned char)NFDATA;
	
	printf("Maker code  : 0x%x\r\n",nand_id[0]);
	printf("Device code : 0x%x\r\n",nand_id[1]);
	printf("3rd byte	: 0x%x\r\n",nand_id[2]);
	printf("4th byte	: 0x%x\r\n",nand_id[3]);
	printf("Page size	: %dKB\r\n",1<<(nand_id[3]&0x03));
	printf("Block size	: %dKB\r\n",64<<((nand_id[3]&0x30)>>4));
	printf("5th byte    : 0x%x\n\r",nand_id[4]);
	
	nand_deselect();
}

unsigned int nand_read(unsigned int addr, unsigned char *buf, unsigned int len){
	unsigned int col = addr&(2048-1);
	unsigned int page = addr>>11;
	unsigned int i = 0;
	
	while(i < len){
		/* cmd 0x00 */
		NFCMD = 0x00;
		/* column address */
		NFADDR = col&0xFF;
		NFADDR = (col>>8)&0xFF;
		/* row address */
		NFADDR = page&0xFF;
		NFADDR = (page>>8)&0xFF;
		NFADDR = (page>>16)&0xFF;
		/* cmd 0x30 */
		NFCMD = 0x30;
		/* wait busy */
		wait_ready();
		/* read data */
		for(; col<2048; i++){
			if(i >= len) break;
			buf[i] = (unsigned char)NFDATA;
		}
		col = 0;
		page ++;
	}
	return i;
}

unsigned int nand_write(unsigned int addr, unsigned char *buf, unsigned int len){
	unsigned int col = addr&(2048-1);
	unsigned int page = addr>>11;
	unsigned int i = 0, try = 0, status = 0;;
	
	while(i < len){
		/* cmd 0x80 : input command*/
		NFCMD = 0x80;
		/* column address */
		NFADDR = col&0xFF;
		NFADDR = (col>>8)&0xFF;
		/* row address */
		NFADDR = page&0xFF;
		NFADDR = (page>>8)&0xFF;
		NFADDR = (page>>16)&0xFF;
		/* write data */
		for(; col<2048; i++){
			if(i >= len) return;
			NFDATA = buf[i];
		}
		/* cmd 0x10 : star program*/
		NFCMD = 0x10;
		/* wait busy */
		wait_ready();
		/* cmd 0x70 : read status*/
		NFCMD = 0x70;
		status = (unsigned char)NFDATA;
		if(!(status&0x01)){
			col = 0;
			page++;
			try = 0;
		}
		else
			try++;
		if(try>3)
			break;
	}
	return i;
}

int nand_erase(unsigned int addr, unsigned int len){
	unsigned int page = 0, status = 0;
	unsigned int block_size = 128<<10;
	if(addr & (block_size-1))
		printf("nand_erase err, addr must be block align\r\n");
	if(len & (block_size-1))
		printf("nand_erase err, erase size must be block align\r\n");
	while(len > 0){
		page = addr>>11;
		/* cmd 0x60 : auto erase */
		NFCMD = 0x60;
		/* row address */
		NFADDR = page&0xFF;
		NFADDR = (page>>8)&0xFF;
		NFADDR = (page>>16)&0xFF;
		/* cmd 0xD0 : start erase */
		NFCMD = 0xD0;
		/* wait busy */
		wait_ready();
		/* cmd 0x70 : read status*/
		NFCMD = 0x70;
		status = (unsigned char)NFDATA;
		if((status&0x01))
			printf("nand block[0x%x] erase fail\r\n",addr);
		len -= block_size;
		addr += block_size;
	}
}

void nand_test(void){
	int i = 0, j = 0;
	char buf[64] = {0};
	nand_read(0, buf, 64);
	for(i=0; i<4; i++){
		for(j=0; j<16; j++){
			printf("%2x ",buf[i*j]);
		}
		printf("   ; ");
		
		for(j=0; j<16; j++){
			if(buf[i*j]>=' ' && buf[i*j]<='~')
				putchar(buf[i*j]);
			else
				putchar('.');
		}
		printf("\r\n");
	}
}


