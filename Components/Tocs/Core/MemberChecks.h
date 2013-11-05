#pragma once
#include <type_traits>
#include <iostream>

namespace Tocs {

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

namespace HasOStreamOperatorImpl {
  typedef char no;
  typedef char yes[2];

  struct any_t {
    template<typename T> any_t( T const& );
  };

  no operator<<( std::ostream const&, any_t const& );

  yes& test( std::ostream& );
  no test( no );

  template<typename T>
  struct HasOStreamOperator {
    static std::ostream &s;
    static T const &t;
    static bool const Value = sizeof( test(s << t) ) == sizeof( yes );
  };
}

template<typename T>
struct HasOStreamOperator : HasOStreamOperatorImpl::HasOStreamOperator<T> {};

}