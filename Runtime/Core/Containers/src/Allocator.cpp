#include "Allocater.hpp"
namespace TE
{
	namespace MEMORY
	{
		char* __default_alloc_template::start_free = 0;
		char* __default_alloc_template::end_free = 0;
		size_t  __default_alloc_template::heap_size = 0;
		__default_alloc_template::obj* volatile
			__default_alloc_template::free_list[__NFREELISTS] =
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

		void* __default_alloc_template::refill(size_t n)
		{
			int nobjs = 20;
			char* chunk = chunk_alloc(n, nobjs);
			obj* volatile* my_free_list;
			obj* result;
			obj* current_obj, * next_obj;
			if (nobjs == 1) {
				return chunk;
			}
			my_free_list = free_list + FREELIST_INDEX(n);
			result = (obj*)chunk;
			*my_free_list = next_obj = (obj*)(chunk + n);
			for (int i = 1;; ++i) {
				current_obj = next_obj;
				next_obj = (obj*)((char*)next_obj + n);
				if (nobjs - 1 == i) {
					current_obj->free_list_link = nullptr;
					break;
				}
				else {
					current_obj->free_list_link = next_obj;
				}
			}
			return (result);
		}

		char* __default_alloc_template::chunk_alloc(size_t size, int& nobjs)
		{
			char* result;
			size_t total_bytes = size * nobjs;
			size_t bytes_left = end_free - start_free;
			if (bytes_left > total_bytes) {
				result = start_free;
				start_free += total_bytes;
				return result;
			}
			else if (bytes_left >= size) {
				nobjs = bytes_left / size;
				result = start_free;
				start_free += nobjs * size;
				return result;
			}
			else {
				size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
				if (bytes_left > 0) {
					obj* volatile* my_free_list = free_list + FREELIST_INDEX(total_bytes);
					((obj*)start_free)->free_list_link = *my_free_list;
					*my_free_list = (obj*)start_free;
				}
				start_free = (char*)malloc(bytes_to_get);
				if (start_free == 0) {
					int i;
					obj* volatile* my_free_list;
					obj* volatile* p;
					for (i = size; i <= __MAX_BYTES; i += __ALIGN) {
						my_free_list = free_list + FREELIST_INDEX(size);
						p = my_free_list;
						if (p != 0) {
							//*my_free_list = p->free_list_link;
							start_free = (char*)p;
							end_free = start_free + i;
							return (chunk_alloc(size, nobjs));
						}
					}
					end_free = 0;
					start_free = (char*)malloc(bytes_to_get);
				}
				heap_size += bytes_to_get;
				end_free = start_free + bytes_to_get;
				return (chunk_alloc(size, nobjs));
			}
		}
	}
}