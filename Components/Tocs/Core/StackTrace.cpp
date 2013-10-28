#include "StackTrace.h"
#include <Windows.h>
#include <DbgHelp.h>
#include "LateStatic.h"
#include <iostream>
#include <sstream>
namespace Tocs {

typedef USHORT (WINAPI *CaptureStackBackTraceType)(__in ULONG, __in ULONG, __out PVOID*, __out_opt PULONG);
   CaptureStackBackTraceType func = (CaptureStackBackTraceType)(GetProcAddress(LoadLibrary(L"kernel32.dll"), "RtlCaptureStackBackTrace"));

class SymbolLookup
{
	bool Inited;
public:
	SymbolLookup ()
	{
		SymSetOptions(SYMOPT_LOAD_LINES);

		Inited = SymInitialize (GetCurrentProcess(),nullptr,true);

		if (!Inited)
		{
			std::cout << "Unable to load symbols for stack trace." << std::endl;
		}
	}

	void LookUp (StackTrace::Symbol &symbol)
	{
		std::stringstream ss;

		DWORD64 addr = reinterpret_cast<DWORD64> (symbol.Address());

		char symbolName[MAX_SYM_NAME + 1];
		char buffer[sizeof(IMAGEHLP_SYMBOL64) + MAX_SYM_NAME*sizeof(TCHAR)] = {0};
		IMAGEHLP_LINE64 line;
		DWORD64 dis64 = 0;
		DWORD dis = 0;
		IMAGEHLP_SYMBOL64 *pSym = NULL;
		BOOL res;

		pSym = (IMAGEHLP_SYMBOL64 *) buffer;
		pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
		pSym->MaxNameLength = MAX_PATH;

		res = SymGetSymFromAddr64(GetCurrentProcess(), addr, &dis64, pSym);
		if (!res)
		{
			/* TODO: call your trace function instead of printf */
			//printf("SymGetSymFromAddr64 fails, error=%ld\n", GetLastError());
		}
		else
		{
			symbol._SymbolName = std::string(pSym->Name);
		}

		memset(&line, 0, sizeof(line));
		line.SizeOfStruct = sizeof(line);
		res = SymGetLineFromAddr64(GetCurrentProcess(), addr, &dis, &line);

		if (!res)
		{
			
		}
		else
		{
			symbol._File = line.FileName;
			symbol._Line = line.LineNumber;
		}

	}
};

static SymbolLookup SymbolFetcher;

StackTrace::Symbol::Symbol (void *addr)
	: _Address (addr), _Line(0)
{
	Tocs::SymbolFetcher.LookUp (*this);
}

StackTrace::StackTrace()
{
	/*STACKFRAME64 frame;
	DWORD machinetype = 
#if WIN64
		IMAGE_FILE_MACHINE_AMD64;
#else
		IMAGE_FILE_MACHINE_I386;
#endif

	HANDLE Process = GetCurrentProcess ();
	HANDLE Thread = GetCurrentThread ();

	CONTEXT context;
	RtlCaptureContext (&context);
	std::memset(&context,0,sizeof(context));*/

	void *callers[62];
	int count = (func)(0,62,callers,nullptr);

	for (int i = 0; i < count; ++i)
	{
		Symbols.push_back (Symbol (callers[i]));
	}
}

std::string StackTrace::GetPrettyString () const
{
	std::stringstream ss;
	for (auto i = Symbols.begin() + 1; i != Symbols.end (); ++i)
	{
		ss << (*i).SymbolName () << "()";

		if (!(*i).File ().empty())
		{
			std::string trimmedfile = (*i).File();
			
			int startindex = trimmedfile.length() - 1;

			for (; startindex > 0; --startindex)
			{
				if (trimmedfile[startindex] == '\\' || trimmedfile[startindex] == '/')
				{
					++startindex;
					break;
				}
			}
			trimmedfile = trimmedfile.substr(startindex);
			ss << " @ "  << trimmedfile << ":" << (*i).Line();
		}

		ss << std::endl;

		if ((*i).SymbolName() == "main")
			break;
	}
	return ss.str();
}
void StackTrace::PrettyPrint () const
{
	std::cout << GetPrettyString () << std::endl;
}

std::string StackTrace::GetVerboseString () const
{
	std::stringstream ss;
	for (auto i = Symbols.begin(); i != Symbols.end (); ++i)
	{
		ss << (*i).SymbolName () << "()";

		if (!(*i).File ().empty())
		{
			ss << " @ " << (*i).File () << ":" << (*i).Line();
		}

		ss << std::endl;

		if ((*i).SymbolName() == "main")
			break;
	}
	return ss.str();
}
void StackTrace::VerbosePrint () const
{
	std::cout << GetVerboseString () << std::endl;
}


}