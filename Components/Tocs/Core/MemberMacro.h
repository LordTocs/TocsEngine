#pragma once
#include <type_traits>

#define GEN_MEMBER_CHECKER(MEMBER) \
	template <class T>\
	class Has_##MEMBER\
	{\
		Has_##MEMBER();\
		Has_##MEMBER(const Has_##MEMBER &);\
		\
		template <class C, C>\
		class CheckStruct;\
		\
		template <class>\
		static char Check (...);\
		template <class C>\
		static int  Check (CheckStruct <decltype(&C::MEMBER),&C::MEMBER> *);\
	public:\
		static const bool Value = (sizeof(int) == sizeof(Check<T>(0)));\
	};

