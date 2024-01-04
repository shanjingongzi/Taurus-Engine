#pragma once
#include <type_traits>
template<typename T>
struct TIsEnumConvertibleToInt
{
	static char(&Resolve(int))[2];
	static char Resole(...);
	enum { Value = sizeof(Resolve(T())) - 1 };
};

template<typename T>
struct TIsEnumClass
{
	enum{Value=TAndValue<__is_enum(T),TNot };
};