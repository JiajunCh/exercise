all:
	arm-linux-gcc -c -o uart.o uart.c
	arm-linux-gcc -c -o wdg.o wdg.c
	arm-linux-gcc -c -o led.o led.c
	arm-linux-gcc -c -o lib1funcs.o lib1funcs.S
	arm-linux-gcc -c -o print.o print.c
	arm-linux-gcc -c -o main.o main.c
	arm-linux-gcc -c -o start.o start.S
	arm-linux-ld -Ttext 0 -Tdata 0xef0 start.o uart.o wdg.o led.o lib1funcs.o print.o main.o -o printf.elf
	arm-linux-objcopy -O binary -S printf.elf printf.bin
	arm-linux-objdump -D printf.elf > printf.dis
clean:
	rm *.bin *.o *.elf *.dis
