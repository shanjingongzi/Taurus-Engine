#pragma once
#include "Type.hpp"
#include <memory>

class ObjectView
{
public:
	constexpr ObjectView()noexcept :ptr{ nullptr } {}
	constexpr ObjectView(Type InType, void* InPtr) : type{ InType }, ptr{ InPtr } {}
	explicit constexpr ObjectView(Type type)noexcept :ObjectView{ type,nullptr } {}
	constexpr void* const& GetPtr()const noexcept { return ptr; }
	constexpr Type GetType()noexcept { return type; }

    template<typename T>
    auto * AsPtr()const noexcept
    {
        assert(type.Is<T>());
        return reinterpret_cast<std::add_pointer_t<T>>(ptr);
    }
    template<typename T>
    constexpr auto As()const noexcept
    {
       assert(ptr);
       auto *ptr=AsPtr<T>();
       if constexpr(std::is_reference_v<T>){
           return std::forward<T>(*ptr);
       }
       else{
           return ptr;
       }
    }
private:
	Type type;
	void* ptr;
};

class SharedObject :public ObjectView
{
public:
	using SharedBuffer = std::shared_ptr<void>;
private:
	SharedBuffer sharedBuffer;
};


using ArgPtrBuffer = void* const*;
class  ArgsView 
{
public:
	constexpr ArgsView() noexcept : buffer{ nullptr } {}
	constexpr ArgsView(ArgPtrBuffer buffer, std::span<const Type> argTypes) noexcept : buffer{ buffer }, argTypes{ argTypes }{}
	constexpr ArgPtrBuffer Buffer() const noexcept { return buffer; }
	constexpr std::span<const Type> Types() const noexcept { return argTypes; }
	constexpr std::span<const Type>& GetParamList() {
		return argTypes;
	}
	constexpr ObjectView operator[](size_t idx)const noexcept
	{
		return { argTypes[idx], buffer[idx] };
	}
private:
	ArgPtrBuffer buffer;
	std::span<const Type> argTypes;
};

template<typename T>
constexpr Type ArgType(const std::remove_const_t<std::remove_reference_t<T>>& arg)noexcept
{
    using U = std::remove_cvref_t<T>;
    if constexpr (std::is_same_v<U, ObjectView> || std::is_same_v<U, SharedObject>) {
        return type_of<T>;
    }
    else {
        return type_of<T>;
    }
}

template<typename T>
constexpr void* ArgPtr(const T& arg)noexcept
{
    if constexpr (std::is_same_v<T, ObjectView> || std::is_same_v<T, SharedObject>) {
        return arg.GetPtr();
    }
    else {
        return const_cast<void*>(static_cast<const void*>(&arg));
    }
}


template<std::size_t N>
class TempArgsView
{
public:
    template<typename ...Args>
    TempArgsView(Args &&...args)noexcept : argTypes{ ArgType<decltype(args)>(args)...}, argptr_buffer{ArgPtr(args)...}
    {
        static_assert(sizeof...(Args) == N);
    }
    operator ArgsView()const&& noexcept { return { argptr_buffer,argTypes }; }
private:
    const Type argTypes[N];
    void* const argptr_buffer[N];
};

template<typename ...Args>
TempArgsView(Args&&...)->TempArgsView<sizeof...(Args)>;
