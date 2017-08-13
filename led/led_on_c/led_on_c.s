	.file	"led_on_c.c"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	mov	r3, #1442840576
	add	r3, r3, #80
	mov	r2, #10752
	str	r2, [r3, #0]
	mov	r3, #1442840576
	add	r3, r3, #84
	mov	r2, #80
	str	r2, [r3, #0]
	mov	r3, #0
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
	.size	main, .-main
	.ident	"GCC: (GNU) 3.4.5"
