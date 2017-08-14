#ifndef _INT_KEY_LED_H

#define _INT_KEY_LED_H

/*
 * LED1,LED2,LED4对应GPF4、GPF5、GPF6
 */
#define GPF_OUT(x)	(1 << ((x) * 2))
#define GPF_MSK(x)	(3 << ((x) * 2))
#define GPG_MSK(x)	GPF_MSK(x)

/*
 * S2,S3,S4对应GPF0、GPF2、GPG3
 */
#define GPF_EINT(x)	(2 << ((x) * 2))
#define GPG_EINT(x) GPF_EINT(x)

#define GPFCON		(*(volatile unsigned long *)0x56000050)
#define GPFDAT 		(*(volatile unsigned long *)0x56000054)
#define GPGCON		(*(volatile unsigned long *)0x56000060)
#define INTOFFSET	(*(volatile unsigned long *)0x4a000014)
#define EINTMASK	(*(volatile unsigned long *)0x560000a4)
#define PRIORITY	(*(volatile unsigned long *)0x4a00000c)
#define INTMSK		(*(volatile unsigned long *)0x4a000008)
#define EINTPEND	(*(volatile unsigned long *)0x560000a8)
#define SRCPND		(*(volatile unsigned long *)0x4a000000)
#define INTPND		(*(volatile unsigned long *)0x4a000010)

/* LED灯对应的二进制数字，可以表示0到7 */
#define LED_NUM(x)  (~(((x) & ~((~0) << 3)) << 4))
#define LED_MSK(x)	(1 << ((x) + 4))

#endif
