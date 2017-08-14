.extern main
.text
.global _start
_start:						@ ���������ߣ���Ϊʹ����IRQ�����Կ�ʼ�Ĳ��ְ���IRQ��Ҫ�������ж��������ӵ�ַ0��ʼ
	b Reset					@ 0x00, reset�쳣���ϵ�����ִ��
HandleUndef:	
	b HandleUndef			@ 0x04, δ�����쳣��һ�·������쳣�����û�д������̣���ֱ���ڶ�Ӧλ����ѭ��
HandleSWI:	
	b HandleSWI				@ 0x08, SWI���ж��쳣
HandlePreFetchAbort:
	b HandlePreFetchAbort	@ 0x0C, Ԥȡָ�쳣
HandleDataAbort:
	b HandleDataAbort		@ 0x10, ���ݷ����쳣
HandleReserved:
	b HandleReserved		@ 0x14��δ����
	b HandleIRQ				@ 0x18, �жϴ���
HandleFIQ:
	b HandleFIQ				@ 0x1c�������ж�

Reset:
	ldr r0,=0x53000000		@ �رտ��Ź�
	mov r1,#0
	str r1,[r0]
	ldr sp,=4096			@ ����ջָ�룬��Ϊ���涼��C������������Ҫ����ջָ��
	msr cpsr_c,#0xd2		@ �����ж�ģʽ��CPSR 11010010
							@ Ϊʲô����cpsr������cpsr_c����Ϊcpsr_c��ʾcpsr�ĵ�8λ
							@ IF���������ˣ�IRQ��FIQ���Σ�ģʽ10010��IRQģʽ
	ldr sp,=3072				@ ����IRQģʽ��ջָ�룬�����ģ��Ĵ����Ŀ���
	msr cpsr_c,#0xdf		@ ����ϵͳģʽ��ģʽ11111
	ldr sp,=4096			@ ����ϵͳģʽ��ջָ�룬CPU��λ֮�󣬴���ϵͳģʽ
	
	bl init_led
	bl init_irq
	msr cpsr_c,#0x5f			@ ��I��IRQȥ������
	
	ldr lr,=halt_loop
	ldr pc,=main
halt_loop:
	b halt_loop
HandleIRQ:
	sub lr,lr,#4			@ ���ص�ַ
	stmdb sp!,{r0-r12,lr}	@ ����ʹ�õ��ļĴ��������ĺ�����sp�������ݴ��͵ĸı���ı�
							@ ����sp���Ѿ���IRQģʽ��sp
							@ IRQģʽ��sp����ϵͳģʽ��1000�ֽڣ�ɶ��˼�����¸�����ϵͳģʽ�µ�ջ���ݣ�
	ldr lr,=int_return
	ldr pc,=EINT_Handle		@ ISR���̣���interrupt.c��ʵ��
int_return:
	ldmia sp!,{r0-r12,pc}^	@ �жϷ��أ�^����˼�ǽ�SPSR�ָ���CPSR 