all: start.o init.o nand.o main.o led.o uart.o lib1funcs.o print.o 
	arm-linux-ld -T test.lds $^ -o test.elf
	arm-linux-objcopy -O binary -S test.elf test.bin
	arm-linux-objdump -D test.elf > test.dis

clean:
	rm *.bin *.o *.elf *.dis
	
%.o : %.c
	arm-linux-gcc -march=armv4 -c -o $@ $<

%.o : %.S
	arm-linux-gcc -march=armv4 -c -o $@ $<