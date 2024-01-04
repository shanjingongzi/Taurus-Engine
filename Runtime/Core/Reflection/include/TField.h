#pragma once
#include <string>
#include <unordered_map>
#include <set>
#include <variant>
#include <functional>
#include <span>
#include <memory>
#include "Type.hpp"
#include "MethodPtr.h"
#include "Util.hpp"
class Attr
{
public:
	Attr()noexcept = default;
};

class AttrLess
{
public:
	using is_transparent = int;
	AttrLess()noexcept = default;
};

enum class FieldFlag
{
	Basic = 0b00001,
	Virtual=0b00010,
	Static =0b00100,
	DynamicShared=0b01000,
	DynamicBuffer=0b10000,

	None=0b00000,
	Owned=0b00011,
	UnOwned=0b11100,
    All=0b11111,
};

using Offsetor = std::function<void* (void*)>;
class FieldPtr
{
	using SharedBuffer = std::shared_ptr<void>;
	static constexpr std::size_t BufferSize = std::max(sizeof(Offsetor), sizeof(SharedBuffer));
	using Buffer = std::aligned_storage_t<BufferSize>;
public:
	using Data = std::variant<std::size_t, Offsetor, void*, SharedBuffer, Buffer>;
	Type GetType()
	{
		return type;
	}
public:
	FieldPtr(Type inType,std::size_t forward_offset_value)noexcept:type(inType),data{forward_offset_value}
	{
	}

	FieldPtr(Type inType,Offsetor offsettor)noexcept:type{inType},data{std::move(offsettor)}
	{
	}
	size_t offset() {
		return std::get<size_t>(data);
	}

private:
	Type type;
	Data data;
};

using AttrSet = std::set<Attr>;
struct FieldInfo
{
	FieldInfo()noexcept = default;
    FieldInfo(FieldPtr inFieldPtr,const AttrSet& attrSet):fieldPtr(inFieldPtr){}
	FieldPtr fieldPtr;
	AttrSet attrs;
};

struct MethodInfo
{
	MethodInfo()noexcept = default;
    MethodInfo(const MethodPtr& InMethodPtr, AttrSet InAttrs) :methodptr{ InMethodPtr } {}
	MethodPtr methodptr;
	AttrSet atrrs;
};

struct InheritCastFunctions
{
	Offsetor static_derive_to_base;
	Offsetor static_base_to_derived;
	Offsetor dynamic_base_to_derived;
};

class BaseInfo
{
public:
	BaseInfo() = default;
	BaseInfo(InheritCastFunctions funcs) :func{ std::move(funcs) } {}
	bool IsVirtual()const noexcept {
		return !static_cast<bool>(func.static_derive_to_base);
	}
	void* StaticCast_DerivedToBase(void* ptr)const noexcept 
	{ 
		return func.static_base_to_derived(ptr); 
	}
	void* StaticCast_BaseToDerived(void *ptr)const noexcept
	{
		return func.static_derive_to_base(ptr);
	}
	void* DynamicCast_base_to_derived(void* ptr)const noexcept 
	{
		return func.dynamic_base_to_derived(ptr);
	}
private:
	InheritCastFunctions func;
};

struct TypeInfo {
	size_t size;
	size_t alignment;
	bool is_polymorphic;
	bool is_trivial;
	std::unordered_map<Name, FieldInfo>fieldInfos;
	std::unordered_multimap<Name, MethodInfo>methodInfos;
	std::unordered_map<Type, BaseInfo>baseInfos;
	AttrSet attrs;
};
