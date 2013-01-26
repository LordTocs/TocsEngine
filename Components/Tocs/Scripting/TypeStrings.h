#pragma once
#include <string>
#include <sstream>
#include <typeinfo>
#include <Tocs/Core/Tokenizer.h>
namespace Tocs {
namespace Scripting {

template <class T>
class TypeString
{
public:
	static std::string Get ()
	{
		//MSVC
		Lexing::StringSource source (typeid(T).name ());
		Lexing::Tokenizer tokens(source);
		std::string name;

		while (!tokens.EndOfStream())
		{
			name = tokens.GetToken ();
		}
		name = tokens.GetToken ();
		
		return name;
	}
};

template <class T>
class TypeString <T*>
{
public:
	static std::string Get ()
	{
		return TypeString<T>::Get() + std::string("@");
	}
};

template <>
class TypeString <std::string>
{
public:
	static std::string Get ()
	{
		return "string";
	}
};

template <class T>
std::string GetTypeString ()
{
	return TypeString<T>::Get();
}


template <class T>
std::string GetTypeString(const T& T)
{
	return TypeString<T>::Get ();
}

template <class C, class R>
std::string GetFunctionString (R (C::*Func) (), const std::string name)
{
	std::stringstream ss;
	ss << GetTypeString<R> () << " " << name << " ()";
	return ss.str ();
}

template <class C, class R>
std::string GetFunctionString (R (__cdecl C::*Func) (), const std::string name)
{
	std::stringstream ss;
	ss << GetTypeString<R> () << " " << name << " ()";
	return ss.str ();
}

template <class R>
std::string GetFunctionString (R (*Func) (), const std::string name)
{
	std::stringstream ss;
	ss << GetTypeString<R> () << " " << name << " ()";
	return ss.str ();
}

template <class C, class R, class A0>
std::string GetFunctionString (R (C::*Func) (A0), const std::string name)
{
	std::stringstream ss;
	ss << GetTypeString<R> () << " " << name << " (" << GetTypeString<A0> () << ")";
	return ss.str ();
}

template <class C, class R, class A0>
std::string GetFunctionString (R (__cdecl C::*Func) (A0), const std::string name)
{
	std::stringstream ss;
	ss << GetTypeString<R> () << " " << name << " (" << GetTypeString<A0> () << ")";
	return ss.str ();
}

template <class R, class A0>
std::string GetFunctionString (R (*Func) (A0), const std::string name)
{
	std::stringstream ss;
	ss << GetTypeString<R> () << " " << name << " (" << GetTypeString<A0> () << ")";
	return ss.str ();
}

template <class C, class R, class A0, class A1>
std::string GetFunctionString (R (C::*Func) (A0,A1), const std::string name)
{
	std::stringstream ss;
	ss << GetTypeString<R> () << " " << name << " (" << GetTypeString<A0> () << ", " << GetTypeString<A1> () << ")";
	return ss.str ();
}

template <class R, class A0, class A1>
std::string GetFunctionString (R (*Func) (A0,A1), const std::string name)
{
	std::stringstream ss;
	ss << GetTypeString<R> () << " " << name << " (" << GetTypeString<A0> () << ", " << GetTypeString<A1> () << ")";
	return ss.str ();
}

}}