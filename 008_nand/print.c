 
#include "print.h"
#include "uart.h"

#define MAX_NUMBER_BYTES	64

#define _out_putchar	putchar

typedef char *  va_list;
#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
#define va_start(ap,v)  ( ap = (va_list)&v + _INTSIZEOF(v) )
#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap)      ( ap = (va_list)0 )

unsigned char hex_tab[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

static int outc(int c){
	_out_putchar(c);
	return 0;
}

static int outs(const char *s){
	while(*s != '\0')
		_out_putchar(*s++);
}

static int out_num(long n, int radix, char lead, int maxwidth){
	char buffer[MAX_NUMBER_BYTES];
	char *s = &buffer[MAX_NUMBER_BYTES];
	unsigned long temp;
	
	*(--s) = '\0';
	
	if(n < 0)
		temp = -n;
	else
		temp = n;
	
	do{
		*(--s) = hex_tab[temp % radix];
		temp /= radix;
		maxwidth--;
	}while(temp > 0);

	while(maxwidth--)
		*(--s) = lead;
	
	if(n < 0)
		*(--s) = '-';

	outs(s);
	return 0;
}

static int vprintf(const char *fmt, va_list ap){
	char lead=' ';
	int  maxwidth=0;
	
	for( ; *fmt != 0; fmt++){
		if(*fmt != '%'){
			outc(*fmt);
			continue;
		}
		
		lead=' ';
		maxwidth=0;
		fmt++;
		
		if(*fmt == '0'){
			lead = '0';
			fmt++;
		}
		
		while(*fmt>='0' && *fmt<='9'){
			maxwidth *= 10;
			maxwidth += (*fmt - '0');
			fmt++;
		}
		
		switch(*fmt){
			case 'c' : outc(va_arg(ap, int)); break;
			case 's' : outs(va_arg(ap, char *)); break;
			case 'd' : out_num(va_arg(ap, int), 10, lead, maxwidth); break;
			case 'o' : out_num(va_arg(ap, unsigned int), 8, lead, maxwidth); break;
			case 'u' : out_num(va_arg(ap, unsigned int), 10, lead, maxwidth); break;
			case 'x' : out_num(va_arg(ap, unsigned int), 16, lead, maxwidth); break;
			default : outc(*fmt); break;
		}
	}
	return 0;
}

int printf(const char *fmt, ...){
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	return 0;
}

