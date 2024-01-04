#include "MethodPtr.h"

MethodPtr::MethodPtr(Func InFunc, MethodFlag InFlag, Type InResultType, ParamList InParamList)
	:func(InFunc), flag(InFlag), result_type(InResultType), paramList(InParamList)
{

}

bool MethodPtr::IsMatch(std::span<const Type>argTypes)const noexcept
{
	const std::size_t n = paramList.size();
	if (argTypes.size() != n) {
		return false;
	}
	for (std::size_t i = 0; i < n; ++i) {
		if(paramList[i]!=argTypes[i]){
			//return false;
		}
	}
	return true;
}
bool MethodPtr::IsMatch(ArgsView*argsView)const noexcept
{
	auto types = argsView->GetParamList();
	return IsMatch(types);
}

void MethodPtr::Invoke(void* obj, void* result_buffer, ArgsView args)const
{
	func(obj, result_buffer, args);
}

void MethodPtr::Invoke(const void* obj, void* result_buffer, ArgsView args) const {
	assert(IsMatch(args.Types()));
	if (flag == MethodFlag::Variable)
		return;
	func(const_cast<void*>(obj), result_buffer, args);
};

void MethodPtr::Invoke(void* result_buffer, ArgsView args) const {
	assert(IsMatch(args.Types()));
	if (flag != MethodFlag::Static)
		return;
	func(nullptr, result_buffer, args);
};
