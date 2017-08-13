#define GPFCON		(*(volatile unsigned long *)0x56000050)
#define GPFDAT		(*(volatile unsigned long *)0x56000054)
#define GPF_OUT(x)	(1 << (2 * (x)))
#define GPF_SET(x)	(1 << (x))

int main()
{
	/* 设置GPF4 5 6为输出端口，GPF4 GPF6为高电平，LED2亮，LED1和3不亮*/
	GPFCON = GPF_OUT(4) | GPF_OUT(5) | GPF_OUT(6);
	GPFDAT = GPF_SET(4) | GPF_SET(6);
	return 0;
}
