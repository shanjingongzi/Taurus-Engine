#pragma once
#include <RefFunction.hpp>
#include "Util.hpp"

template<typename F>
struct WrapFuncTraits;

template<typename Func,typename  Obj>
struct WrapFuncTraits<Func Obj::*> :FuncTraits<Func Obj::*>
{
private:
    using Traits = FuncTraits<Func>;
public:
    using Object = Obj;
    using ArgList = typename Traits::ArgList;
    using Return = typename Traits::Return;
    static constexpr bool is_const = Traits::is_const;

};

template<typename F>
struct WrapFuncTraits
{
private:
    using Traits = FuncTraits<F>;
    using ObjectArgList = typename Traits::ArgList;
    static_assert(!IsEmpty_v<ObjectArgList>);
    using CVObjRef = Front_t<ObjectArgList>;
    using CVObj = std::remove_reference_t<CVObjRef>;
public:
    using ArgList = PopFront_t<ObjectArgList>;
    using Object = std::remove_cv_t<CVObj>;
    using Return = typename Traits::Return;
    static constexpr bool is_const = std::is_const_v<CVObj>;
    static_assert(is_const || !std::is_rvalue_reference_v<CVObjRef>);
};



template<typename ArgList>
struct FunctionCall;

template<typename ...Args>
struct FunctionCall<TypeList<Args...>>
{
    template<typename Obj, typename Func, typename MaybeConstVoidPtr, std::size_t... Ns>
    static  decltype(auto) run(MaybeConstVoidPtr ptr, Func&& func, ArgsView args, std::index_sequence<Ns...>)
    {
        if constexpr (std::is_member_function_pointer_v<Func>)
        {
			return (buffer_as<Obj>(ptr).*func)(auto_get_arg<Args>(args[Ns])...);
        }
        return std::forward<Func>(func)(buffer_as<Obj>(ptr),auto_get_arg<Args>(args[Ns])...);
    }

    template<typename Obj, auto func_ptr, typename MaybeConstVoidPtr, std::size_t... Ns>
    static constexpr decltype(auto) run(MaybeConstVoidPtr ptr, ArgsView args, std::index_sequence<Ns...>)
    {
        return (buffer_as<Obj>(ptr).*func_ptr)(auto_get_arg<Args>(args[Ns])...);
    }

    template<auto func_ptr, std::size_t... Ns>
    static constexpr decltype(auto) run(ArgsView args, std::index_sequence<Ns...>)
    {
        return func_ptr(auto_get_arg<Args>(args[Ns])...);
    }

    template<typename Func, std::size_t... Ns>
    static constexpr decltype(auto) run(Func&& func, ArgsView args, std::index_sequence<Ns...>) {
        return std::forward<Func>(func)(auto_get_arg<Args>(args[Ns])...);
    }

    template<typename T>
    static decltype(auto) auto_get_arg(ObjectView obj) {
        if constexpr (std::is_same_v<T, ObjectView>) {
            return obj;
        }
        else {
            return obj.As<T>();
        }
    }
};

template<typename Func>
auto MemberFunctionCreator(Func &&func)
{
    using Traits = WrapFuncTraits<std::decay_t<Func>>;
    using Return = typename Traits::Return;
    using Obj = typename Traits::Object;
    using ArgList = typename Traits::ArgList;
    using IndexSeq = std::make_index_sequence<Length_v<ArgList>>;
    auto wrapped_function = [f = std::forward<Func>(func)](void* obj, void* result_buffer, ArgsView args)mutable{
        if constexpr (!std::is_void_v<Return>) {
            using NonCVReturn = std::remove_cv_t<Return>;
            NonCVReturn rst = FunctionCall<ArgList>::template run<Obj>(obj, std::forward<Func>(f), args, IndexSeq{});
            if (result_buffer) {
                if constexpr (std::is_reference_v<Return>) {
                    buffer_as<std::add_pointer_t<Return>>(result_buffer) = &rst;
                }
                else {
                    new (result_buffer)NonCVReturn{ std::move(rst) };
                }
            }
        }
        else {
            FunctionCall<ArgList>::template run<Obj>(obj, std::forward<Func>(f), args, IndexSeq{});
        }
    };
    return wrapped_function;
}

template<auto func_ptr>
constexpr auto MemberFunctionCreator()noexcept
{
    using FuncPtr=decltype(func_ptr);
    static_assert(std::is_member_function_pointer_v<FuncPtr>);
    using Traits=FuncTraits<FuncPtr>;
    using Obj=typename Traits::Object;
    using Return=typename Traits::Return;
    using ArgList=typename Traits::ArgList;
    using IndexSeq=std::make_index_sequence<Length_v<ArgList>>;
   constexpr auto wrapped_function=[](void *obj,void *result_buffer,ArgsView args){
       FunctionCall<ArgList>::template run<Obj,func_ptr>(obj,args,IndexSeq{});
   };
   return wrapped_function;
}
