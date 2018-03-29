

.text
.global _start

_start:

	/* 设置CPU工作于异步模式 */
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0xc0000000   //R1_nF:OR:R1_iA
	mcr p15,0,r0,c1,c0,0

	/* 设置内存: sp 栈 */
	/* 分辨是nor/nand启动
	 * 写0到0地址, 再读出来
	 * 如果得到0, 表示0地址上的内容被修改了, 它对应ram, 这就是nand启动
	 * 否则就是nor启动
	 * nand启动sram地址偏移是0，nor启动sram地址偏移0x40000000
	 */
	mov r1,#0
	ldr r0,[r1]	/* 读出原来的值备份,r0<-[0] */
	str r1,[r1]	/* 0->[0] */
	ldr r2,[r1] /* r2<-[0] */
	cmp r1,r2	/* r1==r2? 如果相等表示nand启动 */
	ldr sp,=0x40000000+4096 /* 先假设是nor启动 */
	moveq sp,#4096	/* nand启动   */
	streq r0,[r1]	/* 恢复原来的值 */

	bl main


_halt:
	b _halt
	
