#ifndef REF_FUNCTION_H
#define REF_FUNCTION_H
#include <type_traits>
#include <TypeList.hpp>
#include <tuple>

template<typename T> struct FuncTraits;

template<typename T> using FuncTraits_Object = typename FuncTraits<T>::Object;
template<typename T> using FuncTraits_ArgList = typename FuncTraits<T>::ArgList;
template<typename T> using FuncTraits_Return = typename FuncTraits<T>::Return;
template<typename T> using FuncTraits_Signature = typename FuncTraits<T>::Signature;
template<typename T> using FuncTraits_Function = typename FuncTraits<T>::Function;
template<typename T> constexpr bool FuncTraits_is_const = FuncTraits<T>::is_const;
template<typename T> constexpr bool FuncTraits_is_volatile = FuncTraits<T>::is_volatile;
template<typename T> constexpr ReferenceMode FuncTraits_ref = FuncTraits<T>::ref;
template<typename T> constexpr bool FuncTraits_is_noexcept = FuncTraits<T>::is_noexcept;

template<typename Obj, typename Func> struct MemFuncOf;
template<typename Func> struct FuncOf;
template<typename NewFunc> struct FuncExpand;

template<typename Lambda>
constexpr auto DecayLambda(Lambda&& lambda) noexcept;
#endif
#include "RefFunction.inl"