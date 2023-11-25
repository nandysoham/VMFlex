.data

.text
	 .globl main
.main



	 #Function main


	 #Moving sp to the Free segment
	 add 	 sp,    sp  , 1000
	 #Initializing Heap Address at First offset of main
	 li 		 x7,  250000
	 sw 		x7	1000(sp)
	 #Initializing Return Address at Second offset of main
	 li 		 x7,  x000
	 sw 		 x7, 	996(sp)
	label_1:
	 #Putting 20 inside x7
	 li 		x7	 20
	 #Putting n_2 inside x4
	 lw 	 x4 	 160(sp)
	 #Putting n_2 inside x7
	 #Clearing x7 having value n_2
	 sw 		x7	80(sp)
	 mv 		x7	x4
	 #Clearing x7 having value n_2
	 sw 		x7	80(sp)
	 #Putting 30 inside x7
	 li 		x7	 30
	 #Clearing x4 having value n_2
	 sw 		x4	80(sp)
	 #Putting m_2 inside x4
	 lw 	 x4 	 144(sp)
	 #Putting m_2 inside x7
	 #Clearing x7 having value m_2
	 sw 		x7	72(sp)
	 mv 		x7	x4
	 #Clearing x7 having value m_2
	 sw 		x7	72(sp)
	 #Putting 4 inside x7
	 li 		x7	 4
	 #Putting n_2 inside x6
	 lw 	 x6 	 160(sp)
	 #Clearing x4 having value m_2
	 sw 		x4	72(sp)
	 #Putting _t4_2 inside x4
	 lw 	 x4 	 96(sp)
	mul		x4	x7	x6
	 #Allocating memory of _t4_2 to _t5_2
	 #Clearing x4 having value _t4_2
	 sw 		x4	48(sp)
	 #Clearing x6 having value n_2
	 sw 		x6	80(sp)

	 
	 #Putting _t4_2 inside x6
	 lw 	 x6 	 96(sp)
	 lw 		 x4	1000(sp)
	 SUB 		x4	,x4,	x6
	 sw 		 x4	1000(sp)
	 mov 		x7	,x4
	 #Done allocating


	 #Clearing x4 having value _t4_2
	 sw 		x4	48(sp)
	 #Putting A_2 inside x4
	 lw 	 x4 	 0(sp)
	 #Putting A_2 inside x7
	 #Clearing x7 having value A_2
	 sw 		x7	0(sp)
	 mv 		x7	x4
	 #Clearing x7 having value A_2
	 sw 		x7	0(sp)
	 #Putting 0 inside x7
	 li 		x7	 0
	 #Clearing x4 having value A_2
	 sw 		x4	0(sp)
	 #Putting i_2 inside x4
	 lw 	 x4 	 112(sp)
	 #Putting i_2 inside x7
	 #Clearing x7 having value i_2
	 sw 		x7	56(sp)
	 mv 		x7	x4
	label_2:
	 #Clearing x6 having value _t4_2
	 sw 		x6	48(sp)
	 #Putting n_2 inside x6
	 lw 	 x6 	 160(sp)
	 #Putting i_2 inside x5
	 lw 	 x5 	 112(sp)
	slt		x7	x5	x6
	 BEQ		x7 ,	x0 ,	label_5
	 JAL label_3
	label_4:
	 #Clearing x5 having value i_2
	 sw 		x5	56(sp)
	 #Putting i_2 inside x5
	 lw 	 x5 	 112(sp)
	 #Putting i_2 inside x5
	 #Clearing x5 having value i_2
	 sw 		x5	56(sp)
	 mv 		x5	x7
	 #Clearing x5 having value i_2
	 sw 		x5	56(sp)
	 #Putting i_2 inside x5
	 lw 	 x5 	 112(sp)
	 #Clearing x4 having value i_2
	 sw 		x4	56(sp)
	 #Putting i_2 inside x4
	 lw 	 x4 	 112(sp)
	addi		x4	x5	1
	 JAL label_2
	label_3:
	 #Clearing x5 having value i_2
	 sw 		x5	56(sp)
	 #Putting i_2 inside x5
	 lw 	 x5 	 112(sp)
	muli		x7	x5	4
	 #Clearing x5 having value i_2
	 sw 		x5	56(sp)
	 #Putting A_2 inside x5
	 lw 	 x5 	 0(sp)
	 #Clearing x4 having value i_2
	 sw 		x4	56(sp)
	 #Putting _t10_3 inside x4
	 lw 	 x4 	 16(sp)
	add		x4	x5	x7
	 #Clearing x7 having value i_2
	 sw 		x7	56(sp)
	 #Putting 4 inside x7
	 li 		x7	 4
	 #Clearing x6 having value n_2
	 sw 		x6	80(sp)
	 #Putting m_2 inside x6
	 lw 	 x6 	 144(sp)
	 #Clearing x4 having value _t10_3
	 sw 		x4	8(sp)
	 #Putting _t12_3 inside x4
	 lw 	 x4 	 32(sp)
	mul		x4	x7	x6
	 #Allocating memory of _t12_3 to _t13_3
	 #Clearing x4 having value _t12_3
	 sw 		x4	16(sp)
	 #Clearing x6 having value m_2
	 sw 		x6	72(sp)
	 #Putting _t12_3 inside x6
	 lw 	 x6 	 32(sp)
	 lw 		 x4	1000(sp)
	 SUB 		x4	,x4,	x6
	 sw 		 x4	1000(sp)
	 mov 		x7	,x4
	 #Done allocating
	 #Clearing x4 having value _t12_3
	 sw 		x4	16(sp)
	 #Putting *_t10_3 inside x4
	 lw 	 x4 	 -4(sp)
	 #Putting *_t10_3 inside x7
	 #Clearing x7 having value *_t10_3
	 sw 		x7	0(sp)
	 mv 		x7	x4
	 JAL label_4
	label_5:
	 #Clearing x7 having value *_t10_3
	 sw 		x7	0(sp)
	 #Putting 0 inside x7
	 li 		x7	 0
	 #Clearing x4 having value *_t10_3
	 sw 		x4	0(sp)
	 #Putting i_2 inside x4
	 lw 	 x4 	 112(sp)
	 #Putting i_2 inside x7
	 #Clearing x7 having value i_2
	 sw 		x7	56(sp)
	 mv 		x7	x4
	label_6:
	 #Clearing x6 having value _t12_3
	 sw 		x6	16(sp)
	 #Putting n_2 inside x6
	 lw 	 x6 	 160(sp)
	 #Clearing x5 having value A_2
	 sw 		x5	0(sp)
	 #Putting i_2 inside x5
	 lw 	 x5 	 112(sp)
	slt		x7	x5	x6
	 BEQ		x7 ,	x0 ,	label_9
	 JAL label_7
	label_8:
	 #Clearing x5 having value i_2
	 sw 		x5	56(sp)
	 #Putting i_2 inside x5
	 lw 	 x5 	 112(sp)
	 #Putting i_2 inside x5
	 #Clearing x5 having value i_2
	 sw 		x5	56(sp)
	 mv 		x5	x7
	 #Clearing x5 having value i_2
	 sw 		x5	56(sp)
	 #Putting i_2 inside x5
	 lw 	 x5 	 112(sp)
	 #Clearing x4 having value i_2
	 sw 		x4	56(sp)
	 #Putting i_2 inside x4
	 lw 	 x4 	 112(sp)
	addi		x4	x5	1
	 JAL label_6
	label_7:
	 #Clearing x7 having value i_2
	 sw 		x7	56(sp)
	 #Putting 0 inside x7
	 li 		x7	 0
	 #Clearing x4 having value i_2
	 sw 		x4	56(sp)
	 #Putting j_2 inside x4
	 lw 	 x4 	 128(sp)
	 #Putting j_2 inside x7
	 #Clearing x7 having value j_2
	 sw 		x7	64(sp)
	 mv 		x7	x4
	label_10:
	 #Clearing x6 having value n_2
	 sw 		x6	80(sp)
	 #Putting m_2 inside x6
	 lw 	 x6 	 144(sp)
	 #Clearing x5 having value i_2
	 sw 		x5	56(sp)
	 #Putting j_2 inside x5
	 lw 	 x5 	 128(sp)
	slt		x7	x5	x6
	 BEQ		x7 ,	x0 ,	label_13
	 JAL label_11
	label_12:
	 #Clearing x5 having value j_2
	 sw 		x5	64(sp)
	 #Putting j_2 inside x5
	 lw 	 x5 	 128(sp)
	 #Putting j_2 inside x5
	 #Clearing x5 having value j_2
	 sw 		x5	64(sp)
	 mv 		x5	x7
	 #Clearing x5 having value j_2
	 sw 		x5	64(sp)
	 #Putting j_2 inside x5
	 lw 	 x5 	 128(sp)
	 #Clearing x4 having value j_2
	 sw 		x4	64(sp)
	 #Putting j_2 inside x4
	 lw 	 x4 	 128(sp)
	addi		x4	x5	1
	 JAL label_10
	label_11:
	 #Clearing x5 having value j_2
	 sw 		x5	64(sp)
	 #Putting i_2 inside x5
	 lw 	 x5 	 112(sp)
	 #Clearing x4 having value j_2
	 sw 		x4	64(sp)
	 #Putting _t20_4 inside x4
	 lw 	 x4 	 48(sp)
	muli		x4	x5	4
	 #Clearing x6 having value m_2
	 sw 		x6	72(sp)
	 #Putting _t20_4 inside x6
	 lw 	 x6 	 48(sp)
	 #Clearing x5 having value i_2
	 sw 		x5	56(sp)
	 #Putting A_2 inside x5
	 lw 	 x5 	 0(sp)
	 #Clearing x4 having value _t20_4
	 sw 		x4	24(sp)
	 #Putting _t21_4 inside x4
	 lw 	 x4 	 64(sp)
	add		x4	x5	x6
	 #Clearing x5 having value A_2
	 sw 		x5	0(sp)
	 #Putting j_2 inside x5
	 lw 	 x5 	 128(sp)
	 #Clearing x4 having value _t21_4
	 sw 		x4	32(sp)
	 #Putting _t22_4 inside x4
	 lw 	 x4 	 80(sp)
	muli		x4	x5	4
	 #Clearing x6 having value _t20_4
	 sw 		x6	24(sp)
	 #Putting _t22_4 inside x6
	 lw 	 x6 	 80(sp)
	 #Clearing x5 having value j_2
	 sw 		x5	64(sp)
	 #Putting *_t21_4 inside x5
	 lw 	 x5 	 -4(sp)
	add		x8	x5	x6
	 #Clearing x7 having value j_2
	 sw 		x7	64(sp)
	 #Putting 1 inside x7
	 li 		x7	 1
	 #Clearing x4 having value _t22_4
	 sw 		x4	40(sp)
	 #Putting *_t23_4 inside x4
	 lw 	 x4 	 -4(sp)
	 #Putting *_t23_4 inside x7
	 #Clearing x7 having value *_t23_4
	 sw 		x7	0(sp)
	 mv 		x7	x4
	 JAL label_12
	label_13:
	 JAL label_8
	label_9:
	 #Clearing x7 having value *_t23_4
	 sw 		x7	0(sp)
	 #Putting 0 inside x7
	 li 		x7	 0
	 #Function returning
	 #Putting 0 inside x9
	 #Clearing x9 having value 0
	 sw 		x9	0(sp)
	 mv 		x9	x7
JAL x1;
