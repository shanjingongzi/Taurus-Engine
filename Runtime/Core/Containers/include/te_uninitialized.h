#pragma once
#ifndef TE_UNINITIALIZED_H
#define TE_UNINITIALIZED_H
#include "te_type_trais.h"
#include "te_algobase.h"
#include "te_iterator_base.h"
#include "te_construct.h"
#include <utility>
#include <memory>
namespace TE 
{
	template<typename InputIter, typename ForwardIter>
	inline ForwardIter __uninitialized_copy_aux(InputIter first, InputIter last, ForwardIter result, __true_type)
	{
		return copy(first, last, result);
	}

	template <typename InputIter,typename ForwardIter>
	ForwardIter __uninitialized_copy_aux(InputIter first, InputIter last, ForwardIter result, __false_type)
	{
		ForwardIter cur = result;
		for (; first != last; ++first, ++cur) {
			Construct(&*cur, *first);
		}
		return cur;
	}

	template <typename InputIter,typename ForwardIter,typename Tp>
	ForwardIter __uninitial_copy(InputIter first, InputIter last, ForwardIter result,Tp*)
	{
#ifdef   _MSC_VER
		typedef  __type_traits<Tp>::is_POD_type _Is_POD;
#else
		typedef typename  __type_traits<Tp>::is_POD_type _Is_POD;
#endif
		return __uninitialized_copy_aux(first, last, result, _Is_POD());
	}

	template<typename InputIter,typename ForwardIter>
	inline ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result)
	{
		return __uninitial_copy(first, last, result,__VALUE_TYPE(result));
	}

	//inline char* uninitialized_copy(const char* first, const char* last, char* result)
	//{
	//	memmove(result, first, last - first);
	//	return result;
	//	return result + (last - first);
	//}

	//inline wchar_t* uninitialized_copy(const wchar_t* first, const wchar_t* last, wchar_t* result)
	//{
	//	memmove(result, first, last - first);
	//	return result + (last - first);
	//}

	template<typename InputIter,typename Size,typename ForwardIter>
	inline std::pair<InputIter, ForwardIter>__uninitialized_copy_n(InputIter first, Size count, ForwardIter result, input_iterator_tag)
	{
		ForwardIter cur = result;
		for (; count > 0; --count, ++first, ++cur) {
			Construct(&*cur, first);
		}
		return std::make_pair<InputIter, ForwardIter>(first, cur);
	}

	template<typename RandomAccessIter,typename Size,typename ForwardIter>
	inline std::pair<RandomAccessIter, ForwardIter>__uninitialized_copy_n(RandomAccessIter first, Size count, ForwardIter result, random_access_iterator_tag) {
		RandomAccessIter last = first + count;
        return std::pair<RandomAccessIter, ForwardIter>(last, uninitialized_copy(first, last, result));
	}

	template<typename InputIter,typename Size,typename ForwardIter>
	inline std::pair<InputIter, ForwardIter>__uninitialized_copy_n(InputIter first, Size count, ForwardIter result)
	{
		return __uninitialized_copy_n(first, count, result, __ITERATOR_CATEGORY(first));
	}

	template<typename InputIter,typename Size,typename ForwardIter>
	inline std::pair<InputIter, ForwardIter>uninitialized_copy_n(InputIter first, Size count, ForwardIter result)
	{
		return __uninitialize_copy_n(first, count, result, __ITERATOR_CATEGORY(first));
	}

	template<typename ForwardIter,typename Tp>
	inline void __uninitialized_fill_aux(ForwardIter first, ForwardIter last, const Tp& __x, __true_type)
	{
		ForwardIter cur = first;
		for (; cur != last; ++cur) {
			*cur = __x;
		}
	}

	template<typename ForwardIter,typename Tp>
	inline void __uninitialized_fill_aux(ForwardIter first, ForwardIter last, const Tp& __x, __false_type)
	{
		ForwardIter cur = first;
		for (; cur != last; ++cur) {
			Construct(&*cur, __x);
		}
	}

	template <class _ForwardIter, class _Tp>
	inline void __uninitialized_fill(_ForwardIter __first, _ForwardIter __last, const _Tp& __x, _Tp*)
	{
		__uninitialized_fill(__first, __last, __x, __VALUE_TYPE(__first));
	}

	template<typename ForwardIter,typename Tp>
	inline void uninitialized_fill(ForwardIter first, ForwardIter last, const Tp& __x)
	{
#ifdef _MSC_VER
		typedef  __type_traits<Tp>::is_POD_type _Is_POD;
#else
		typedef typename  __type_traits<Tp>::is_POD_type _Is_POD;
#endif
        __uninitial_fill_aux(first,last,__x,__VALUE_TYPE(first));
	}

	

	template <typename ForwardIter,typename Size,typename Tp>
	inline ForwardIter __uninitialized_fill_n_aux(ForwardIter first, Size n, const Tp& __x, __true_type)
	{
		return fill_n(first, n, __x);
	}

	template<typename ForwardIter,typename Size,typename Tp>
	inline ForwardIter __uninitialized_fill_n_aux(ForwardIter first, Size n, const Tp& __x, __false_type)
	{
		for (; n > 0; --n, ++first) {
			Construct(&*first, __x);
		}
		return first;
	}

	template<typename ForwardIter,typename Size,typename Tp >
	inline ForwardIter __uninitialized_fill_n(ForwardIter first, Size count, const Tp& __x,Tp*) {
#ifdef _MSC_VER
		typedef  __type_traits<Tp>::is_POD_type Is_POD_type;
#else
		typedef typename  __type_traits<Tp>::is_POD_type Is_POD_type;
#endif
		return __uninitialized_fill_n_aux(first, count, __x, Is_POD_type());
	}

	template <class _ForwardIter, class _Size, class _Tp>
	inline _ForwardIter
		uninitialized_fill_n(_ForwardIter __first, _Size __n, const _Tp& __x)
	{
		return __uninitialized_fill_n(__first, __n, __x, value_type(__first));
	}

	template<typename InputIter1,typename InputIter2,typename ForwardIter>
	inline ForwardIter __uninitialized_copy_copy(InputIter1 first1, InputIter1 last1,
												 InputIter2 first2, InputIter2 last2,
												 ForwardIter result)
	{
		ForwardIter mid = uninitialized_copy(first1, last1, mid);
		return uninitialized_copy(first2, last2, mid);
	}

	template<typename ForwardIter,typename Tp,typename InputIter>
	inline ForwardIter __uninitialized_fill_copy(ForwardIter result, ForwardIter mid, const Tp& __x, InputIter first, InputIter last)
	{
		uninitialized_copy(result, mid, __x);
		return uninitialized_copy(first, last, mid);
	}

	template <class _InputIter, class _ForwardIter, class _Tp>
	inline void
		__uninitialized_copy_fill(_InputIter __first1, _InputIter __last1,
			_ForwardIter __first2, _ForwardIter __last2,
			const _Tp& __x)
	{
		_ForwardIter __mid2 = uninitialized_copy(__first1, __last1, __first2);
	    uninitialized_fill(__mid2, __last2, __x);
	}
}

#endif
