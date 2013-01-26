#pragma once
#include <angelscript.h>

namespace Tocs {
namespace Scripting {

class Engine;

class Context
{
	asIScriptContext *ContextPtr;
	Engine &EngineRef;
public:
	Context(Engine &engine);
	~Context(void);

	template <class T>
	T GetReturnValue ()
	{ return *static_cast<T*> (ContextPtr->GetReturnObject ()); 	}

	template <class T>
	void SetArgValue (int index, T value)
	{ ContextPtr->SetArgObject (index,&value); }

	template <class T>
	void SetArgValue (int index, T* value)
	{ ContextPtr->SetArgObject(index,value); }

	asIScriptContext *GetContextPtr () { return ContextPtr; }

	
	void ExecuteCall ();
};

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