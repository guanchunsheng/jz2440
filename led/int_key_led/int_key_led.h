#ifndef _INT_KEY_LED_H

#define _INT_KEY_LED_H

/*
 * LED1,LED2,LED4对应GPF4、GPF5、GPF6
 */
#define GPF_OUT(x)	(1 << ((x) * 2))
#define GPF_MSK(x)	(3 << ((x) * 2))

/*
 * S2,S3,S4对应GPF0、GPF2、GPG3
 */
#define GPF_EINT(x)	(2 << ((x) * 2))


#define GPFCON		(*(volatile unsigned long *)0x56000050)
#define GPFDAT 		(*(volatile unsigned long *)0x56000054)
#define INTOFFSET	(*(volatile unsigned long *)0x56000054)

/* LED灯对应的二进制数字，可以表示0到7 */
#define LED_NUM(x)  (~(((x) & ~((~0) << 3)) << 4))

#endif