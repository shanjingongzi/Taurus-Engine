#pragma once
#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>
//#define __MEMORY_POOL__ 

namespace TE
{
namespace MEMORY
{

	enum { __ALIGN = 8 };
	enum { __MAX_BYTES = 128 };
	enum { __NFREELISTS = __MAX_BYTES / __ALIGN };

	class __default_alloc_template {
	private:
		static size_t ROUND_UP(size_t bytes) {
			return (((bytes)+__ALIGN - 1) & ~(__ALIGN - 1));
		}

	private:
		union obj {
			union obj* free_list_link;
			char client_data[1];
		};
		static obj* volatile free_list[__NFREELISTS];
		static size_t FREELIST_INDEX(size_t bytes) {
			return (((bytes)+__ALIGN - 1) / __ALIGN - 1);
		}
		static void* refill(size_t n);
		static char* chunk_alloc(size_t size, int& nobjs);
		static char* start_free;
		static char* end_free;
		static size_t heap_size;
	public:
		static void* allocate(size_t n)
		{
			obj* volatile* my_free_list;
			obj* result;
			if (n > (size_t)__MAX_BYTES) {
				return(malloc(n));
			}
			my_free_list = free_list + FREELIST_INDEX(n);
			result = *my_free_list;
			if (result == 0) {
				void* r = refill(ROUND_UP(n));
				return r;
			}
			*my_free_list = result->free_list_link;
			return (result);
		}
		static void deallocate(void* p, size_t n)
		{
			obj* q = (obj*)p;
			obj* volatile* my_free_list;
			if (n > (size_t)__MAX_BYTES) {
				free(p);
				return;
			}
			my_free_list = free_list + FREELIST_INDEX(n);
			q->free_list_link = *my_free_list;
			*my_free_list = q;
		}
		static void reallocate(void* p, size_t old_sz, size_t new_sz)
		{

		}
	};
	
   template <typename T>
   class Allocator
   {
   public:
	   typedef T value_type;
	   typedef T* pointer;
	   typedef const T* const_pointer;
	   typedef T& reference;
	   typedef const T& const_reference;
	   typedef size_t size_type;
	   typedef ptrdiff_t differnce_type;
	   static T* allocate(size_t n)
	   {
#ifdef __MEMORY_POOL__
		   if (sizeof(T)*n > __MAX_BYTES) {
			   return (T*)::operator new (n * sizeof(T));
		   }
		   return (T*)__default_alloc_template::allocate(n*sizeof(T));
#else
		   return new T[n];
#endif
	   }
	   static T* allocate(void)
	   {
		   return nullptr;
	   }
	   static void deallocate(T* p, size_t n)
	   {
#ifdef __MEMORY_POOL__
#else
		   delete[] p;
#endif
	   }
	   static void deallocate(T* p)
	   {
#ifdef __MEMORY_POOL__
#else
		   delete[] p;
#endif
	   }

   };

    
}
}
