label_1:
Return a_2

label_2:
Return s_2

label_3:
_t1_2 = #1
k_2 = _t1_2
_t2_3 = #1
k_2 = _t2_3
label_4:
_t3_3 = #2
_t4_3 = k_2 < _t3_3
if ( _t4_3 == #0 ) goto label_7
goto label_5
label_6:
_t5_3 = k_2
k_2 = k_2 + #1
goto label_4
label_5:
_t6_3 = #2
lal_3 = _t6_3
_t7_3 = r_2
r_2 = r_2 + #1
goto label_6
label_7:
_t8_2 = #3
lal_3 = _t8_2
_t21_2 = #1
j_2 = _t21_2
FunctionCall fi
_t22_2 = #0
param _t22_2
_t23_2 = #1
param _t23_2
call label_8
label_9:
_t24_2 = ReturnVal
_t25_2 = #0
Return _t25_2
_t26_2 = #1
val_2 = _t26_2
_t27_2 = #2
_t28_2 = _t27_2 * val_2
_t29_2 = #1
_t30_2 = _t28_2 + _t29_2
val_2 = _t30_2
_t31_2 = #1
_t32_2 = val_2 + _t31_2
val_2 = _t32_2

label_8:
_t9_3 = #10
c_0_3 = _t9_3
memory c_3 _t9_3 #4
_t10_3 = #7
_t11_3 = _t10_3 * #4
_t12_3 = c_3 + _t11_3
_t13_3 = a_3 + b_3
_t14_3 = _t13_3 + lal_3
*_t12_3 = _t14_3
_t15_3 = #7
_t16_3 = _t15_3 * #4
_t17_3 = c_3 + _t16_3
Return *_t17_3
_t18_3 = #0
s_3 = _t18_3
_t19_3 = #1
_t20_3 = s_3 + _t19_3
s_3 = _t20_3

