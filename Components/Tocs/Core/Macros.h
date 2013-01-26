#pragma once

#define STRINGIFY(X) STRINGIFY_(X)
#define STRINGIFY_(X) STRINGIFY__(X)
#define STRINGIFY__(X) #X

#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2

#define EXPAND(X) EXPAND_(X)
#define EXPAND_(X) EXPAND__(X)
#define EXPAND__(X) X


#define NARG(...)\
	EXPAND (ARG_N(__VA_ARGS__,32,31,30,29,28,27,26,25,24,23,22,21,19,18,17,16,15,14,113,12,11,10,9,8,7,6,5,4,3,2,1,0))
#define ARG_N(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,N,...) N 


#define ITERATE_LIST(macro, ...) ITERATE_LIST__(SYNC_NARG(__VA_ARGS__), macro,__VA_ARGS__)
#define ITERATE_LIST__(N,macro, ...) EXPAND(CONCATENATE(ITERATE_LIST_,N)(macro,__VA_ARGS__))

#define ITERATE_LIST_0(macro, element)
#define ITERATE_LIST_1(macro, element) macro(element)

#define ITERATE_LIST_2(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_1(macro, __VA_ARGS__))

#define ITERATE_LIST_3(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_2(macro, __VA_ARGS__))

#define ITERATE_LIST_4(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_3(macro, __VA_ARGS__))

#define ITERATE_LIST_5(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_4(macro, __VA_ARGS__))

#define ITERATE_LIST_6(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_5(macro, __VA_ARGS__))

#define ITERATE_LIST_7(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_6(macro, __VA_ARGS__))

#define ITERATE_LIST_8(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_7(macro, __VA_ARGS__))

#define ITERATE_LIST_9(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_8(macro, __VA_ARGS__))

#define ITERATE_LIST_10(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_9(macro, __VA_ARGS__))

#define ITERATE_LIST_11(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_10(macro, __VA_ARGS__))

#define ITERATE_LIST_12(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_11(macro, __VA_ARGS__))

#define ITERATE_LIST_13(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_12(macro, __VA_ARGS__))

#define ITERATE_LIST_14(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_13(macro, __VA_ARGS__))

#define ITERATE_LIST_15(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_14(macro, __VA_ARGS__))

#define ITERATE_LIST_16(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_15(macro, __VA_ARGS__))

#define ITERATE_LIST_17(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_16(macro, __VA_ARGS__))

#define ITERATE_LIST_18(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_17(macro, __VA_ARGS__))

#define ITERATE_LIST_19(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_18(macro, __VA_ARGS__))

#define ITERATE_LIST_20(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_19(macro, __VA_ARGS__))

#define ITERATE_LIST_21(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_20(macro, __VA_ARGS__))

#define ITERATE_LIST_22(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_21(macro, __VA_ARGS__))

#define ITERATE_LIST_23(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_22(macro, __VA_ARGS__))

#define ITERATE_LIST_24(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_23(macro, __VA_ARGS__))

#define ITERATE_LIST_25(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_24(macro, __VA_ARGS__))

#define ITERATE_LIST_26(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_25(macro, __VA_ARGS__))

#define ITERATE_LIST_27(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_26(macro, __VA_ARGS__))

#define ITERATE_LIST_28(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_27(macro, __VA_ARGS__))

#define ITERATE_LIST_29(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_28(macro, __VA_ARGS__))

#define ITERATE_LIST_30(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_29(macro, __VA_ARGS__))

#define ITERATE_LIST_31(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_30(macro, __VA_ARGS__))

#define ITERATE_LIST_32(macro, element, ...) \
	macro (element) \
	EXPAND(ITERATE_LIST_31(macro, __VA_ARGS__))

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define ITERATE_LIST_I(macro, ...) ITERATE_LIST_I__(SYNC_NARG(__VA_ARGS__), macro,__VA_ARGS__)
#define ITERATE_LIST_I__(N,macro, ...) EXPAND(CONCATENATE(ITERATE_LIST_I_,N)(macro,__VA_ARGS__))

#define ITERATE_LIST_I_0(macro, element) 
#define ITERATE_LIST_I_1(macro, element) macro(element,0)

#define ITERATE_LIST_I_2(macro, element, ...) \
	macro (element,1) \
	EXPAND(ITERATE_LIST_I_1(macro, __VA_ARGS__))

#define ITERATE_LIST_I_3(macro, element, ...) \
	macro (element,2) \
	EXPAND(ITERATE_LIST_I_2(macro, __VA_ARGS__))

#define ITERATE_LIST_I_4(macro, element, ...) \
	macro (element,3) \
	EXPAND(ITERATE_LIST_I_3(macro, __VA_ARGS__))

#define ITERATE_LIST_I_5(macro, element, ...) \
	macro (element,4) \
	EXPAND(ITERATE_LIST_I_4(macro, __VA_ARGS__))

