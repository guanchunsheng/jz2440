.extern main
.text
.global _start
_start:						@ 这个例子里边，因为使用了IRQ，所以开始的部分按照IRQ的要求设置中断向量，从地址0开始
	b Reset					@ 0x00, reset异常，上电首先执行
HandleUndef:	
	b HandleUndef			@ 0x04, 未定义异常，一下发生的异常，如果没有处理例程，就直接在对应位置死循环
HandleSWI:	
	b HandleSWI				@ 0x08, SWI软中断异常
HandlePreFetchAbort:
	b HandlePreFetchAbort	@ 0x0C, 预取指异常
HandleDataAbort:
	b HandleDataAbort		@ 0x10, 数据访问异常
HandleReserved:
	b HandleReserved		@ 0x14，未定义
	b HandleIRQ				@ 0x18, 中断处理
HandleFIQ:
	b HandleFIQ				@ 0x1c，快速中断

Reset:
	ldr r0,=0x53000000		@ 关闭看门狗
	mov r1,#0
	str r1,[r0]
	ldr sp,=4096			@ 设置栈指针，因为下面都是C函数，所以需要设置栈指针
	msr cpsr_c,#0xd2		@ 进入中断模式，CPSR 11010010
							@ 为什么不是cpsr，而是cpsr_c，因为cpsr_c表示cpsr的低8位
							@ IF都设置上了，IRQ和FIQ屏蔽，模式10010，IRQ模式
	ldr sp,3072				@ 设置IRQ模式的栈指针，见上文，寄存器的拷贝
	msr cpsr_c,#0xdf		@ 进入系统模式，模式11111
	ldr dp,=4096			@ 设置系统模式的栈指针，CPU复位之后，处于系统模式
	
	bl init_led
	bl init_irq
	msr cpsr_c,#5f			@ 打开I，IRQ去掉屏蔽
	
	ldr lr,=halt_loop
	ldr pc,=main
halt_loop:
	b halt_loop
HandleIRQ:
	sub lr,lr,#4			@ 返回地址
	stmdb sp!,{r0-r12,lr}	@ 保存使用到的寄存器，！的含义是sp随着数据传送的改变而改变
							@ 现在sp，已经是IRQ模式的sp
							@ IRQ模式的sp，比系统模式少1000字节，啥意思，是怕覆盖了系统模式下的栈数据？
	ldr lr,=int_return
	ldr pc,=EINT_Handle		@ ISR例程，在interrupt.c中实现
int_return:
	ldmia sp!,{r0-r12,lr}^	@ 中断返回，^的意思是将SPSR恢复到CPSR 
