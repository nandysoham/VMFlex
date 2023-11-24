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
	FunctionCall map_init
	param map_2
	call label_2
	label_9:
	 #Putting  inside x7
	 mv 		x7	x8
	 lw 	 x4-998000(sp)
	 #Putting 0 inside x4
	 li 		x4	 0
	 lw 	 x6-998000(sp)
	 lw 	 x5-998000(sp)
	seq		x7	x5	x6
	if ( _t16_2 == #0 ) goto label_10
	 #Putting 1 inside x7
	 li 		x7	 1
	 lw 	 x5-998000(sp)
	 #Clearing x4 having value 0
	 lw 	 x4-998000(sp)
	add		x4	x5	x7
	 lw 	 x5-998000(sp)
	 #Clearing x4 having value 0
	 lw 	 x4-998000(sp)
	 #Putting 0 inside x5
	 #Clearing x5 having value 0
	 mv 		x5	x4
	goto label_11
	label_10:
	label_11:
	 #Clearing x7 having value 1
	 #Putting 0 inside x7
	 li 		x7	 0
	Return _t19_2



	 #Function map_init


	 #Fetching params for map_init
	 #Putting  inside x8
	 mv 		x8	x12
	label_2:
	 lw 	 x4-998000(sp)
	 #Putting 0 inside x4
	 li 		x4	 0
	 lw 	 x6-998000(sp)
	seq		x7	x8	x6
	if ( _t3_3 == #0 ) goto label_3
	 #Putting 0 inside x7
	 li 		x7	 0
	Return _t4_4
	label_3:
	label_4:
	 #Clearing x7 having value 0
	 #Putting 0 inside x7
	 li 		x7	 0
	 #Clearing x4 having value 0
	 lw 	 x4-998000(sp)
	 #Putting 0 inside x7
	 #Clearing x7 having value 0
	 mv 		x7	x4
	label_5:
	 lw 	 x5-998000(sp)
	slt		x8	x5	x7
	if ( _t6_4 == #0 ) goto label_8
	goto label_6
	label_7:
	 lw 	 x5-998000(sp)
	 #Putting 0 inside x5
	 #Clearing x5 having value 0
	 mv 		x5	x7
	 #Clearing x5 having value 0
	 lw 	 x5-998000(sp)
	 #Clearing x4 having value 0
	 lw 	 x4-998000(sp)
	addi		x4	x5	1
	goto label_5
	label_6:
	 #Clearing x5 having value 0
	 lw 	 x5-998000(sp)
	 #Clearing x4 having value 0
	 lw 	 x4-998000(sp)
	muli		x4	x5	4
	 lw 	 x6-998000(sp)
	 #Clearing x5 having value 0
	 lw 	 x5-998000(sp)
	 #Clearing x4 having value 0
	 lw 	 x4-998000(sp)
	add		x4	x5	x6
	 #Clearing x4 having value 0
	 lw 	 x4-998000(sp)
	 #Clearing x4 having value 0
	 #Putting 1 inside x4
	 li 		x4	 1
	 lw 	 x6-998000(sp)
	 #Clearing x4 having value 1
	 lw 	 x4-998000(sp)
	sub		x4	x0	x6
	 #Clearing x5 having value 0
	 lw 	 x5-998000(sp)
	 #Clearing x4 having value 1
	 lw 	 x4-998000(sp)
	 #Putting 1 inside x5
	 #Clearing x5 having value 1
	 mv 		x5	x4
	goto label_7
	label_8:
	 #Clearing x7 having value 0
	 #Putting 0 inside x7
	 li 		x7	 0
	 #Clearing x4 having value 1
	 lw 	 x4-998000(sp)
	 #Putting 1 inside x7
	 #Clearing x7 having value 1
	 mv 		x7	x4
	 #Clearing x7 having value 1
	 #Putting 1 inside x7
	 li 		x7	 1
	Return _t13_3
