#pragma once
#include "Platform.h"
#include <type_traits>

template<bool>struct TEnumAsByte_EnumClass {
	struct Value {};
};
template<>struct TEnumAsByte_EnumClass<true> {
	struct Value {};
};
template<>struct TEnumAsByte_EnumClass<false> 
{
	struct Value {};
};



template<typename TEnum>
class TEnumAsByte
{
//	typedef TEnumAsByte_EnumClass<std::is_enum_v<TEnum>>::Value Check;
public:
	typedef TEnum EnumType;
	TEnumAsByte() = default;
	TEnumAsByte(const TEnumAsByte&) = default;
	TEnumAsByte& operator=(const TEnumAsByte&) = default;
	inline TEnumAsByte(TEnum value) :value{ value } {}
	explicit TEnumAsByte(int32 inValue) :value(static_cast<uint8>(inValue)) {}
	explicit inline TEnumAsByte(uint8 value) : value{ value } {}
public:
	bool operator==(TEnum inValue)const {
		return static_cast<TEnum>(value) == inValue;
	}
	bool operator==(TEnumAsByte inValue)const
	{
		return value == inValue.value;
	}
	operator TEnum()const
	{
		return (TEnum)value;
	}
	TEnum GetValue()const {
		return (TEnum)value;
	}
	uint8 GetInValue()const
	{
		return value;
	}

private:
	uint8 value;
};