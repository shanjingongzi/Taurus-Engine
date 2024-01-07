#pragma once
#include <string_view>
#include <exception>
#define DO_CHECK 1
#if DO_CHECK
#ifndef checkCode
	#define CheckCode(Code) do{Code;}while(false);
#endif
#ifndef verify
#define verify(expr) CHECK_IMPL(expr)
#endif
#ifndef check
#define check(expr) CHECK_IMPL(expr)
#endif
#endif
#define CHECK_IMPL(expr) \
{\
	if(!(expr)){\
		throw __FILE__###expr;\
	}\
}\
