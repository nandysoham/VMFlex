label_1:
_t1_2 = y_2 + x_2
c_2 = _t1_2
_t2_2 = y_2 < x_2
if ( _t2_2 == #0 ) goto label_2
_t3_3 = #1
_t4_3 = y_2 + _t3_3
y_2 = _t4_3
goto label_3
label_2:
label_3:
Return c_2

label_4:
_t5_2 = #1
a_2 = _t5_2
_t6_2 = #2
b_2 = _t6_2
FunctionCall fn1
param a_2
param b_2
call label_1
label_5:
_t7_2 = ReturnVal
_t8_2 = #3
c_2 = _t8_2
_t9_2 = #4
d_2 = _t9_2
FunctionCall fn1
param d_2
param c_2
call label_1
label_6:
_t10_2 = ReturnVal

