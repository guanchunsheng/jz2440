src := $(shell ls *.c *.s)
obj := $(patsubst %.s, %.o, $(src))
obj := $(patsubst %.c, %.o, $(obj))
int_key_led.bin : $(obj)
	arm-linux-ld -Ttext 0x00000000 $^ -o int_key_led_elf
	arm-linux-objcopy -O binary -S int_key_led_elf int_key_led.bin
%.o : %.c
	arm-linux-gcc -c -o $@ $<
%.o : %.s
	arm-linux-gcc -c -o $@ $<
clean :
	rm *.o *_elf *.bin
