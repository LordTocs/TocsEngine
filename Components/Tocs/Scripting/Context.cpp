#include "Context.h"
#include "Engine.h"
#include <iostream>
using namespace std;

namespace Tocs {
namespace Scripting {


Context::Context(Engine &engine)
	: EngineRef(engine),
	ContextPtr (engine.GetEnginePtr ()->CreateContext ())
{

}


Context::~Context(void)
{
}

void Context::ExecuteCall ()
{
	int r = ContextPtr->Execute();
	if (r != asEXECUTION_FINISHED)
	{
		if (r == asEXECUTION_EXCEPTION)
		{
			cout << "Exception: " << ContextPtr->GetExceptionString () << endl;
			cout << "\tin ("<< ContextPtr->GetExceptionLineNumber() <<"): " << ContextPtr->GetExceptionFunction ()->GetDeclaration() << endl;
		}
	}
}


/*
template <>
void Context::SetArgValue (int index, const char &value)
{ ContextPtr->SetArgByte (index,value); }
template <>
void Context::SetArgValue (int index, const unsigned char &value)
{ ContextPtr->SetArgByte (index,value); }

template <>
void Context::SetArgValue (int index, const short &value)
{ ContextPtr->SetArgWord (index,value); }
template <>
void Context::SetArgValue (int index, const unsigned short &value)
{ ContextPtr->SetArgWord (index,value); }

template <>
void Context::SetArgValue (int index, const int &value)
{ ContextPtr->SetArgDWord (index,value); }
template <>
void Context::SetArgValue (int index, const unsigned int &value)
{ ContextPtr->SetArgDWord (index,value); }

template <>
void Context::SetArgValue (int index, const long long &value)
{ ContextPtr->SetArgQWord (index,value); }
template <>
void Context::SetArgValue (int index, const unsigned long long &value)
{ ContextPtr->SetArgQWord (index,value); }

template <>
void Context::SetArgValue (int index, const float &value)
{ ContextPtr->SetArgFloat (index,value); }
template <>
void Context::SetArgValue (int index, const double &value)
{ ContextPtr->SetArgDouble (index,value); }

template <>
void Context::SetArgValue (int index, const std::string &value)
{ ContextPtr->SetArgObject (index,const_cast<void*>(static_cast<const void*>(&value))); }


///////////////////////////////////////////////////

template <>
char Context::GetReturnValue<char> ()
{ return ContextPtr->GetReturnByte (); }
template <>
unsigned char Context::GetReturnValue<unsigned char> ()
{ return ContextPtr->GetReturnByte (); }

template <>
short Context::GetReturnValue<short> ()
{ return ContextPtr->GetReturnWord (); }
template <>
unsigned short Context::GetReturnValue<unsigned short> ()
{ return ContextPtr->GetReturnWord (); }

template <>
int Context::GetReturnValue<int> ()
{ return ContextPtr->GetReturnDWord (); }
template <>
unsigned int Context::GetReturnValue<unsigned int> ()
{ return ContextPtr->GetReturnDWord (); }

template <>
long long Context::GetReturnValue<long long> ()
{ return ContextPtr->GetReturnQWord (); }
template <>
unsigned long long Context::GetReturnValue<unsigned long long> ()
{ return ContextPtr->GetReturnQWord (); }

template <>
float Context::GetReturnValue<float> ()
{ return ContextPtr->GetReturnFloat (); }
template <>
double Context::GetReturnValue<double> ()
{ return ContextPtr->GetReturnDouble (); }

*/
}}