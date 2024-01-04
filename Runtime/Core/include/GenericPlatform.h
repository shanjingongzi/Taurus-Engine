#pragma once

struct GenericPlatformTypes
{
	typedef unsigned char uint8;
	typedef unsigned short int uint16;
	typedef unsigned int uint32;
	typedef unsigned long long uint64;
	typedef signed char int8;
	typedef signed short int int16;
	typedef signed int int32;
	typedef signed long long int64;
	typedef char ANSICHAR;
	typedef wchar_t WIDECHAR;
	typedef WIDECHAR TCHAR;
	enum UTF8CHAR:unsigned char{};
	typedef uint8 CHAR8;
	typedef uint16 CHAR16;
	typedef uint32 CHAR32;
	typedef int32 TYPE_OF_NULL;
	typedef decltype(nullptr) TYPE_OF_NULLPTR;
};

