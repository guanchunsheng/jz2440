#define GPFCON		(*(volatile unsigned long *)0x56000050)
#define GPFDAT		(*(volatile unsigned long *)0x56000054)
#define GPF_OUT(x)	(1 << (2 * (x)))
#define LED_NUM(x)  (~(((x) & ~((~0) << 3)) << 4))

int main()
{
    unsigned int i;
    unsigned long j;
    /* led to count, in binary */
    GPFCON = GPF_OUT(4) | GPF_OUT(5) | GPF_OUT(6);
    for (i = 0;;i = ++i % 8)
    {
        GPFDAT = LED_NUM(i);
        for (j = 0; j < 1000000; j++)
            ;
    }
    return 0;
}
