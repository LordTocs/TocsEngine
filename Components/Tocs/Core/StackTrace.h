#pragma once
#include <memory>
#include <string>
#include <vector>
namespace Tocs {

class StackTrace
{
public:
	class Symbol
	{
		void *_Address;
		std::string _SymbolName;
		std::string _File;
		unsigned int _Line;
	public:
		friend class SymbolLookup;
		void *Address () const { return _Address; }
		std::string SymbolName () const { return _SymbolName; }
		std::string File () const { return _File; }
		unsigned int Line () const { return _Line; }

		Symbol (void *address);
	};
private:
	std::vector<Symbol> Symbols;
public:

	StackTrace();

	std::string GetPrettyString () const;
	void PrettyPrint () const;

	std::string GetVerboseString () const;
	void VerbosePrint () const;
};

}