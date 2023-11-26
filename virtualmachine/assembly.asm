.data

.text
	 .globl main
.main



	 #Function main


	 #Moving sp to the Free segment
	 add 	 sp,    sp  , 2000
	 #Initializing Heap Address at First offset of main
	 li 		 x7,  250000
	 sw 		x7	2000(sp)
	 #Initializing Return Address at Second offset of main
	 li 		 x7,  x000
	 sw 		 x7, 	1996(sp)
	label_2:
	 #Putting 20 inside x7
	 li 		x7	,	20
	 #Putting n_2 inside x4
	 lw 		x4 	,	176(sp)
	 #Putting n_2 inside x7
	 #Clearing x7 having value n_2
	 sw		x7	,	88(sp)
	 mv 		x7	,	x4
	 #Clearing x7 having value n_2
	 sw		x7	,	88(sp)
	 #Putting 30 inside x7
	 li 		x7	,	30
	 #Clearing x4 having value n_2
	 sw		x4	,	88(sp)
	 #Putting m_2 inside x4
	 lw 		x4 	,	160(sp)
	 #Putting m_2 inside x7
	 #Clearing x7 having value m_2
	 sw		x7	,	80(sp)
	 mv 		x7	,	x4
	 #Clearing x7 having value m_2
	 sw		x7	,	80(sp)
	 #Putting 4 inside x7
	 li 		x7	,	4
	 #Putting n_2 inside x6
	 lw 		x6 	,	176(sp)
	 #Clearing x4 having value m_2
	 sw		x4	,	80(sp)
	 #Putting _t7_2 inside x4
	 lw 		x4 	,	112(sp)
	mul		x4	,	x7	,	x6
	 #Allocating memory of _t7_2 to _t8_2
	 #Clearing x4 having value _t7_2
	 sw		x4	,	56(sp)
	 #Clearing x6 having value n_2
	 sw		x6	,	88(sp)
	 #Putting _t7_2 inside x6
	 lw 		x6 	,	112(sp)
	 lw 		 x4	,	2000(sp)
	 sub 		x4	,	x4	,	x6
	 sw 		 x4	,	2000(sp)
	 mov 		x7	,	x4
	 #Done allocating
	 #Clearing x4 having value _t7_2
	 sw		x4	,	56(sp)
	 #Putting A_2 inside x4
	 lw 		x4 	,	0(sp)
	 #Putting A_2 inside x7
	 #Clearing x7 having value A_2
	 sw		x7	,	0(sp)
	 mv 		x7	,	x4
	 #Clearing x7 having value A_2
	 sw		x7	,	0(sp)
	 #Putting 0 inside x7
	 li 		x7	,	0
	 #Clearing x4 having value A_2
	 sw		x4	,	0(sp)
	 #Putting i_2 inside x4
	 lw 		x4 	,	128(sp)
	 #Putting i_2 inside x7
	 #Clearing x7 having value i_2
	 sw		x7	,	64(sp)
	 mv 		x7	,	x4
	label_3:
	 #Clearing x6 having value _t7_2
	 sw		x6	,	56(sp)
	 #Putting n_2 inside x6
	 lw 		x6 	,	176(sp)
	 #Putting i_2 inside x5
	 lw 		x5 	,	128(sp)
	slt		x7	,	x5	,	x6
	BEQ		x7	,	x0	,	label_6
	 JAL label_4
	label_5:
	 #Clearing x5 having value i_2
	 sw		x5	,	64(sp)
	 #Putting i_2 inside x5
	 lw 		x5 	,	128(sp)
	 #Putting i_2 inside x5
	 #Clearing x5 having value i_2
	 sw		x5	,	64(sp)
	 mv 		x5	,	x7
	 #Clearing x5 having value i_2
	 sw		x5	,	64(sp)
	 #Putting i_2 inside x5
	 lw 		x5 	,	128(sp)
	 #Clearing x4 having value i_2
	 sw		x4	,	64(sp)
	 #Putting i_2 inside x4
	 lw 		x4 	,	128(sp)
	addi		x4	,	x5	,	1
	 JAL label_3
	label_4:
	 #Clearing x5 having value i_2
	 sw		x5	,	64(sp)
	 #Putting i_2 inside x5
	 lw 		x5 	,	128(sp)
	muli		x7	,	x5	,	4
	 #Clearing x5 having value i_2
	 sw		x5	,	64(sp)
	 #Putting A_2 inside x5
	 lw 		x5 	,	0(sp)
	 #Clearing x4 having value i_2
	 sw		x4	,	64(sp)
	 #Putting _t13_3 inside x4
	 lw 		x4 	,	16(sp)
	add		x4	,	x5	,	x7
	 #Clearing x7 having value i_2
	 sw		x7	,	64(sp)
	 #Putting 4 inside x7
	 li 		x7	,	4
	 #Clearing x6 having value n_2
	 sw		x6	,	88(sp)
	 #Putting m_2 inside x6
	 lw 		x6 	,	160(sp)
	 #Clearing x4 having value _t13_3
	 sw		x4	,	8(sp)
	 #Putting _t15_3 inside x4
	 lw 		x4 	,	32(sp)
	mul		x4	,	x7	,	x6
	 #Allocating memory of _t15_3 to _t16_3
	 #Clearing x4 having value _t15_3
	 sw		x4	,	16(sp)
	 #Clearing x6 having value m_2
	 sw		x6	,	80(sp)
	 #Putting _t15_3 inside x6
	 lw 		x6 	,	32(sp)
	 lw 		 x4	,	2000(sp)
	 sub 		x4	,	x4	,	x6
	 sw 		 x4	,	2000(sp)
	 mov 		x7	,	x4
	 #Done allocating
	 #Processing *_t13_3
	 #
	 #
	 #Declared so No need to bring up memory
	 #Clearing x4 having value _t15_3
	 sw		x4	,	16(sp)
	 #Putting _t13_3 inside x4
	 lw 		x4 	,	16(sp)
	 #Putting _t13_3 inside x7
	 #Clearing x7 having value _t13_3
	 sw		x7	,	8(sp)
	 mv 		x7	,	x4
	 #Storing back *_t13_3 which is in x4 to its position
	 #Clearing x5 having value A_2
	 sw		x5	,	0(sp)
	 #Putting _t13_3 inside x5
	 lw 		x5 	,	16(sp)
	 sub 		x5	,	x5	,	sp
	lw 		 x5	,	x5(sp)
	 sub 		x5	,	x5	,	sp
	sw 		 x4	,	x5(sp)
	 #Stored*_t13_3
	 JAL label_5
	label_6:
	 #Spilling the return address to the 0th offset of the function
	 sw 		x1	,	2000(sp)
	 #Picking up the new return address
	 li 		x1	175
	 #Storing register table of main
	 #
	 #
	 lw 		 x4	,	2000(sp)
	 addi 		x4	,	x4	,t2000
	 sw 		 x4	,	2000(sp)
	 sub 		x4	,	x4	,	sp
	sw 		 x0	,	x4(sp)
	addi 		x4	,	x4	,	4
	sw 		 x1	,	x4(sp)
	addi 		x4	,	x4	,	4
	sw 		 x10	,	x4(sp)
	addi 		x4	,	x4	,	4
	sw 		 x11	,	x4(sp)
	addi 		x4	,	x4	,	4
	sw 		 x12	,	x4(sp)
	addi 		x4	,	x4	,	4
	sw 		 x13	,	x4(sp)
	addi 		x4	,	x4	,	4
	sw 		 x14	,	x4(sp)
	addi 		x4	,	x4	,	4
	sw 		 x15	,	x4(sp)
	addi 		x4	,	x4	,	4
	sw 		 x16	,	x4(sp)
	addi 		x4	,	x4	,	4
	sw 		 x17	,	x4(sp)
	addi 		x4	,	x4	,	4
	sw 		 x4	,	x4(sp)
	addi 		x4	,	x4	,	4
	sw 		 x5	,	x4(sp)
	addi 		x4	,	x4	,	4
	sw 		 x6	,	x4(sp)
	addi 		x4	,	x4	,	4
	sw 		 x7	,	x4(sp)
	addi 		x4	,	x4	,	4
	sw 		 x8	,	x4(sp)
	addi 		x4	,	x4	,	4
	sw 		 x9	,	x4(sp)
	addi 		x4	,	x4	,	4
	 #Done storing Register Table
	 #
	 #
	 #Function call happening
	 JAL label_1
	 #getting back the old return address
	 lw 		x1	,	2000(sp)
	 #Retreiving register table of main
	 #
	 #
	 lw 		 x4	,	2000(sp)
	 sub 		x4	,	x4	,	sp
	lw 		 x0	,	x4(sp)
	addi 		x4	,	x4	,	4
	lw 		 x1	,	x4(sp)
	addi 		x4	,	x4	,	4
	lw 		 x10	,	x4(sp)
	addi 		x4	,	x4	,	4
	lw 		 x11	,	x4(sp)
	addi 		x4	,	x4	,	4
	lw 		 x12	,	x4(sp)
	addi 		x4	,	x4	,	4
	lw 		 x13	,	x4(sp)
	addi 		x4	,	x4	,	4
	lw 		 x14	,	x4(sp)
	addi 		x4	,	x4	,	4
	lw 		 x15	,	x4(sp)
	addi 		x4	,	x4	,	4
	lw 		 x16	,	x4(sp)
	addi 		x4	,	x4	,	4
	lw 		 x17	,	x4(sp)
	addi 		x4	,	x4	,	4
	lw 		 x4	,	x4(sp)
	addi 		x4	,	x4	,	4
	lw 		 x5	,	x4(sp)
	addi 		x4	,	x4	,	4
	lw 		 x6	,	x4(sp)
	addi 		x4	,	x4	,	4
	lw 		 x7	,	x4(sp)
	addi 		x4	,	x4	,	4
	lw 		 x8	,	x4(sp)
	addi 		x4	,	x4	,	4
	lw 		 x9	,	x4(sp)
	addi 		x4	,	x4	,	4
	 #Done Retrieving Register Table
	 #
	 #
	label_7:
	 #Putting _t17_2 inside x4
	 lw 		x4 	,	48(sp)
	 #Putting _t17_2 inside x9
	 #Clearing x9 having value _t17_2
	 sw		x9	,	24(sp)
	 mv 		x9	,	x4
	 #Clearing x5 having value _t13_3
	 sw		x5	,	8(sp)
	 #Putting _t17_2 inside x5
	 lw 		x5 	,	48(sp)
	 #Putting _t13_3 inside x5
	 #Clearing x5 having value _t13_3
	 sw		x5	,	8(sp)
	 mv 		x5	,	x7
	 #Clearing x7 having value _t13_3
	 sw		x7	,	8(sp)
	 #Putting 0 inside x7
	 li 		x7	,	0
	 #Clearing x4 having value _t17_2
	 sw		x4	,	24(sp)
	 #Putting i_2 inside x4
	 lw 		x4 	,	128(sp)
	 #Putting i_2 inside x7
	 #Clearing x7 having value i_2
	 sw		x7	,	64(sp)
	 mv 		x7	,	x4
	label_8:
	 #Clearing x6 having value _t15_3
	 sw		x6	,	16(sp)
	 #Putting n_2 inside x6
	 lw 		x6 	,	176(sp)
	 #Clearing x5 having value _t13_3
	 sw		x5	,	8(sp)
	 #Putting i_2 inside x5
	 lw 		x5 	,	128(sp)
	slt		x7	,	x5	,	x6
	BEQ		x7	,	x0	,	label_11
	 JAL label_9
	label_10:
	 #Clearing x5 having value i_2
	 sw		x5	,	64(sp)
	 #Putting i_2 inside x5
	 lw 		x5 	,	128(sp)
	 #Putting i_2 inside x5
	 #Clearing x5 having value i_2
	 sw		x5	,	64(sp)
	 mv 		x5	,	x7
	 #Clearing x5 having value i_2
	 sw		x5	,	64(sp)
	 #Putting i_2 inside x5
	 lw 		x5 	,	128(sp)
	 #Clearing x4 having value i_2
	 sw		x4	,	64(sp)
	 #Putting i_2 inside x4
	 lw 		x4 	,	128(sp)
	addi		x4	,	x5	,	1
	 JAL label_8
	label_9:
	 #Clearing x7 having value i_2
	 sw		x7	,	64(sp)
	 #Putting 0 inside x7
	 li 		x7	,	0
	 #Clearing x4 having value i_2
	 sw		x4	,	64(sp)
	 #Putting j_2 inside x4
	 lw 		x4 	,	144(sp)
	 #Putting j_2 inside x7
	 #Clearing x7 having value j_2
	 sw		x7	,	72(sp)
	 mv 		x7	,	x4
	label_12:
	 #Clearing x6 having value n_2
	 sw		x6	,	88(sp)
	 #Putting m_2 inside x6
	 lw 		x6 	,	160(sp)
	 #Clearing x5 having value i_2
	 sw		x5	,	64(sp)
	 #Putting j_2 inside x5
	 lw 		x5 	,	144(sp)
	slt		x7	,	x5	,	x6
	BEQ		x7	,	x0	,	label_15
	 JAL label_13
	label_14:
	 #Clearing x5 having value j_2
	 sw		x5	,	72(sp)
	 #Putting j_2 inside x5
	 lw 		x5 	,	144(sp)
	 #Putting j_2 inside x5
	 #Clearing x5 having value j_2
	 sw		x5	,	72(sp)
	 mv 		x5	,	x7
	 #Clearing x5 having value j_2
	 sw		x5	,	72(sp)
	 #Putting j_2 inside x5
	 lw 		x5 	,	144(sp)
	 #Clearing x4 having value j_2
	 sw		x4	,	72(sp)
	 #Putting j_2 inside x4
	 lw 		x4 	,	144(sp)
	addi		x4	,	x5	,	1
	 JAL label_12
	label_13:
	 #Clearing x5 having value j_2
	 sw		x5	,	72(sp)
	 #Putting i_2 inside x5
	 lw 		x5 	,	128(sp)
	 #Clearing x4 having value j_2
	 sw		x4	,	72(sp)
	 #Putting _t24_4 inside x4
	 lw 		x4 	,	64(sp)
	muli		x4	,	x5	,	4
	 #Clearing x6 having value m_2
	 sw		x6	,	80(sp)
	 #Putting _t24_4 inside x6
	 lw 		x6 	,	64(sp)
	 #Clearing x5 having value i_2
	 sw		x5	,	64(sp)
	 #Putting A_2 inside x5
	 lw 		x5 	,	0(sp)
	 #Clearing x4 having value _t24_4
	 sw		x4	,	32(sp)
	 #Putting _t25_4 inside x4
	 lw 		x4 	,	80(sp)
	add		x4	,	x5	,	x6
	 #Clearing x5 having value A_2
	 sw		x5	,	0(sp)
	 #Putting j_2 inside x5
	 lw 		x5 	,	144(sp)
	 #Clearing x4 having value _t25_4
	 sw		x4	,	40(sp)
	 #Putting _t26_4 inside x4
	 lw 		x4 	,	96(sp)
	muli		x4	,	x5	,	4
	 #Clearing x6 having value _t24_4
	 sw		x6	,	32(sp)
	 #Putting _t26_4 inside x6
	 lw 		x6 	,	96(sp)
	 #Processing *_t25_4
	 #
	 #
	 #Recursively get the value into x5
	 #Clearing x5 having value j_2
	 sw		x5	,	72(sp)
	 #Putting _t25_4 inside x5
	 lw 		x5 	,	80(sp)
	 sub 		x5	,	x5	,	sp
	lw 		 x5	,	x5(sp)
	add		x8	,	x5	,	x6
	 #Clearing x7 having value j_2
	 sw		x7	,	72(sp)
	 #Putting 1 inside x7
	 li 		x7	,	1
	 #Processing *_t27_4
	 #
	 #
	 #Declared so No need to bring up memory
	 #Putting  inside x7
	 mv 		x7	,	x8
	 #Storing back *_t27_4 which is in x4 to its position
	 sub 		x5	,	x5	,	sp
	lw 		 x5	,	x5(sp)
	 sub 		x5	,	x5	,	sp
	sw 		 x4	,	x5(sp)
	 #Stored*_t27_4
	 JAL label_14
	label_15:
	 JAL label_10
	label_11:
	 #Putting 0 inside x7
	 li 		x7	,	0
	 #Function returning
	 #Putting 0 inside x9
	 #Clearing x9 having value 0
	 sw		x9	,	0(sp)
	 mv 		x9	,	x7
