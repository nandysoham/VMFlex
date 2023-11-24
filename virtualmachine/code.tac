label_1:
_t1_2 = #40
_INTERNAL_MAP_SIZE_0 = _t1_2
FunctionCall map_init
param map_2
call label_2
label_9:
_t14_2 = ReturnVal
_t15_2 = #0
_t16_2 = val_2 == _t15_2
if ( _t16_2 == #0 ) goto label_10
_t17_3 = #1
_t18_3 = val_2 + _t17_3
val_2 = _t18_3
goto label_11
label_10:
label_11:
_t19_2 = #0
Return _t19_2

label_2:
_t2_3 = #0
_t3_3 = map_3 == _t2_3
if ( _t3_3 == #0 ) goto label_3
_t4_4 = #0
Return _t4_4
goto label_4
label_3:
label_4:
_t5_4 = #0
i_3 = _t5_4
label_5:
_t6_4 = i_3 < _INTERNAL_MAP_SIZE_0
if ( _t6_4 == #0 ) goto label_8
goto label_6
label_7:
_t7_4 = i_3
i_3 = i_3 + #1
goto label_5
label_6:
_t8_4 = i_3 * #4
_t9_4 = *map._map_3 + _t8_4
_t10_4 = #1
_t11_4 = minus _t10_4
*_t9_4 = _t11_4
goto label_7
label_8:
_t12_3 = #0
*map._size_3 = _t12_3
_t13_3 = #1
Return _t13_3

