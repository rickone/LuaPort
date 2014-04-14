#pragma once
#
#define LUACG_CAT(a, b) LUACG_CAT_X(a, b)
#define LUACG_CAT_X(a, b) a##b
#
#define LUACG_INC(n) LUACG_CAT(LUACG_INC_, n)
#define LUACG_INC_0 1
#define LUACG_INC_1 2
#define LUACG_INC_2 3
#define LUACG_INC_3 4
#define LUACG_INC_4 5
#define LUACG_INC_5 6
#define LUACG_INC_6 7
#define LUACG_INC_7 8
#define LUACG_INC_8 9
#define LUACG_INC_9 10
#define LUACG_INC_10 11
#define LUACG_INC_11 12
#define LUACG_INC_12 13
#define LUACG_INC_13 14
#define LUACG_INC_14 15
#define LUACG_INC_15 16
#define LUACG_INC_16 17
#define LUACG_INC_17 18
#define LUACG_INC_18 19
#define LUACG_INC_19 20
#define LUACG_INC_20 21
#define LUACG_INC_21 22
#define LUACG_INC_22 23
#define LUACG_INC_23 24
#define LUACG_INC_24 25
#define LUACG_INC_25 26
#define LUACG_INC_26 27
#define LUACG_INC_27 28
#define LUACG_INC_28 29
#define LUACG_INC_29 30
#define LUACG_INC_30 31
#define LUACG_INC_31 0
#
#define LUACG_DEC(n) LUACG_CAT(LUACG_DEC_, n)
#define LUACG_DEC_0 31
#define LUACG_DEC_1 0
#define LUACG_DEC_2 1
#define LUACG_DEC_3 2
#define LUACG_DEC_4 3
#define LUACG_DEC_5 4
#define LUACG_DEC_6 5
#define LUACG_DEC_7 6
#define LUACG_DEC_8 7
#define LUACG_DEC_9 8
#define LUACG_DEC_10 9
#define LUACG_DEC_11 10
#define LUACG_DEC_12 11
#define LUACG_DEC_13 12
#define LUACG_DEC_14 13
#define LUACG_DEC_15 14
#define LUACG_DEC_16 15
#define LUACG_DEC_17 16
#define LUACG_DEC_18 17
#define LUACG_DEC_19 18
#define LUACG_DEC_20 19
#define LUACG_DEC_21 20
#define LUACG_DEC_22 21
#define LUACG_DEC_23 22
#define LUACG_DEC_24 23
#define LUACG_DEC_25 24
#define LUACG_DEC_26 25
#define LUACG_DEC_27 26
#define LUACG_DEC_28 27
#define LUACG_DEC_29 28
#define LUACG_DEC_30 29
#define LUACG_DEC_31 30
#
#define LUACG_TOBOOL(n) LUACG_CAT(LUACG_TOBOOL_, n)
#define LUACG_TOBOOL_0 0
#define LUACG_TOBOOL_1 1
#define LUACG_TOBOOL_2 1
#define LUACG_TOBOOL_3 1
#define LUACG_TOBOOL_4 1
#define LUACG_TOBOOL_5 1
#define LUACG_TOBOOL_6 1
#define LUACG_TOBOOL_7 1
#define LUACG_TOBOOL_8 1
#define LUACG_TOBOOL_9 1
#define LUACG_TOBOOL_10 1
#define LUACG_TOBOOL_11 1
#define LUACG_TOBOOL_12 1
#define LUACG_TOBOOL_13 1
#define LUACG_TOBOOL_14 1
#define LUACG_TOBOOL_15 1
#define LUACG_TOBOOL_16 1
#define LUACG_TOBOOL_17 1
#define LUACG_TOBOOL_18 1
#define LUACG_TOBOOL_19 1
#define LUACG_TOBOOL_20 1
#define LUACG_TOBOOL_21 1
#define LUACG_TOBOOL_22 1
#define LUACG_TOBOOL_23 1
#define LUACG_TOBOOL_24 1
#define LUACG_TOBOOL_25 1
#define LUACG_TOBOOL_26 1
#define LUACG_TOBOOL_27 1
#define LUACG_TOBOOL_28 1
#define LUACG_TOBOOL_29 1
#define LUACG_TOBOOL_30 1
#define LUACG_TOBOOL_31 1
#
#define LUACG_COMMA() ,
#define LUACG_COMMA_IF(c) LUACG_CAT(LUACG_COMMA_IF_, LUACG_TOBOOL(c))
#define LUACG_COMMA_IF_0
#define LUACG_COMMA_IF_1 LUACG_COMMA()
#
#define LUACG_LEFT_PAR() (
#define LUACG_RIGHT_PAR() )
#
#define LUACG_REPEAT(n, a, f) LUACG_CAT(LUACG_REPEAT_, n)(LUACG_DEC(n), a, f)
#define LUACG_REPEAT_0(n, a, f)
#define LUACG_REPEAT_1(n, a, f) f(a, n)
#define LUACG_REPEAT_2(n, a, f) LUACG_REPEAT_1(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_3(n, a, f) LUACG_REPEAT_2(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_4(n, a, f) LUACG_REPEAT_3(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_5(n, a, f) LUACG_REPEAT_4(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_6(n, a, f) LUACG_REPEAT_5(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_7(n, a, f) LUACG_REPEAT_6(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_8(n, a, f) LUACG_REPEAT_7(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_9(n, a, f) LUACG_REPEAT_8(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_10(n, a, f) LUACG_REPEAT_9(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_11(n, a, f) LUACG_REPEAT_10(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_12(n, a, f) LUACG_REPEAT_11(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_13(n, a, f) LUACG_REPEAT_12(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_14(n, a, f) LUACG_REPEAT_13(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_15(n, a, f) LUACG_REPEAT_14(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_16(n, a, f) LUACG_REPEAT_15(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_17(n, a, f) LUACG_REPEAT_16(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_18(n, a, f) LUACG_REPEAT_17(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_19(n, a, f) LUACG_REPEAT_18(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_20(n, a, f) LUACG_REPEAT_19(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_21(n, a, f) LUACG_REPEAT_20(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_22(n, a, f) LUACG_REPEAT_21(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_23(n, a, f) LUACG_REPEAT_22(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_24(n, a, f) LUACG_REPEAT_23(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_25(n, a, f) LUACG_REPEAT_24(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_26(n, a, f) LUACG_REPEAT_25(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_27(n, a, f) LUACG_REPEAT_26(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_28(n, a, f) LUACG_REPEAT_27(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_29(n, a, f) LUACG_REPEAT_28(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_30(n, a, f) LUACG_REPEAT_29(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_31(n, a, f) LUACG_REPEAT_30(LUACG_DEC(n), a, f)f(a, n)
#define LUACG_REPEAT_32(n, a, f) LUACG_REPEAT_31(LUACG_DEC(n), a, f)f(a, n)
#
#define LUACG_SELECT(n, i, d) LUACG_CAT(LUACG_SELECT_, LUACG_CAT(n, LUACG_CAT(_, i)))d
#define LUACG_SELECT_1_0(a0) a0
#define LUACG_SELECT_2_0(a0, a1) a0
#define LUACG_SELECT_2_1(a0, a1) a1
#define LUACG_SELECT_3_0(a0, a1, a2) a0
#define LUACG_SELECT_3_1(a0, a1, a2) a1
#define LUACG_SELECT_3_2(a0, a1, a2) a2
#define LUACG_SELECT_4_0(a0, a1, a2, a3) a0
#define LUACG_SELECT_4_1(a0, a1, a2, a3) a1
#define LUACG_SELECT_4_2(a0, a1, a2, a3) a2
#define LUACG_SELECT_4_3(a0, a1, a2, a3) a3
#define LUACG_SELECT_5_0(a0, a1, a2, a3, a4) a0
#define LUACG_SELECT_5_1(a0, a1, a2, a3, a4) a1
#define LUACG_SELECT_5_2(a0, a1, a2, a3, a4) a2
#define LUACG_SELECT_5_3(a0, a1, a2, a3, a4) a3
#define LUACG_SELECT_5_4(a0, a1, a2, a3, a4) a4
#define LUACG_SELECT_6_0(a0, a1, a2, a3, a4, a5) a0
#define LUACG_SELECT_6_1(a0, a1, a2, a3, a4, a5) a1
#define LUACG_SELECT_6_2(a0, a1, a2, a3, a4, a5) a2
#define LUACG_SELECT_6_3(a0, a1, a2, a3, a4, a5) a3
#define LUACG_SELECT_6_4(a0, a1, a2, a3, a4, a5) a4
#define LUACG_SELECT_6_5(a0, a1, a2, a3, a4, a5) a5
#define LUACG_SELECT_7_0(a0, a1, a2, a3, a4, a5, a6) a0
#define LUACG_SELECT_7_1(a0, a1, a2, a3, a4, a5, a6) a1
#define LUACG_SELECT_7_2(a0, a1, a2, a3, a4, a5, a6) a2
#define LUACG_SELECT_7_3(a0, a1, a2, a3, a4, a5, a6) a3
#define LUACG_SELECT_7_4(a0, a1, a2, a3, a4, a5, a6) a4
#define LUACG_SELECT_7_5(a0, a1, a2, a3, a4, a5, a6) a5
#define LUACG_SELECT_7_6(a0, a1, a2, a3, a4, a5, a6) a6
#define LUACG_SELECT_8_0(a0, a1, a2, a3, a4, a5, a6, a7) a0
#define LUACG_SELECT_8_1(a0, a1, a2, a3, a4, a5, a6, a7) a1
#define LUACG_SELECT_8_2(a0, a1, a2, a3, a4, a5, a6, a7) a2
#define LUACG_SELECT_8_3(a0, a1, a2, a3, a4, a5, a6, a7) a3
#define LUACG_SELECT_8_4(a0, a1, a2, a3, a4, a5, a6, a7) a4
#define LUACG_SELECT_8_5(a0, a1, a2, a3, a4, a5, a6, a7) a5
#define LUACG_SELECT_8_6(a0, a1, a2, a3, a4, a5, a6, a7) a6
#define LUACG_SELECT_8_7(a0, a1, a2, a3, a4, a5, a6, a7) a7
#
#define LUACG_ENUM(n, a, f) LUACG_REPEAT(n, (a, f), LUACG_ENUM_F)
#define LUACG_ENUM_F(af, n) LUACG_COMMA_IF(n)LUACG_SELECT(2, 1, af)(LUACG_SELECT(2, 0, af), n)
#
#define LUACG_ENUM_PARAMS(n, a) LUACG_ENUM(n, a, LUACG_ENUM_PARAMS_F)
#define LUACG_ENUM_PARAMS_F(a, n) LUACG_CAT(a, n)
#
#define LUACG_ITERATE() "LuaForward.h"
#
#define LUACG_ITERATOR_0 LUACG_ITERATOR_BEGIN
#define LUACG_ITERATOR_1 LUACG_INC(LUACG_ITERATOR_0)
#define LUACG_ITERATOR_2 LUACG_INC(LUACG_ITERATOR_1)
#define LUACG_ITERATOR_3 LUACG_INC(LUACG_ITERATOR_2)
#define LUACG_ITERATOR_4 LUACG_INC(LUACG_ITERATOR_3)
#define LUACG_ITERATOR_5 LUACG_INC(LUACG_ITERATOR_4)
#define LUACG_ITERATOR_6 LUACG_INC(LUACG_ITERATOR_5)
#define LUACG_ITERATOR_7 LUACG_INC(LUACG_ITERATOR_6)
#define LUACG_ITERATOR_8 LUACG_INC(LUACG_ITERATOR_7)
#define LUACG_ITERATOR_9 LUACG_INC(LUACG_ITERATOR_8)
#define LUACG_ITERATOR_10 LUACG_INC(LUACG_ITERATOR_9)
#define LUACG_ITERATOR_11 LUACG_INC(LUACG_ITERATOR_10)
#define LUACG_ITERATOR_12 LUACG_INC(LUACG_ITERATOR_11)
#define LUACG_ITERATOR_13 LUACG_INC(LUACG_ITERATOR_12)
#define LUACG_ITERATOR_14 LUACG_INC(LUACG_ITERATOR_13)
#define LUACG_ITERATOR_15 LUACG_INC(LUACG_ITERATOR_14)
#define LUACG_ITERATOR_16 LUACG_INC(LUACG_ITERATOR_15)
#define LUACG_ITERATOR_17 LUACG_INC(LUACG_ITERATOR_16)
#define LUACG_ITERATOR_18 LUACG_INC(LUACG_ITERATOR_17)
#define LUACG_ITERATOR_19 LUACG_INC(LUACG_ITERATOR_18)
#define LUACG_ITERATOR_20 LUACG_INC(LUACG_ITERATOR_19)
#define LUACG_ITERATOR_21 LUACG_INC(LUACG_ITERATOR_20)
#define LUACG_ITERATOR_22 LUACG_INC(LUACG_ITERATOR_21)
#define LUACG_ITERATOR_23 LUACG_INC(LUACG_ITERATOR_22)
#define LUACG_ITERATOR_24 LUACG_INC(LUACG_ITERATOR_23)
#define LUACG_ITERATOR_25 LUACG_INC(LUACG_ITERATOR_24)
#define LUACG_ITERATOR_26 LUACG_INC(LUACG_ITERATOR_25)
#define LUACG_ITERATOR_27 LUACG_INC(LUACG_ITERATOR_26)
#define LUACG_ITERATOR_28 LUACG_INC(LUACG_ITERATOR_27)
#define LUACG_ITERATOR_29 LUACG_INC(LUACG_ITERATOR_28)
#define LUACG_ITERATOR_30 LUACG_INC(LUACG_ITERATOR_29)
#define LUACG_ITERATOR_31 LUACG_INC(LUACG_ITERATOR_30)
#define LUACG_ITERATOR_32 LUACG_INC(LUACG_ITERATOR_31)
