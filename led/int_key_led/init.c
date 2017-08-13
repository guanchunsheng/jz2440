/*
 * init.c: 进行一些初始化
 */ 

#include "int_key_led.h"

void init_led(void)
{
    // LED1,LED2,LED4对应的3根引脚设为输出
    GPFCON &= ~(GPF_MSK(4) | GPF_MSK(5) | GPF_MSK(6));
    GPFCON |= GPF_OUT(4) | GPF_OUT(5) | GPF_OUT(6);
}

/*
 * 初始化GPIO引脚为外部中断
 * GPIO引脚用作外部中断时，默认为低电平触发、IRQ方式(不用设置INTMOD)
 */ 
void init_irq( )
{
    // S2,S3对应的2根引脚设为中断引脚 EINT0,ENT2
    GPFCON &= ~(GPF_MSK(0) | GPF_MSK(2));
    GPFCON |= GPF_EINT(0) | GPF_EINT(2);

    // S4对应的引脚设为中断引脚EINT11
    GPGCON &= ~GPF_MSK(3);
    GPGCON |= GPF_EINT(3);
    
    // 对于EINT11，需要在EINTMASK寄存器中使能它
    EINTMASK &= ~(1 << 11);
        
    /*
     * 设定优先级：
     * ARB_SEL0 = 00b, ARB_MODE0 = 0: REQ1 > REQ3，即EINT0 > EINT2
     * 仲裁器1、6无需设置
     * 最终：
     * EINT0 > EINT2 > EINT11即K2 > K3 > K4
     */
    PRIORITY = (PRIORITY & ((~1) | (3 << 7))) | (0 << 7) ;

    // EINT0、EINT2、EINT8_23使能
    INTMSK &= (~(1 << 0)) & (~(1 << 2)) & (~(1 << 5));
}
