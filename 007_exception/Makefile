all: sdram.o uart.o main.o
	arm-linux-gcc -c -o start.o start.S
	arm-linux-ld -Ttext 0 start.o sdram.o uart.o main.o -o und.elf
	arm-linux-objcopy -O binary -S und.elf und.bin
	arm-linux-objdump -D und.elf > und.dis

%.o: %.c
	arm-linux-gcc -c -o $@ $<
	
clean:
	rm *.bin *.o *.elf *.dis
