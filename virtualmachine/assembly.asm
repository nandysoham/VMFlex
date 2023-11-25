.data

.text
	 .globl main
.main



	 #Function main


	 #Moving sp to the Free segment
	 add 	 sp,    sp  , 2000
	 #Initializing Heap Address at First offset of main
	 li 		 x7,  x000
	 sw 		x7	2000(sp)
	 #Initializing Return Address at Second offset of main
	 li 		 x7,  x000
	 sw 		 x7, 	1996(sp)
	label_1:
	 #Putting 40 inside x8
	 li 		x8	 40
	 #Putting  inside x8
	 mv 		x8	x7
	 #
	 #assigning params for map_init
	 #Param map_2loading into x12
	 #Putting  inside x12
	 mv 		x12	x7
	 #Spilling the return address to the 0th offset of the function
	 sw 	 x1 	 2000(sp)
	 #Picking up the new return address
	 li 		x1	28
	 #Function call happening
	 JAL label_2
	 #getting back the old return address
	 lw 	 x1 	 2000(sp)
	label_9:
	 #Putting  inside x9
	 mv 		x9	x8
	 #Putting _t15_2 inside x4
	 lw 	 x4 	 0(sp)
	 #Clearing x4 having value _t15_2
	 sw 		x4	0(sp)
	 #Putting 0 inside x4
	 li 		x4	 0
	 #Putting _t15_2 inside x6
	 lw 	 x6 	 0(sp)
	 #Putting val_2 inside x5
	 lw 	 x5 	 32(sp)
	seq		x7	x5	x6
	 BEQ		x7 ,	x0 ,	label_10
	 #Putting 1 inside x7
	 li 		x7	 1
	 #Clearing x5 having value val_2
	 sw 		x5	16(sp)
	 #Putting val_2 inside x5
	 lw 	 x5 	 32(sp)
	 #Clearing x4 having value 0
	 sw 		x4	0(sp)
	 #Putting _t18_3 inside x4
	 lw 	 x4 	 16(sp)
	add		x4	x5	x7
	 #Clearing x5 having value val_2
	 sw 		x5	16(sp)
	 #Putting _t18_3 inside x5
	 lw 	 x5 	 16(sp)
	 #Clearing x4 having value _t18_3
	 sw 		x4	8(sp)
	 #Putting val_2 inside x4
	 lw 	 x4 	 32(sp)
	 #Putting val_2 inside x5
	 #Clearing x5 having value val_2
	 sw 		x5	16(sp)
	 mv 		x5	x4
	 JAL label_11
	label_10:
	label_11:
	 #Clearing x7 having value 1
	 sw 		x7	0(sp)
	 #Putting 0 inside x7
	 li 		x7	 0
	 #Function returning
	 #Putting 0 inside x9
	 #Clearing x9 having value 0
	 sw 		x9	0(sp)
	 mv 		x9	x7
JAL x1;



	 #Function map_init


	 #Fetching params for map_init
	 #Putting  inside x8
	 mv 		x8	x12
	label_2:
	 #Putting _t2_3 inside x4
	 lw 	 x4 	 32(sp)
	 #Clearing x4 having value _t2_3
	 sw 		x4	16(sp)
	 #Putting 0 inside x4
	 li 		x4	 0
	 #Putting _t2_3 inside x6
	 lw 	 x6 	 32(sp)
	seq		x7	x8	x6
	 BEQ		x7 ,	x0 ,	label_3
	 #Putting 0 inside x7
	 li 		x7	 0
	 #Function returning
	 #Putting 0 inside x9
	 #Clearing x9 having value 0
	 sw 		x9	0(sp)
	 mv 		x9	x7
