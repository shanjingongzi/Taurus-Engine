#pragma once
#include <string_view>
#include <TField.h>
#include "IDRegistry.hpp"
#include "MethodPtr.h"
#include "FuncImp.hpp"
#include <memory>
#include <TField.h>
#include <iostream>
#include "TField.h"
#if _MSC_VER
#include <memory_resource>
#else
#include <experimental/memory_resource>
#endif

template<typename ...Params>
ParamList GenerateParamList()noexcept {
	if constexpr (sizeof...(Params) > 0) {
		static_assert(((!std::is_const_v<Params> &&!std::is_volatile_v<Params>)&&...), "paramerter type shouldn't be const.");
		return{ type_of<Params>... };
	}
	else {
		return {};
	}
}

template<typename ArgList>
struct GenerateParamListHelper;

template<typename ...Args>
struct GenerateParamListHelper<TypeList<Args...>>
{
	static ParamList get()noexcept(sizeof...(Args) == 0) {
		return GenerateParamList<Args...>();
	}
};

class TClass
{
public:
    ObjectView MakeShared(Type type, ArgsView args = {});
#ifdef __clang__
    ObjectView MMakeShared(Type type, std::experimental::pmr::memory_resource* rsrc, ArgsView args);
    ObjectView MNew(Type type, std::experimental::pmr::memory_resource* rsrc, ArgsView args);
#else
    ObjectView MMakeShared(Type type, std::pmr::memory_resource* rsrc, ArgsView args);
	ObjectView MNew(Type type, std::pmr::memory_resource* rsrc, ArgsView args);
#endif
	Type Invoke(ObjectView obj, Name method_name, void* result_buffer, ArgsView args, MethodFlag flag);
	ObjectView Var(ObjectView obj, Name field_name, FieldFlag flag);
	template<typename T>
	void RegisterType();
	Type RegisterType(Type type, size_t size, size_t alignment, bool is_polymorphic, bool is_tarivil);
	template<typename T>
	inline void TypeAutoRegister();

	inline Name AddTrivialCopyConstructor(Type type);
	inline Name AddMethod(Type type, Name method_name, MethodInfo methodinfo);
	template<auto func_ptr>
	inline bool AddMethod(Name name, AttrSet attrs = {});
    template<auto field_data>
    bool AddField(Name name,AttrSet={});
    bool AddField(Type type,Name field_name,FieldInfo fieldInfo);
	template<typename T,typename ...Args>
	bool AddConstructor(AttrSet attrs = {});
	template<typename Derived,typename ...Base>
	bool AddBases();
	bool AddBase(Type dervied, Type Base, BaseInfo baseinfo);
	bool Construct(ObjectView obj, ArgsView args);
	template<typename T,typename ...Args>
	inline MethodPtr GenerateConstructorPtr();
	template<typename Func>
	inline MethodPtr GenerateMeberMethodPtr(Func&& func);
    template<auto funcptr>
    MethodPtr GenerateMethodPtr();
    template<auto fieldData,bool NeedRegisterFieldType>
    FieldPtr GenerateFieldPtr();
	inline TypeInfo* GetTypeInfo(Type type);
	template<typename Dervied,typename Base>
	BaseInfo GenerateBaseInfo();
	template<typename Dervied,typename Base>
	InheritCastFunctions inherit_cast_function();
	template<typename From,typename To>
	constexpr auto static_cast_functor()noexcept;
	template<typename Base,typename Derived>
	constexpr auto dynamic_cast_function()noexcept;
public:
	static std::unordered_map<Type,TypeInfo> typeinfos;
	static TypeIDRegistry tregistry;
	static NameIDRegistry nregistry;
#ifdef __clang__
    static std::shared_ptr<std::experimental::pmr::memory_resource>object_resource;
#else
    static std::shared_ptr<std::pmr::memory_resource>object_resource;
#endif
};

template<typename T>
void TClass::RegisterType()
{
	static_assert(!std::is_volatile_v<T>);
	if constexpr (std::is_void_v<T>) {
		return;
	}
	else {
		if constexpr(std::is_const_v<T>) {
			RegisterType<std::remove_const_t<T>>();
		}
		else if constexpr (std::is_reference_v<T>) {
			RegisterType<std::remove_cvref_t<T>>();
		}
		else {
			if (typeinfos.contains(type_of<T>)) {
				return;
			}
			tregistry.Register<T>();
			RegisterType(
				type_of<T>,
				std::is_empty_v<T> ? 0 : sizeof(T),
				alignof(T),
				std::is_polymorphic_v<T>,
				std::is_trivial_v<T>
			);
			TypeAutoRegister<T>();
		}
	}
}

template<typename T>
inline void TClass::TypeAutoRegister()
{
	if (std::is_default_constructible_v<T> && !std::is_trivial_v<T>) {
		AddConstructor<T>();
	}
}

template<typename T,typename ...Args>
inline bool TClass::AddConstructor(AttrSet attrs)
{
	AddMethod(type_of<T>,NameIDRegistry::Meta::ctor,MethodInfo(GenerateConstructorPtr<T,Args...>(),std::move(attrs)));
	return false;
}

template<auto  func_ptr>
inline bool TClass::AddMethod(Name name,AttrSet attrs)
{
	using MemberFuncPtr = decltype(func_ptr);
	using Obj = member_pointer_traits_object<MemberFuncPtr>;
	AddMethod(type_of<Obj>,name,MethodInfo(GenerateMethodPtr<func_ptr>(),std::move(attrs)));
	return false;
}

