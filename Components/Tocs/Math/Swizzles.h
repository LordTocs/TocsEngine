#pragma once

#define SWIZZELS(...)

#define SWIZZELS_LIST_4(A, B, C, D) \

#define PERMUTATE_3(A, B, C, GENERATOR) \
	GENERATOR(A,A,A) \
	GENERATOR(A,A,B) \
	GENERATOR(A,A,C) \
	\
	GENERATOR(A,B,A) \
	GENERATOR(A,B,B) \
	GENERATOR(A,B,C) \
	\
	GENERATOR(A,C,A) \
	GENERATOR(A,C,B) \
	GENERATOR(A,C,C) \
	\
	\
	GENERATOR(B,A,A) \
	GENERATOR(B,A,B) \
	GENERATOR(B,A,C) \
	\
	GENERATOR(B,B,A) \
	GENERATOR(B,B,B) \
	GENERATOR(B,B,C) \
	\
	GENERATOR(B,C,A) \
	GENERATOR(B,C,B) \
	GENERATOR(B,C,C) \
	\
	\
	GENERATOR(C,A,A) \
	GENERATOR(C,A,B) \
	GENERATOR(C,A,C) \
	\
	GENERATOR(C,B,A) \
	GENERATOR(C,B,B) \
	GENERATOR(C,B,C) \
	\
	GENERATOR(C,C,A) \
	GENERATOR(C,C,B) \
	GENERATOR(C,C,C) \

