.text
.global _start
_start:
	LDR	R0,=0x56000050		@ R0设为GPBCON寄存器，选择F组GPIO引脚功能
	MOV R1,#0x00000500
	STR R1,[R0]				@ 这3个指令是存入某个寄存器一个给定值的套路
	
	LDR R0,=0x56000054
	MOV R1,#0x00000000
	STR R1,[R0]				@ GPF4,5 6 输出0，点亮LED1,2,3
	
MAIN_LOOP:					@ 代码部分注意不要在中文输入模式，例如这句的冒号，如果是中文冒号，会显示“无效指令 main_loop：”
	B MAIN_LOOP
