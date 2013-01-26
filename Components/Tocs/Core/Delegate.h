#pragma once

namespace Tocs 
{
	template <typename TSignature> class Delegate;
}
#define TOCS_DELEGATE_PREFERRED_SYNTAX
#ifdef _MSC_VER
#define TOCS_DELEGATE_CALLTYPE __fastcall
#else
#define TOCS_DELEGATE_CALLTYPE
#endif

#include "DelegateList.h"

#undef TOCS_DELEGATE_CALLTYPE