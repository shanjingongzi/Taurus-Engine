#pragma once

#include <GenericPlatform.h>
#include "sal.h"
#include "AssertionMacros.h"
#if defined(__clang__)
#include "ClangPlatform.h"
#else

#endif

#define VARARGS        __cdecl
#define CDECL          __cdecl
#define STDCALL        __stdcall
#define FORCEINLINE    __forceinline
#define FORCENOINLINE  __declspec(noinline)
#define FUNCTION_NON_NULL_RETURN_START _Ret_notnull_

#define DECLARE_UINT64(X) X


struct WindowsPlatformTypes :public GenericPlatformTypes
{
#ifdef _WIN64
	typedef unsigned __int64 SIZE_T;
	typedef __int64 SSIZE_T;
#else
	typedef unsigned long SIZE_T;
	typedef long SSIZE_T;
#endif
#if USE_UT7_TCHARS
	typedef UTF8CHAR TCHAR;
#endif
};

typedef WindowsPlatformTypes PlatformTypes;

#define PLATFORM_DESKTOP 1
#if defined(_WIN64)
#define PLATFORM_64BITS 1
#else
#define PLATFORM_64BITS 0
#endif
