#ifndef TE_ALGOBASE_H
#define TE_ALGOBASE_H
#include <string.h>

namespace TE
{
	template <typename  InputIter, typename OutputIter>
	inline OutputIter copy(InputIter first, InputIter last, OutputIter result)
	{
		for (; first != last; ++result, ++first) {
			*result = *first;
		}
		return result;
	}

	template<typename ForwardIter,typename Tp>
	inline void fill(ForwardIter first, ForwardIter last, const Tp& __x) {
		for (; first != last; ++first) {
			*first = __x;
		}
	}

	template<typename ForwardIter,typename Size,typename Tp>
	inline ForwardIter fill_n(ForwardIter first, Size n, const Tp& __x) {
		for (; n > 0; --n, ++first) {
			*first = __x;
		}
		return first;
	}

	inline void fill(unsigned char* first, unsigned char* last, const unsigned char& __c)
	{
		unsigned char __tmp = __c;
		memset(first, static_cast<unsigned char>(__tmp), last - first);
	}
	inline void fill(signed char* first, signed char* last, const signed char& __c)
	{
		signed char __tmp = __c;
		memset(first, static_cast<signed char>(__tmp), last - first);
	}
	inline void fill(char* first, char* last, const char& __c)
	{
		char __tmp = __c;
		memset(first, static_cast<char>(__tmp), last - first);
	}
}
#endif