template<typename Func>
inline MethodPtr TClass::GenerateMeberMethodPtr(Func&& func)
{

	using Traits = WrapFuncTraits<std::decay_t<Func>>;
	using ArgList = typename Traits::ArgList;
	using Return = typename Traits::Return;
	constexpr MethodFlag flag = Traits::is_const ? MethodFlag::Const : MethodFlag::Variable;
	return {
		MemberFunctionCreator(std::forward<Func>(func)),
		flag,
		type_of<Return>,
		GenerateParamListHelper<ArgList>::get()
	};
}

template<auto funcptr>
MethodPtr TClass::GenerateMethodPtr()
{
   using FuncPtr=decltype(funcptr);
   using Traits=FuncTraits<decltype(funcptr)>;
   using ArgList=typename Traits::ArgList;
   using Return=typename Traits::Return;
   constexpr MethodFlag flag=MethodFlag::Variable;
   return {MemberFunctionCreator<funcptr>(),flag,type_of<Return>,GenerateParamListHelper<ArgList>::get()};
}
inline TypeInfo* TClass::GetTypeInfo(Type type)
{
	auto target = typeinfos.find(type);
	if (target == typeinfos.end()) {
		return nullptr;
	}
	return const_cast<TypeInfo*>(&target->second);
}

inline Name TClass::AddMethod(Type type, Name method_name, MethodInfo methodinfo)
{
	auto typeinfo = GetTypeInfo(type);
	if (!typeinfo) {
		assert(false);
		return {};
	}
	auto [begin_iter, end_iter] = typeinfo->methodInfos.equal_range(method_name);
	for (auto iter = begin_iter; iter != end_iter; ++iter) {
		if (iter->second.methodptr.IsDistinguishableWith(methodinfo.methodptr))
		{
		//	return {};
		}
	}
	Name new_method_name = { nregistry.Register(method_name.GetID(),method_name.GetName()),method_name.GetID()};
	typeinfo->methodInfos.emplace(new_method_name, std::move(methodinfo));
	return new_method_name;
}

template<auto field_data>
bool TClass::AddField(Name name,AttrSet attrs)
{
    using FieldData=decltype(field_data);
    if constexpr (std::is_member_object_pointer_v<FieldData>){
        using Obj=member_pointer_traits<FieldData>::Object;
        FieldPtr fieldPtr=GenerateFieldPtr<field_data,true>();
        FieldInfo fieldinfo={fieldPtr,std::move(attrs)};
       return AddField(type_of<Obj>,name,fieldinfo);
    }
}

template<auto field_data,bool NeedRegisterFieldType>
FieldPtr TClass::GenerateFieldPtr()
{
    using FieldData=decltype(field_data);
    if constexpr(std::is_member_object_pointer_v<FieldData>){
        using Traits=member_pointer_traits<FieldData>;
        using Obj=Traits::Object;
        using Value=typename Traits::Value;
        return {type_of<Value>,field_forward_offset_value(field_data)};
    }
}

inline Name TClass::AddTrivialCopyConstructor(Type type)
{
	auto target = typeinfos.find(type);
	if (target == typeinfos.end()) {
		return {};
	}
	auto& typeinfo = target->second;
	MethodPtr methodPtr{ 
		[size = typeinfo.size](void* obj, void*, ArgsView args) {
			memcpy(obj,args[0].GetPtr(),size); 
		},
		MethodFlag::Variable,
		{},
	};
	MethodInfo methodInfo;
	methodInfo.methodptr = methodPtr;
	return AddMethod(type, NameIDRegistry::Meta::ctor, methodInfo);
}

template<typename T,typename ...Args>
inline MethodPtr TClass::GenerateConstructorPtr()
{
      std::function<void(T&,Args...)> func = [](T& obj, Args... args) {
		if (std::is_constructible_v<T, Args...>) {
			new(&obj)T(std::forward<Args>(args)...);
		}
		else if (std::is_aggregate_v<T>) {
			new(&obj)T{ std::forward<Args>(args)... };
		}
		else
		{
			assert(false);
		}
	}; 
	return GenerateMeberMethodPtr(func);
}
template<typename Derived,typename ...Bases>
bool TClass::AddBases()
{
	return (AddBase(type_of<Derived>, type_of<Bases>, GenerateBaseInfo<Derived, Bases>()) &&...);
}
template<typename Dervied,typename Base>
BaseInfo TClass::GenerateBaseInfo()
{
	return inherit_cast_function<Dervied, Base>();
}

template<typename Derived,typename Base>
InheritCastFunctions TClass::inherit_cast_function()
{
	static_assert(std::is_base_of_v<Base, Derived>);
	if constexpr (std::is_polymorphic_v<Derived>) {
		if constexpr (is_virtual_base_of_v<Base, Derived>) {
			return { static_cast_functor<Derived,Base>(),nullptr,dynamic_cast_function<Base,Derived>()};
		}
		else {
			return { static_cast_functor<Derived,Base>(),static_cast_functor<Base,Derived>(),dynamic_cast_function<Base,Derived>() };
		}
	}
	else {
		if constexpr (is_virtual_base_of_v<Base, Derived>) {
			return { static_cast_functor<Derived,Base>(),nullptr,nullptr};
		}
		else {
			return { static_cast_functor<Derived,Base>(),static_cast_functor<Base,Derived>(),nullptr };
		}
	}
}
template<typename From,typename To>
constexpr auto TClass::static_cast_functor()noexcept
{
	static_assert(!is_virtual_base_of_v<From, To>);
	return [](void* obj)noexcept->void* {
		return static_cast<To*>(reinterpret_cast<To*>(obj));
	};
}

template<typename Base,typename Derived>
constexpr auto TClass::dynamic_cast_function()noexcept
{
	if constexpr (std::is_polymorphic_v<Base>) {
		return [](void* obj)->void* {
			return dynamic_cast<Derived*>(reinterpret_cast<Base*>(obj));
		};
	}
	else {
		return static_cast_functor<Base, Derived>();
	}
}
