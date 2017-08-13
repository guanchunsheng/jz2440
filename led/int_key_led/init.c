/*
 * init.c: ����һЩ��ʼ��
 */ 

#include "int_key_led.h"

void init_led(void)
{
    // LED1,LED2,LED4��Ӧ��3��������Ϊ���
    GPFCON &= ~(GPF_MSK(4) | GPF_MSK(5) | GPF_MSK(6));
    GPFCON |= GPF_OUT(4) | GPF_OUT(5) | GPF_OUT(6);
}

/*
 * ��ʼ��GPIO����Ϊ�ⲿ�ж�
 * GPIO���������ⲿ�ж�ʱ��Ĭ��Ϊ�͵�ƽ������IRQ��ʽ(��������INTMOD)
 */ 
void init_irq( )
{
    // S2,S3��Ӧ��2��������Ϊ�ж����� EINT0,ENT2
    GPFCON &= ~(GPF_MSK(0) | GPF_MSK(2));
    GPFCON |= GPF_EINT(0) | GPF_EINT(2);

    // S4��Ӧ��������Ϊ�ж�����EINT11
    GPGCON &= ~GPF_MSK(3);
    GPGCON |= GPF_EINT(3);
    
    // ����EINT11����Ҫ��EINTMASK�Ĵ�����ʹ����
    EINTMASK &= ~(1 << 11);
        
    /*
     * �趨���ȼ���
     * ARB_SEL0 = 00b, ARB_MODE0 = 0: REQ1 > REQ3����EINT0 > EINT2
     * �ٲ���1��6��������
     * ���գ�
     * EINT0 > EINT2 > EINT11��K2 > K3 > K4
     */
    PRIORITY = (PRIORITY & ((~1) | (3 << 7))) | (0 << 7) ;

    // EINT0��EINT2��EINT8_23ʹ��
    INTMSK &= (~(1 << 0)) & (~(1 << 2)) & (~(1 << 5));
}
