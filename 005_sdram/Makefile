all:
	arm-linux-gcc -c -o uart.o uart.c
	arm-linux-gcc -c -o wdg.o wdg.c
	arm-linux-gcc -c -o led.o led.c
	arm-linux-gcc -c -o lib1funcs.o lib1funcs.S
	arm-linux-gcc -c -o main.o main.c
	arm-linux-gcc -c -o sdram.o sdram.c
	arm-linux-gcc -c -o start.o start.S
	arm-linux-ld -Ttext 0 start.o uart.o wdg.o led.o lib1funcs.o main.o sdram.o -o sdram.elf
	arm-linux-objcopy -O binary -S sdram.elf sdram.bin
	arm-linux-objdump -D sdram.elf > sdram.dis
clean:
	rm *.bin *.o *.elf *.dis
