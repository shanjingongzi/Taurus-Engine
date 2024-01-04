#pragma once
#include <memory>
#include <vector>
#include "Allocater.hpp"
#include "te_uninitialized.h"
#include "te_construct.h"
#include <assert.h>
#define FORCEINLINE inline 
#define ASSERT(value) assert((value))
using Allocator = TE::MEMORY::Allocator<double>;
template <typename T,typename InAllocatorType=TE::MEMORY::Allocator<T>>
class Array 
{
public:
	typedef typename InAllocatorType::size_type SizeType;
	typedef T Element;
	typedef InAllocatorType Allocator;
	typedef T value_type;
	typedef value_type* pointer;
	using iterator=value_type*;
	typedef value_type& reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	using const_iterator = const value_type*;
	
	FORCEINLINE Array() :	start(0),finish(0),end_of_storage(0)
	{
		
	}

	FORCEINLINE explicit Array(size_type n)
	{
		fill_initialize(n, T());
	}
	
	FORCEINLINE Array(int n, const T& value)
	{
		fill_initialize(n, value);
	}

	FORCEINLINE Array(long n, const T& value)
	{
		fill_initialize(n, value);
	}

	Array(const Array<T>& other)
	{
		if (other.size() == 0) {
			start = nullptr;
			finish = nullptr;
			end_of_storage = nullptr;
			return;
		}
		fill_initialized(other.size(),other.begin(), other.end());
	}

	~Array()
	{
		Allocator::deallocate(start);
	}
	
	FORCEINLINE void insert_aux(iterator position, const T& value)
	{
		if (finish != end_of_storage) {
			TE::Construct(finish, *(finish - 1));
			++finish;
			TE::copy_backward(position, finish - 2, finish - 1);
			T x_copy = value;
			*position = value;
		}
		else {
			const size_type old_size = size();
			const size_type len = old_size !=0 ? old_size * 2 : 1;
			iterator new_start = Allocator::allocate(len);
			iterator new_finish = new_start;
			new_finish=TE::uninitialized_copy(start, position, new_start);
			TE::Construct(new_finish, value);
			++new_finish;
			new_finish = TE::uninitialized_copy(position, finish, new_finish);
			start = new_start;
			finish = new_finish;
			end_of_storage = new_start+len;
		}

	}

public:
	FORCEINLINE const_iterator begin()const {
		return start;
	}
	FORCEINLINE iterator begin() 
	{
		return start;
	}

	FORCEINLINE const_iterator end()const
	{
		return finish;
	}

	FORCEINLINE iterator end() 
	{
		return finish;
	}

	FORCEINLINE size_type size()const
	{
		return size_type(end() - begin());
	}

	FORCEINLINE void resize(size_type new_size,const T &x)
	{
		if (new_size < size()) {
			erase(begin() + new_size, end());
		}
		else {
			//insert(end(), new_size - size(),x);
		}
	}

	FORCEINLINE void resize(size_type new_size) 
	{
		return resize(new_size, T());
	}

	FORCEINLINE void clear() 
	{
		erase(begin(), end());
	}

	FORCEINLINE size_type capacity()
	{
		return end_of_storage - begin();
	}

	FORCEINLINE bool Empty()
	{
		return begin() == end();
	}

	FORCEINLINE reference operator[](size_type n) 
	{
		return *(begin() + n);
	}

	FORCEINLINE value_type operator[](size_type n)const
	{
		return *(begin() + n);
	}

	FORCEINLINE reference front() {
		return *begin();
	}

	FORCEINLINE reference back()
	{
		return *end_of_storage;
	}

	FORCEINLINE void push_back(const T& x) 
	{
		if (finish != end_of_storage) {
			TE::Construct(finish, x);
			++finish;
		}
		else {
			insert_aux(end(), x);
		}
	}
	
	FORCEINLINE iterator insert(const_iterator position, value_type&& _x) 
	{
		return insert_aux(position, std::move(_x));
	}

	FORCEINLINE iterator insert(const_iterator position, const_iterator first, const_iterator last)
	{
		size_type n = last - first;
		if (n < end_of_storage - finish) {
			finish=TE::copy_backward(position, finish, finish + n);
		TE::uninitialized_copy(first, last, position);
		}
		else {
			
		}

	}

	iterator erase(iterator first, iterator last) {
		iterator i = TE::copy(last, finish, first);
	//	TE::destroy(i, finish);
		finish = finish - (last - first);
		return first;
	}
	iterator erase(iterator position)
	{
		if (position - 1 != end()) {
			std::copy(position + 1, finish, position);
			--finish;
			TE::destroy(finish);
			return position;
		}
	}
	
	size_t Emplace(const T &val)
	{
		push_back(val);
		return size() - 1;
	}

	size_t AddDefaulted(size_t n=1)
	{
		auto oldSize = size();
		for (int i = 0; i < n; --n) {
			push_back(T());
		}
		return oldSize;
	}


	void Push(const T&val)
	{
	}

	T Pop() 
	{
		return back();
	}

	size_t Num()
	{
		return size();
	}

	bool empty()const
	{
		return begin() == end();
	}

protected:

	FORCEINLINE void fill_initialize(size_type n, const T& value)
	{
		start = allocate_and_fill(n, value);
		finish = start + n;
		end_of_storage = finish;
	}

	FORCEINLINE iterator allocate_and_fill(size_type n, const T& x)
	{
		iterator result = Allocator::allocate(n);
		TE::uninitialized_fill_n(result, n, x);
		return result;
	}

	FORCEINLINE iterator fill_initialized(size_type n, const_iterator first, const_iterator last)
	{
		start = Allocator::allocate(n);
		finish=TE::uninitialized_copy(first, last, start);
		end_of_storage = finish;
		return finish;
	}
	iterator start;
	iterator finish;
	iterator end_of_storage;
};
