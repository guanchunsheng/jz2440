#include "int_key_led.h"

void EINT_Handle()
{
    unsigned long oft = INTOFFSET;
    unsigned long val;
	
	GPFDAT &= ~(LED_MSK(0) | LED_MSK(1) | LED_MSK(2));
	GPFDAT |= LED_NUM(oft);

    //���ж�
    if( oft == 5 ) 
        EINTPEND = (1<<11);   // EINT8_23����IRQ5
    SRCPND = 1 << oft;
    INTPND = 1 << oft;
}
