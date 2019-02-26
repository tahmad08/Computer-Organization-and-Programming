	.cpu arm7tdmi
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 2
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"bouncingghost.c"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, lr}
	mov	r2, #67108864
	mov	r9, #0
	mov	ip, r2
	mov	r3, r9
	mov	r1, r9
	mov	r4, #-2147483592
	ldr	r0, .L27
	ldr	lr, .L27+4
	ldr	r8, [r0]
	strh	lr, [r2]	@ movhi
	add	r7, r8, #28672
	ldr	lr, .L27+8
	add	r7, r7, #128
.L12:
	ldr	r2, [ip, #304]
	tst	r2, #16
	ldr	r2, [ip, #304]
	addeq	r6, r9, #1
	movne	r6, r9
	tst	r2, #32
	ldr	r2, [ip, #304]
	subeq	r6, r6, #1
	tst	r2, #64
	ldr	r2, [ip, #304]
	subeq	r5, r3, #1
	movne	r5, r3
	tst	r2, #128
	addeq	r5, r5, #1
.L6:
	ldrh	r2, [ip, #6]
	cmp	r2, #160
	bhi	.L6
.L7:
	ldrh	r2, [ip, #6]
	cmp	r2, #159
	bls	.L7
	rsb	r3, r3, r3, lsl #4
	add	r9, r9, r3, lsl #4
	lsl	r9, r9, #1
	add	r0, r8, r9
	add	r9, r7, r9
.L8:
	mov	r3, r0
	add	r2, r0, #112
.L9:
	strh	r1, [r3], #2	@ movhi
	cmp	r2, r3
	bne	.L9
	add	r0, r0, #480
	cmp	r0, r9
	bne	.L8
	rsb	r2, r5, r5, lsl #4
	add	r2, r6, r2, lsl #4
	ldr	r3, .L27+12
	add	r2, r8, r2, lsl #1
.L11:
	str	r3, [ip, #212]
	add	r3, r3, #112
	cmp	lr, r3
	str	r2, [ip, #216]
	str	r4, [ip, #220]
	add	r2, r2, #480
	bne	.L11
	mov	r9, r6
	mov	r3, r5
	b	.L12
.L28:
	.align	2
.L27:
	.word	.LANCHOR0
	.word	1027
	.word	ghost+6720
	.word	ghost
	.size	main, .-main
	.text
	.align	2
	.global	setPixel
	.syntax unified
	.arm
	.fpu softvfp
	.type	setPixel, %function
setPixel:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L30
	rsb	r0, r0, r0, lsl #4
	add	r1, r1, r0, lsl #4
	ldr	r3, [r3]
	lsl	r1, r1, #1
	strh	r2, [r3, r1]	@ movhi
	bx	lr
.L31:
	.align	2
.L30:
	.word	.LANCHOR0
	.size	setPixel, .-setPixel
	.align	2
	.global	drawRectangle
	.syntax unified
	.arm
	.fpu softvfp
	.type	drawRectangle, %function
drawRectangle:
	@ Function supports interworking.
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, lr}
	cmp	r3, #0
	ldrh	ip, [sp, #12]
	ble	.L32
	mov	r4, #0
	ldr	lr, .L40
	rsb	r0, r0, r0, lsl #4
	ldr	lr, [lr]
	add	r0, r1, r0, lsl #4
	add	lr, lr, r0, lsl #1
	lsl	r5, r2, #1
.L34:
	cmp	r2, #0
	movgt	r1, lr
	addgt	r0, lr, r5
	ble	.L37
.L35:
	strh	ip, [r1], #2	@ movhi
	cmp	r1, r0
	bne	.L35
.L37:
	add	r4, r4, #1
	cmp	r3, r4
	add	lr, lr, #480
	bne	.L34
.L32:
	pop	{r4, r5, lr}
	bx	lr
.L41:
	.align	2
.L40:
	.word	.LANCHOR0
	.size	drawRectangle, .-drawRectangle
	.align	2
	.global	waitForVblank
	.syntax unified
	.arm
	.fpu softvfp
	.type	waitForVblank, %function
waitForVblank:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r2, #67108864
.L43:
	ldrh	r3, [r2, #6]
	cmp	r3, #160
	bhi	.L43
	mov	r2, #67108864
.L44:
	ldrh	r3, [r2, #6]
	cmp	r3, #159
	bls	.L44
	bx	lr
	.size	waitForVblank, .-waitForVblank
	.align	2
	.global	drawGhost
	.syntax unified
	.arm
	.fpu softvfp
	.type	drawGhost, %function
drawGhost:
	@ Function supports interworking.
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r3, #0
	bxle	lr
	push	{r4, r5, r6, lr}
	mov	lr, #67108864
	ldr	r6, .L56
	add	r3, r0, r3
	rsb	r4, r3, r3, lsl #4
	rsb	r5, r0, r0, lsl #4
	ldr	r3, [r6]
	add	r0, r1, r4, lsl #4
	ldr	ip, [sp, #16]
	add	r1, r1, r5, lsl #4
	add	r0, r3, r0, lsl #1
	add	r1, r3, r1, lsl #1
	orr	r3, r2, #-2147483648
	lsl	r2, r2, #1
.L50:
	str	ip, [lr, #212]
	str	r1, [lr, #216]
	add	r1, r1, #480
	cmp	r1, r0
	str	r3, [lr, #220]
	add	ip, ip, r2
	bne	.L50
	pop	{r4, r5, r6, lr}
	bx	lr
.L57:
	.align	2
.L56:
	.word	.LANCHOR0
	.size	drawGhost, .-drawGhost
	.global	videoBuffer
	.data
	.align	2
	.set	.LANCHOR0,. + 0
	.type	videoBuffer, %object
	.size	videoBuffer, 4
videoBuffer:
	.word	100663296
	.ident	"GCC: (devkitARM release 47) 7.1.0"
