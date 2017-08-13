led_on_c.bin : led_on_c.c crt0.s
	arm-linux-gcc -c led_on_c.c -o led_on_c.o
	arm-linux-gcc -c crt0.s -o crt0.o
	arm-linux-ld -Ttext 0x00000000 crt0.o led_on_c.o -o led_on_c_elf
	arm-linux-objcopy -O binary -S led_on_c_elf led_on_c.bin
clean :
	rm *.o led_on_c_elf led_on_c.bin