#define PERMUTATE_4(A, B, C, D, GENERATOR) \
	GENERATOR(A,A,A,A) \
	GENERATOR(A,A,A,B) \
	GENERATOR(A,A,A,C) \
	GENERATOR(A,A,A,D) \
	\
	GENERATOR(A,A,B,A) \
	GENERATOR(A,A,B,B) \
	GENERATOR(A,A,B,C) \
	GENERATOR(A,A,B,D) \
	\
	GENERATOR(A,A,C,A) \
	GENERATOR(A,A,C,B) \
	GENERATOR(A,A,C,C) \
	GENERATOR(A,A,C,D) \
	\
	GENERATOR(A,A,D,A) \
	GENERATOR(A,A,D,B) \
	GENERATOR(A,A,D,C) \
	GENERATOR(A,A,D,D) \
	\
	\
	GENERATOR(A,B,A,A) \
	GENERATOR(A,B,A,B) \
	GENERATOR(A,B,A,C) \
	GENERATOR(A,B,A,D) \
	\
	GENERATOR(A,B,B,A) \
	GENERATOR(A,B,B,B) \
	GENERATOR(A,B,B,C) \
	GENERATOR(A,B,B,D) \
	\
	GENERATOR(A,B,C,A) \
	GENERATOR(A,B,C,B) \
	GENERATOR(A,B,C,C) \
	GENERATOR(A,B,C,D) \
	\
	GENERATOR(A,B,D,A) \
	GENERATOR(A,B,D,B) \
	GENERATOR(A,B,D,C) \
	GENERATOR(A,B,D,D) \
	\
	\
	GENERATOR(A,C,A,A) \
	GENERATOR(A,C,A,B) \
	GENERATOR(A,C,A,C) \
	GENERATOR(A,C,A,D) \
	\
	GENERATOR(A,C,B,A) \
	GENERATOR(A,C,B,B) \
	GENERATOR(A,C,B,C) \
	GENERATOR(A,C,B,D) \
	\
	GENERATOR(A,C,C,A) \
	GENERATOR(A,C,C,B) \
	GENERATOR(A,C,C,C) \
	GENERATOR(A,C,C,D) \
	\
	GENERATOR(A,C,D,A) \
	GENERATOR(A,C,D,B) \
	GENERATOR(A,C,D,C) \
	GENERATOR(A,C,D,D) \
	\
	\
	GENERATOR(A,D,A,A) \
	GENERATOR(A,D,A,B) \
	GENERATOR(A,D,A,C) \
	GENERATOR(A,D,A,D) \
	\
	GENERATOR(A,D,B,A) \
	GENERATOR(A,D,B,B) \
	GENERATOR(A,D,B,C) \
	GENERATOR(A,D,B,D) \
	\
	GENERATOR(A,D,C,A) \
	GENERATOR(A,D,C,B) \
	GENERATOR(A,D,C,C) \
	GENERATOR(A,D,C,D) \
	\
	GENERATOR(A,D,D,A) \
	GENERATOR(A,D,D,B) \
	GENERATOR(A,D,D,C) \
	GENERATOR(A,D,D,D) \
	\
	\
	\
	\
	GENERATOR(B,A,A,A) \
	GENERATOR(B,A,A,B) \
	GENERATOR(B,A,A,C) \
	GENERATOR(B,A,A,D) \
	\
	GENERATOR(B,A,B,A) \
	GENERATOR(B,A,B,B) \
	GENERATOR(B,A,B,C) \
	GENERATOR(B,A,B,D) \
	\
	GENERATOR(B,A,C,A) \
	GENERATOR(B,A,C,B) \
	GENERATOR(B,A,C,C) \
	GENERATOR(B,A,C,D) \
	\
	GENERATOR(B,A,D,A) \
	GENERATOR(B,A,D,B) \
	GENERATOR(B,A,D,C) \
	GENERATOR(B,A,D,D) \
	\
	\
	GENERATOR(B,B,A,A) \
	GENERATOR(B,B,A,B) \
	GENERATOR(B,B,A,C) \
	GENERATOR(B,B,A,D) \
	\
	GENERATOR(B,B,B,A) \
	GENERATOR(B,B,B,B) \
	GENERATOR(B,B,B,C) \
	GENERATOR(B,B,B,D) \
	\
	GENERATOR(B,B,C,A) \
	GENERATOR(B,B,C,B) \
	GENERATOR(B,B,C,C) \
	GENERATOR(B,B,C,D) \
	\
	GENERATOR(B,B,D,A) \
	GENERATOR(B,B,D,B) \
	GENERATOR(B,B,D,C) \
	GENERATOR(B,B,D,D) \
	\
	\
	GENERATOR(B,C,A,A) \
	GENERATOR(B,C,A,B) \
	GENERATOR(B,C,A,C) \
	GENERATOR(B,C,A,D) \
	\
	GENERATOR(B,C,B,A) \
	GENERATOR(B,C,B,B) \
	GENERATOR(B,C,B,C) \
	GENERATOR(B,C,B,D) \
	\
	GENERATOR(B,C,C,A) \
	GENERATOR(B,C,C,B) \
	GENERATOR(B,C,C,C) \
	GENERATOR(B,C,C,D) \
	\
	GENERATOR(B,C,D,A) \
	GENERATOR(B,C,D,B) \
	GENERATOR(B,C,D,C) \
	GENERATOR(B,C,D,D) \
	\
	\
	GENERATOR(B,D,A,A) \
	GENERATOR(B,D,A,B) \
	GENERATOR(B,D,A,C) \
	GENERATOR(B,D,A,D) \
	\
	GENERATOR(B,D,B,A) \
	GENERATOR(B,D,B,B) \
	GENERATOR(B,D,B,C) \
	GENERATOR(B,D,B,D) \
	\
	GENERATOR(B,D,C,A) \
	GENERATOR(B,D,C,B) \
	GENERATOR(B,D,C,C) \
	GENERATOR(B,D,C,D) \
	\
	GENERATOR(B,D,D,A) \
	GENERATOR(B,D,D,B) \
	GENERATOR(B,D,D,C) \
	GENERATOR(B,D,D,D) \
	\
	\
	\
	\
	GENERATOR(C,A,A,A) \
	GENERATOR(C,A,A,B) \
	GENERATOR(C,A,A,C) \
	GENERATOR(C,A,A,D) \
	\
	GENERATOR(C,A,B,A) \
	GENERATOR(C,A,B,B) \
	GENERATOR(C,A,B,C) \
	GENERATOR(C,A,B,D) \
	\
	GENERATOR(C,A,C,A) \
	GENERATOR(C,A,C,B) \
	GENERATOR(C,A,C,C) \
	GENERATOR(C,A,C,D) \
	\
	GENERATOR(C,A,D,A) \
	GENERATOR(C,A,D,B) \
	GENERATOR(C,A,D,C) \
	GENERATOR(C,A,D,D) \
	\
	\
	GENERATOR(C,B,A,A) \
	GENERATOR(C,B,A,B) \
	GENERATOR(C,B,A,C) \
	GENERATOR(C,B,A,D) \
	\
	GENERATOR(C,B,B,A) \
	GENERATOR(C,B,B,B) \
	GENERATOR(C,B,B,C) \
	GENERATOR(C,B,B,D) \
	\
	GENERATOR(C,B,C,A) \
	GENERATOR(C,B,C,B) \
	GENERATOR(C,B,C,C) \
	GENERATOR(C,B,C,D) \
	\
	GENERATOR(C,B,D,A) \
	GENERATOR(C,B,D,B) \
	GENERATOR(C,B,D,C) \
	GENERATOR(C,B,D,D) \
	\
	\
	GENERATOR(C,C,A,A) \
	GENERATOR(C,C,A,B) \
	GENERATOR(C,C,A,C) \
	GENERATOR(C,C,A,D) \
	\
	GENERATOR(C,C,B,A) \
	GENERATOR(C,C,B,B) \
	GENERATOR(C,C,B,C) \
	GENERATOR(C,C,B,D) \
	\
	GENERATOR(C,C,C,A) \
	GENERATOR(C,C,C,B) \
	GENERATOR(C,C,C,C) \
	GENERATOR(C,C,C,D) \
	\
	GENERATOR(C,C,D,A) \
	GENERATOR(C,C,D,B) \
	GENERATOR(C,C,D,C) \
	GENERATOR(C,C,D,D) \
	\
	\
	GENERATOR(C,D,A,A) \
	GENERATOR(C,D,A,B) \
	GENERATOR(C,D,A,C) \
	GENERATOR(C,D,A,D) \
	\
	GENERATOR(C,D,B,A) \
	GENERATOR(C,D,B,B) \
	GENERATOR(C,D,B,C) \
	GENERATOR(C,D,B,D) \
	\
	GENERATOR(C,D,C,A) \
	GENERATOR(C,D,C,B) \
	GENERATOR(C,D,C,C) \
	GENERATOR(C,D,C,D) \
	\
	GENERATOR(C,D,D,A) \
	GENERATOR(C,D,D,B) \
	GENERATOR(C,D,D,C) \
	GENERATOR(C,D,D,D) \
	\
	\
	\
	\
	GENERATOR(D,A,A,A) \
	GENERATOR(D,A,A,B) \
	GENERATOR(D,A,A,C) \
	GENERATOR(D,A,A,D) \
	\
	GENERATOR(D,A,B,A) \
	GENERATOR(D,A,B,B) \
	GENERATOR(D,A,B,C) \
	GENERATOR(D,A,B,D) \
	\
	GENERATOR(D,A,C,A) \
	GENERATOR(D,A,C,B) \
	GENERATOR(D,A,C,C) \
	GENERATOR(D,A,C,D) \
	\
	GENERATOR(D,A,D,A) \
	GENERATOR(D,A,D,B) \
	GENERATOR(D,A,D,C) \
	GENERATOR(D,A,D,D) \
	\
	\
	GENERATOR(D,B,A,A) \
	GENERATOR(D,B,A,B) \
	GENERATOR(D,B,A,C) \
	GENERATOR(D,B,A,D) \
	\
	GENERATOR(D,B,B,A) \
	GENERATOR(D,B,B,B) \
	GENERATOR(D,B,B,C) \
	GENERATOR(D,B,B,D) \
	\
	GENERATOR(D,B,C,A) \
	GENERATOR(D,B,C,B) \
	GENERATOR(D,B,C,C) \
	GENERATOR(D,B,C,D) \
	\
	GENERATOR(D,B,D,A) \
	GENERATOR(D,B,D,B) \
	GENERATOR(D,B,D,C) \
	GENERATOR(D,B,D,D) \
	\
	\
	GENERATOR(D,C,A,A) \
	GENERATOR(D,C,A,B) \
	GENERATOR(D,C,A,C) \
	GENERATOR(D,C,A,D) \
	\
	GENERATOR(D,C,B,A) \
	GENERATOR(D,C,B,B) \
	GENERATOR(D,C,B,C) \
	GENERATOR(D,C,B,D) \
	\
	GENERATOR(D,C,C,A) \
	GENERATOR(D,C,C,B) \
	GENERATOR(D,C,C,C) \
	GENERATOR(D,C,C,D) \
	\
	GENERATOR(D,C,D,A) \
	GENERATOR(D,C,D,B) \
	GENERATOR(D,C,D,C) \
	GENERATOR(D,C,D,D) \
	\
	\
	GENERATOR(D,D,A,A) \
	GENERATOR(D,D,A,B) \
	GENERATOR(D,D,A,C) \
	GENERATOR(D,D,A,D) \
	\
	GENERATOR(D,D,B,A) \
	GENERATOR(D,D,B,B) \
	GENERATOR(D,D,B,C) \
	GENERATOR(D,D,B,D) \
	\
	GENERATOR(D,D,C,A) \
	GENERATOR(D,D,C,B) \
	GENERATOR(D,D,C,C) \
	GENERATOR(D,D,C,D) \
	\
	GENERATOR(D,D,D,A) \
	GENERATOR(D,D,D,B) \
	GENERATOR(D,D,D,C) \
	GENERATOR(D,D,D,D) \