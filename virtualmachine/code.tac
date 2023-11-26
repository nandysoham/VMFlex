label_1:
_t1_2 = #20
n_2 = _t1_2
_t2_2 = #30
m_2 = _t2_2
_t3_2 = #4
_t4_2 = _t3_2 * n_2
memory _t5_2 _t4_2 #1
A_2 = _t5_2
_t6_3 = #0
i_2 = _t6_3
label_2:
_t7_3 = i_2 < n_2
if ( _t7_3 == #0 ) goto label_5
goto label_3
label_4:
_t8_3 = i_2
i_2 = i_2 + #1
goto label_2
label_3:
_t9_3 = i_2 * #4
_t10_3 = A_2 + _t9_3
_t11_3 = #4
_t12_3 = _t11_3 * m_2
memory _t13_3 _t12_3 #1
*_t10_3 = _t13_3
goto label_4
label_5:
_t14_3 = #0
i_2 = _t14_3
label_6:
_t15_3 = i_2 < n_2
if ( _t15_3 == #0 ) goto label_9
goto label_7
label_8:
_t16_3 = i_2
i_2 = i_2 + #1
goto label_6
label_7:
_t17_4 = #0
j_2 = _t17_4
label_10:
_t18_4 = j_2 < m_2
if ( _t18_4 == #0 ) goto label_13
goto label_11
label_12:
_t19_4 = j_2
j_2 = j_2 + #1
goto label_10
label_11:
_t20_4 = i_2 * #4
_t21_4 = A_2 + _t20_4
_t22_4 = j_2 * #4
_t23_4 = *_t21_4 + _t22_4
_t24_4 = #1
*_t23_4 = _t24_4
goto label_12
label_13:
goto label_8
label_9:
_t25_2 = #0
Return _t25_2

