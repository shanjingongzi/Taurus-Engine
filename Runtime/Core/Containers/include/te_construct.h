#ifndef TE_CONSTRUCT_H
#define TE_CONSTRUCT_H
#include "te_type_trais.h"
namespace TE 
{

	template<typename _T1,typename _T2>
	inline void Construct(_T1* __p, const _T2& __value) 
	{
		new ((void*)__p) _T2(__value);
	}

	template<typename T1>
	inline void Construct(T1* __p) {
		new((void*)__p)T1();
	}

	template <class _Tp>
	inline void _Destroy(_Tp* __pointer) {
		__pointer->~_Tp();
	}

	template <class _ForwardIterator>
	void __destroy_aux(_ForwardIterator __first, _ForwardIterator __last, __false_type)
	{
		for (; __first != __last; ++__first)
			destroy(&*__first);
	}

	template <class _ForwardIterator>
	inline void __destroy_aux(_ForwardIterator, _ForwardIterator, __true_type) {}

	template <class _ForwardIterator, class _Tp>
	inline void
		__destroy(_ForwardIterator __first, _ForwardIterator __last, _Tp*)
	{
		typedef typename __type_traits<_Tp>::has_trivial_destructor _Trivial_destructor;
		__destroy_aux(__first, __last, _Trivial_destructor());
	}

	template <class _ForwardIterator>
	inline void _Destroy(_ForwardIterator __first, _ForwardIterator __last) {
		__destroy(__first, __last, __VALUE_TYPE(__first));
	}


	template <class _Tp>
	inline void destroy(_Tp* __pointer) {
		_Destroy(__pointer);
	}

	template <class _ForwardIterator>
	inline void destroy(_ForwardIterator __first, _ForwardIterator __last) {
		_Destroy(__first, __last);
	}
}

#endif
