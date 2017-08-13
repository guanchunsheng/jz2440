.text
.global _start
_start:
	ldr r0,=0x53000000		@ 第一步关闭看门狗
	mov r1,#0
	str r1,[r0]
	
	ldr sp,=1024*4			@ 设置堆栈
	bl main					@ 调用C语言程序main函数
halt_loop:
	b halt_loop