#define ITERATE_LIST_I_6(macro, element, ...) \
	macro (element,5) \
	EXPAND(ITERATE_LIST_I_5(macro, __VA_ARGS__))

#define ITERATE_LIST_I_7(macro, element, ...) \
	macro (element,6) \
	EXPAND(ITERATE_LIST_I_6(macro, __VA_ARGS__))

#define ITERATE_LIST_I_8(macro, element, ...) \
	macro (element,7) \
	EXPAND(ITERATE_LIST_7(macro, __VA_ARGS__))

#define ITERATE_LIST_I_9(macro, element, ...) \
	macro (element,8) \
	EXPAND(ITERATE_LIST_I_8(macro, __VA_ARGS__))

#define ITERATE_LIST_I_10(macro, element, ...) \
	macro (element,9) \
	EXPAND(ITERATE_LIST_I_9(macro, __VA_ARGS__))

#define ITERATE_LIST_I_11(macro, element, ...) \
	macro (element,10) \
	EXPAND(ITERATE_LIST_I_10(macro, __VA_ARGS__))

#define ITERATE_LIST_I_12(macro, element, ...) \
	macro (element,11) \
	EXPAND(ITERATE_LIST_I_11(macro, __VA_ARGS__))

#define ITERATE_LIST_I_13(macro, element, ...) \
	macro (element,12) \
	EXPAND(ITERATE_LIST_I_12(macro, __VA_ARGS__))

#define ITERATE_LIST_I_14(macro, element, ...) \
	macro (element,13) \
	EXPAND(ITERATE_LIST_I_13(macro, __VA_ARGS__))

#define ITERATE_LIST_I_15(macro, element, ...) \
	macro (element,14) \
	EXPAND(ITERATE_LIST_I_14(macro, __VA_ARGS__))

#define ITERATE_LIST_I_16(macro, element, ...) \
	macro (element,15) \
	EXPAND(ITERATE_LIST_I_15(macro, __VA_ARGS__))

#define ITERATE_LIST_I_17(macro, element, ...) \
	macro (element,16) \
	EXPAND(ITERATE_LIST_I_16(macro, __VA_ARGS__))

#define ITERATE_LIST_I_18(macro, element, ...) \
	macro (element,17) \
	EXPAND(ITERATE_LIST_I_17(macro, __VA_ARGS__))

#define ITERATE_LIST_I_19(macro, element, ...) \
	macro (element,18) \
	EXPAND(ITERATE_LIST_I_18(macro, __VA_ARGS__))

#define ITERATE_LIST_I_20(macro, element, ...) \
	macro (element,19) \
	EXPAND(ITERATE_LIST_I_19(macro, __VA_ARGS__))

#define ITERATE_LIST_I_21(macro, element, ...) \
	macro (element,20) \
	EXPAND(ITERATE_LIST_I_20(macro, __VA_ARGS__))

#define ITERATE_LIST_I_22(macro, element, ...) \
	macro (element,21) \
	EXPAND(ITERATE_LIST_I_21(macro, __VA_ARGS__))

#define ITERATE_LIST_I_23(macro, element, ...) \
	macro (element,22) \
	EXPAND(ITERATE_LIST_I_22(macro, __VA_ARGS__))

#define ITERATE_LIST_I_24(macro, element, ...) \
	macro (element,23) \
	EXPAND(ITERATE_LIST_I_23(macro, __VA_ARGS__))

#define ITERATE_LIST_I_25(macro, element, ...) \
	macro (element,24) \
	EXPAND(ITERATE_LIST_I_24(macro, __VA_ARGS__))

#define ITERATE_LIST_I_26(macro, element, ...) \
	macro (element,25) \
	EXPAND(ITERATE_LIST_I_25(macro, __VA_ARGS__))

#define ITERATE_LIST_I_27(macro, element, ...) \
	macro (element,26) \
	EXPAND(ITERATE_LIST_I_26(macro, __VA_ARGS__))

#define ITERATE_LIST_I_28(macro, element, ...) \
	macro (element,27) \
	EXPAND(ITERATE_LIST_I_27(macro, __VA_ARGS__))

#define ITERATE_LIST_I_29(macro, element, ...) \
	macro (element,28) \
	EXPAND(ITERATE_LIST_I_28(macro, __VA_ARGS__))

#define ITERATE_LIST_I_30(macro, element, ...) \
	macro (element,29) \
	EXPAND(ITERATE_LIST_I_29(macro, __VA_ARGS__))

#define ITERATE_LIST_I_31(macro, element, ...) \
	macro (element,30) \
	EXPAND(ITERATE_LIST_I_30(macro, __VA_ARGS__))

#define ITERATE_LIST_I_32(macro, element, ...) \
	macro (element,31) \
	EXPAND(ITERATE_LIST_I_31(macro, __VA_ARGS__))