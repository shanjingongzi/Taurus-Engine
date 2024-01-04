#ifndef METHOD_PTR_H
#define METHOD_PTR_H
#include<vector>
#include <functional>
#include <span>
#include "Type.hpp"
#include "Object.hpp"

enum class MethodFlag
{
	Variable=0b001,
	Const=0b010,
	Static =0b100,

	None=0b000,
	Member=0b011,
	Priority=0b101,
	All=0b111
};

using ParamList = std::vector<Type>;

class MethodPtr
{
public:
	using Func = std::function<void(void*, void*, ArgsView)>;
	MethodPtr() = default;
	MethodPtr(Func func, MethodFlag flag, Type result_type = type_of<void>, ParamList = {});
	MethodFlag GetMethodFlag()const noexcept { return flag; }
	const Type& GetResultType()const noexcept {return result_type;}
	const ParamList& GetParamList()const noexcept { return paramList; }
	bool IsDistinguishableWith(const MethodPtr& rhs)const noexcept { return flag != rhs.GetMethodFlag() || paramList != rhs.paramList; }
	bool IsMatch(const std::span<const Type>argTypes)const noexcept;
	bool IsMatch(ArgsView*)const noexcept;
	void Invoke(void* obj, void* result_buffer, ArgsView args)const;
	void Invoke(const void* obj, void* result_buffer, ArgsView args)const;
	void Invoke(void* result_buffer, ArgsView args)const;
private:
	MethodFlag flag;   
	Func func;
	Type result_type;
	ParamList paramList;
};

#endif