JAL x1;



	 #Function soham


	 #Fetching params for soham
	label_1:
	 #Putting b_2 inside x6
	 lw 		x6 	,	48(sp)
	 #Putting a_2 inside x5
	 lw 		x5 	,	32(sp)
	 #Putting _t1_2 inside x4
	 lw 		x4 	,	0(sp)
	add		x4	,	x5	,	x6
	 #Clearing x5 having value a_2
	 sw		x5	,	16(sp)
	 #Putting _t1_2 inside x5
	 lw 		x5 	,	0(sp)
	 #Putting  inside x5
	 mv 		x5	,	x7
	 #Clearing x6 having value b_2
	 sw		x6	,	24(sp)
	 #Putting b_2 inside x6
	 lw 		x6 	,	48(sp)
	 #Putting a_2 inside x5
	 lw 		x5 	,	32(sp)
	mul		x7	,	x5	,	x6
	 #Clearing x4 having value _t1_2
	 sw		x4	,	0(sp)
	 #Putting a_2 inside x4
	 lw 		x4 	,	32(sp)
	 #Putting a_2 inside x7
	 #Clearing x7 having value a_2
	 sw		x7	,	16(sp)
	 mv 		x7	,	x4
	 #Clearing x5 having value a_2
	 sw		x5	,	16(sp)
	 #Putting b_2 inside x5
	 lw 		x5 	,	48(sp)
	 #Clearing x4 having value a_2
	 sw		x4	,	16(sp)
	 #Putting _t3_2 inside x4
	 lw 		x4 	,	16(sp)
	add		x4	,	x5	,	x7
	 #Clearing x5 having value b_2
	 sw		x5	,	24(sp)
	 #Putting _t3_2 inside x5
	 lw 		x5 	,	16(sp)
	 #Clearing x4 having value _t3_2
	 sw		x4	,	8(sp)
	 #Putting b_2 inside x4
	 lw 		x4 	,	48(sp)
	 #Putting b_2 inside x5
	 #Clearing x5 having value b_2
	 sw		x5	,	24(sp)
	 mv 		x5	,	x4
	 #Function returning
	 #Clearing x4 having value b_2
	 sw		x4	,	24(sp)
	 #Putting a_2 inside x4
	 lw 		x4 	,	32(sp)
	 #Putting a_2 inside x9
	 #Clearing x9 having value a_2
	 sw		x9	,	16(sp)
	 mv 		x9	,	x4
JAL x1;