JAL x1;
	label_3:
	label_4:
	 #Clearing x7 having value 0
	 sw 		x7	0(sp)
	 #Putting 0 inside x7
	 li 		x7	 0
	 #Clearing x4 having value 0
	 sw 		x4	0(sp)
	 #Putting i_3 inside x4
	 lw 	 x4 	 80(sp)
	 #Putting i_3 inside x7
	 #Clearing x7 having value i_3
	 sw 		x7	40(sp)
	 mv 		x7	x4
	label_5:
	 #Putting i_3 inside x5
	 lw 	 x5 	 80(sp)
	slt		x8	x5	x7
	 BEQ		x8 ,	x0 ,	label_8
	 JAL label_6
	label_7:
	 #Clearing x5 having value i_3
	 sw 		x5	40(sp)
	 #Putting i_3 inside x5
	 lw 	 x5 	 80(sp)
	 #Putting i_3 inside x5
	 #Clearing x5 having value i_3
	 sw 		x5	40(sp)
	 mv 		x5	x7
	 #Clearing x5 having value i_3
	 sw 		x5	40(sp)
	 #Putting i_3 inside x5
	 lw 	 x5 	 80(sp)
	 #Clearing x4 having value i_3
	 sw 		x4	40(sp)
	 #Putting i_3 inside x4
	 lw 	 x4 	 80(sp)
	addi		x4	x5	1
	 JAL label_5
	label_6:
	 #Clearing x5 having value i_3
	 sw 		x5	40(sp)
	 #Putting i_3 inside x5
	 lw 	 x5 	 80(sp)
	 #Clearing x4 having value i_3
	 sw 		x4	40(sp)
	 #Putting _t8_4 inside x4
	 lw 	 x4 	 48(sp)
	muli		x4	x5	4
	 #Clearing x6 having value _t2_3
	 sw 		x6	16(sp)
	 #Putting _t8_4 inside x6
	 lw 	 x6 	 48(sp)
	 #Clearing x5 having value i_3
	 sw 		x5	40(sp)
	 #Putting *map._map_3 inside x5
	 lw 	 x5 	 -4(sp)
	 #Clearing x4 having value _t8_4
	 sw 		x4	24(sp)
	 #Putting _t9_4 inside x4
	 lw 	 x4 	 64(sp)
	add		x4	x5	x6
	 #Clearing x4 having value _t9_4
	 sw 		x4	32(sp)
	 #Putting _t10_4 inside x4
	 lw 	 x4 	 0(sp)
	 #Clearing x4 having value _t10_4
	 sw 		x4	0(sp)
	 #Putting 1 inside x4
	 li 		x4	 1
	 #Clearing x6 having value _t8_4
	 sw 		x6	24(sp)
	 #Putting _t10_4 inside x6
	 lw 	 x6 	 0(sp)
	 #Clearing x4 having value 1
	 sw 		x4	0(sp)
	 #Putting _t11_4 inside x4
	 lw 	 x4 	 16(sp)
	sub		x4	x0	x6
	 #Clearing x5 having value *map._map_3
	 sw 		x5	0(sp)
	 #Putting _t11_4 inside x5
	 lw 	 x5 	 16(sp)
	 #Clearing x4 having value _t11_4
	 sw 		x4	8(sp)
	 #Putting *_t9_4 inside x4
	 lw 	 x4 	 -4(sp)
	 #Putting *_t9_4 inside x5
	 #Clearing x5 having value *_t9_4
	 sw 		x5	0(sp)
	 mv 		x5	x4
	 JAL label_7
	label_8:
	 #Clearing x7 having value i_3
	 sw 		x7	40(sp)
	 #Putting 0 inside x7
	 li 		x7	 0
	 #Clearing x4 having value *_t9_4
	 sw 		x4	0(sp)
	 #Putting *map._size_3 inside x4
	 lw 	 x4 	 -4(sp)
	 #Putting *map._size_3 inside x7
	 #Clearing x7 having value *map._size_3
	 sw 		x7	0(sp)
	 mv 		x7	x4
	 #Clearing x7 having value *map._size_3
	 sw 		x7	0(sp)
	 #Putting 1 inside x7
	 li 		x7	 1
	 #Function returning
	 #Putting 1 inside x9
	 #Clearing x9 having value 1
	 sw 		x9	0(sp)
	 mv 		x9	x7
JAL x1;
