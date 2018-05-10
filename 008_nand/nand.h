#ifndef _NAND_H_ 
#define _NAND_H_ 

void nand_init(void);
void get_nand_id(void);
unsigned int nand_read(unsigned int addr, unsigned char *buf, unsigned int len);
unsigned int nand_write(unsigned int addr, unsigned char *buf, unsigned int len);
int nand_erase(unsigned int addr, unsigned int len);
void nand_test(void);

#endif
