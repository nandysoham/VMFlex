.data

.text
	 .globl main
.main
	 #Moving sp to the Free segment
	 add 	 sp,    sp  , 2000
	 #Initializing Heap Address at First offset of main
	 li 		 x7 ,  x000
	 sw 		 x7 	2000(sp)
	 #Initializing Return Address at Second offset of main
	 li 		 x7 ,  x000
	 sw 		 x7, 	1996(sp)
	label_1:
	_t1_2 = #40
	_INTERNAL_MAP_SIZE_0 = _t1_2
	FunctionCall map_init
	param map_2
	call label_2
	label_9:
	_t14_2 = ReturnVal
	_t15_2 = #0
	seq		x19	x20	x18
	if ( _t16_2 == #0 ) goto label_10
	_t17_3 = #1
	add		x19	x20	x18
	val_2 = _t18_3
	goto label_11
	label_10:
	label_11:
	_t19_2 = #0
	Return _t19_2
	 #Fetching params for map_init
	 mv 		x20	x12
	label_2:
	_t2_3 = #0
	seq		x19	x20	x18
	if ( _t3_3 == #0 ) goto label_3
	_t4_4 = #0
	Return _t4_4
	label_3:
	label_4:
	_t5_4 = #0
	i_3 = _t5_4
	label_5:
	slt		x20	x19	x18
	if ( _t6_4 == #0 ) goto label_8
	goto label_6
	label_7:
	_t7_4 = i_3
	addi		x19	x19	1
	goto label_5
	label_6:
	muli		x18	x19	4
	 lw 	 x5-998000(sp)
	add		x20	x5	x18
	_t10_4 = #1
	_t11_4 = minus _t10_4
	*_t9_4 = _t11_4
	goto label_7
	label_8:
	_t12_3 = #0
	*map._size_3 = _t12_3
	_t13_3 = #1
	Return _t13_3
