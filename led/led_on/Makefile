led_on.bin : led_on.s
	arm-linux-gcc -c -o led_on.o led_on.s
	arm-linux-ld -Ttext 0x00000000 -o led_on_elf led_on.o
	arm-linux-objcopy -O binary -S led_on_elf led_on.bin
clean :
	rm *.o led_on_elf led_on.bin