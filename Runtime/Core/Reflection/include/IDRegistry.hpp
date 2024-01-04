#pragma once
#include "Type.hpp"
#include <shared_mutex>
#include <unordered_set>
#ifdef __clang__
#include <experimental/memory_resource>
#include <experimental/unordered_map>
#include <experimental/unordered_set>
#else
#include<memory_resource>
#endif
#include <cstring>

template<typename T, typename U>
class IDRegistry
{
public:
	IDRegistry() :id2name{ &resource }
	{

	}
	void RegisterUnmanaged(T ID, std::string_view name)
	{
		assert(!name.empty());
		std::shared_lock rlock{ smutex };
		auto target = id2name.find(ID);
		if (target != id2name.end()) {
			assert(target->second == name);
			return;
		}
		rlock.unlock();
		std::lock_guard wlock{ smutex };
		id2name.emplace_hint(target, ID, name);
	}

	T RegistrUnmanaged(std::string_view name)
	{
		T ID{ name };
		RegisterUnmanaged(ID, name);
		return ID;
	}
	std::string_view Register(T ID, std::string_view name)
	{
		assert(!name.empty());
		std::shared_lock rlock{ smutex };
		auto target = id2name.find(ID);
		if (target != id2name.end()) {
			assert(target->second == name);
			return target->second;
		}
		rlock.unlock();
		assert(name.data() && name.data()[name.size()] == 0);
		std::lock_guard wlock{ smutex };
		auto buffer = reinterpret_cast<char*>(resource.allocate(name.size() + 1, alignof(char)));
		memcpy(buffer, name.data(), name.size());
		std::string_view new_name{ buffer,name.size() };
		id2name.emplace_hint(target, ID, new_name);
		return new_name;
	}

	U Register(std::string_view name)
	{
		T ID{ name };
		auto new_name = Register(ID, name);
		return { new_name,ID };
	}

	bool IsRegistered(T ID)const
	{
		std::shared_lock{smutex};
		return id2name.contains(ID);
	}

	std::string_view ViewOf(T ID)const
	{
		std::shared_lock rlock{ smutex };
		auto iter = id2name.find(ID);
		if (iter != id2name.end()) {
			return iter->second;
		}
		return {};
	}

	void UnregisterUnmanaged(T ID)
	{
		std::shared_lock rlock{ smutex };
		auto target = id2name.find(ID);
		if (target == id2name.end()) {
			return;
		}
		rlock.unlock();
		std::lock_guard wlock{ smutex };
		id2name.erase(target);
	}

	void Clear()noexcept
	{
		id2name.clear();
    //	resource.release();
	}
protected:
#ifdef __clang__
        std::experimental::pmr::polymorphic_allocator<char>get_allocator() { return &resource; }
#else
	std::pmr::polymorphic_allocator<char>get_allocator() { return &resource; }
#endif
	mutable std::shared_mutex smutex;
private:
#ifdef __clang__
    std::experimental::pmr::polymorphic_allocator<char>  resource;
        std::experimental::pmr::unordered_map<T, std::string_view>id2name;
#else
    std::pmr::monotonic_buffer_resource resource;
	std::pmr::unordered_map<T, std::string_view>id2name;
#endif
};

class TypeIDRegistry :public IDRegistry<TypeID, Type> 
{
public:
	using IDRegistry<TypeID, Type>::Register;
	struct Meta {
		static constexpr Type global{ "__global" };
	};

	TypeIDRegistry() :IDRegistry<TypeID, Type>()
	{
	}

	template<typename T>
	void Register()
	{
		IDRegistry<TypeID,Type>::RegisterUnmanaged(typeid_of<T>, type_name<T>());
	}

	template<typename T>
	bool IsRegistered()const
	{
		static_assert(!std::is_volatile_v<T>);
        return true;
	}


	Type Typeof(TypeID ID)const
	{
		auto view = ViewOf(ID);
		if (view.empty()) {
			return {};
		}
		return { view,ID };
	}

	//Type RegisterAddConstLValueReference(Type type)
//	{
		//std::string_view name = type.GetName();
		//if (name.empty()) {
		//	return {};
		//}
		//TypeID ref_ID{ type_name_add_const_lvalue_reference_hash(name) };
		//if (auto ref_name = ViewOf(ref_ID); ref_name.empty()) {
		//	return { ref_name, ref_ID };
		//}
		//std::string_view rst_name;
		//{
		//	std::lock_guard wlock{ smutex };
		//	rst_name = type_name_add_const_lvalue_reference(name, get_allocator());
		//}
		//RegisterUnManaged(ref_ID, rst_name);
		//return { rst_name,ref_ID };

//	}

};

class NameIDRegistry:IDRegistry<NameID,Name>
{
public:
	struct Meta {
		static constexpr Name operator_bool{ "__bool" };

		static constexpr Name operator_add{ "__add" };
		static constexpr Name operator_sub{ "__sub" };
		static constexpr Name operator_mul{ "__mul" };
		static constexpr Name operator_div{ "__div" };
		static constexpr Name operator_mod{ "__mod" };

		static constexpr Name operator_bnot{ "__bnot" };
		static constexpr Name operator_band{ "__band" };
		static constexpr Name operator_bor{ "__bor" };
		static constexpr Name operator_bxor{ "__bxor" };
		static constexpr Name operator_shl{ "__shl" };
		static constexpr Name operator_shr{ "__shr" };

		static constexpr Name operator_pre_inc{ "__pre_inc" };
		static constexpr Name operator_pre_dec{ "__pre_dec" };
		static constexpr Name operator_post_inc{ "__post_inc" };
		static constexpr Name operator_post_dec{ "__post_dec" };

		static constexpr Name operator_assignment{ "__assignment" };
		static constexpr Name operator_assignment_add{ "__assignment_add" };
		static constexpr Name operator_assignment_sub{ "__assignment_sub" };
		static constexpr Name operator_assignment_mul{ "__assignment_mul" };
		static constexpr Name operator_assignment_div{ "__assignment_div" };
		static constexpr Name operator_assignment_mod{ "__assignment_mod" };
		static constexpr Name operator_assignment_band{ "__assignment_band" };
		static constexpr Name operator_assignment_bor{ "__assignment_bor" };
		static constexpr Name operator_assignment_bxor{ "__assignment_bxor" };
		static constexpr Name operator_assignment_shl{ "__assignment_shl" };
		static constexpr Name operator_assignment_shr{ "__assignment_shr" };

		static constexpr Name operator_eq{ "__eq" };
		static constexpr Name operator_ne{ "__ne" };
		static constexpr Name operator_lt{ "__lt" };
		static constexpr Name operator_le{ "__le" };
		static constexpr Name operator_gt{ "__gt" };
		static constexpr Name operator_ge{ "__ge" };

		static constexpr Name operator_and{ "__and" };
		static constexpr Name operator_or{ "__or" };
		static constexpr Name operator_not{ "__not" };

		static constexpr Name operator_subscript{ "__subscript" };
		static constexpr Name operator_indirection{ "__indirection" };

		static constexpr Name operator_call{ "__call" };

		// non-member functions

		static constexpr Name ctor{ "__ctor" };
		static constexpr Name dtor{ "__dtor" };

		static constexpr Name get{ "__get" };
		static constexpr Name variant_visit_get{ "__variant_visit_get" }; // std::visit + std::get

		static constexpr Name tuple_size{ "__tuple_size" };
		static constexpr Name tuple_element{ "__tuple_element" };

		static constexpr Name get_if{ "__get_if" };
		static constexpr Name holds_alternative{ "__holds_alternative" };
		static constexpr Name variant_size{ "__variant_size" };
		static constexpr Name variant_alternative{ "__variant_alternative" };

		static constexpr Name advance{ "__advance" };
		static constexpr Name distance{ "__distance" };
		static constexpr Name next{ "__next" };
		static constexpr Name prev{ "__prev" };

		// member functions

		static constexpr Name container_assign{ "assign" };

		static constexpr Name container_begin{ "begin" };
		static constexpr Name container_cbegin{ "cbegin" };
		static constexpr Name container_end{ "end" };
		static constexpr Name container_cend{ "cend" };
		static constexpr Name container_rbegin{ "rbegin" };
		static constexpr Name container_crbegin{ "crbegin" };
		static constexpr Name container_rend{ "rend" };
		static constexpr Name container_crend{ "crend" };

		static constexpr Name container_at{ "at" };
		static constexpr Name container_data{ "data" };
		static constexpr Name container_front{ "front" };
		static constexpr Name container_back{ "back" };
		static constexpr Name container_top{ "top" };

		static constexpr Name container_empty{ "empty" };
		static constexpr Name container_size{ "size" };
		static constexpr Name container_size_bytes{ "size_bytes" };
		static constexpr Name container_resize{ "resize" };
		static constexpr Name container_capacity{ "capacity" };
		static constexpr Name container_bucket_count{ "bucket_count" };
		static constexpr Name container_reserve{ "reserve" };
		static constexpr Name container_shrink_to_fit{ "shrink_to_fit" };

		static constexpr Name container_clear{ "clear" };
		static constexpr Name container_insert{ "insert" };
		static constexpr Name container_insert_after{ "insert_after" };
		static constexpr Name container_insert_or_assign{ "insert_or_assign" };
		static constexpr Name container_erase{ "erase" };
		static constexpr Name container_erase_after{ "erase_after" };
		static constexpr Name container_push_front{ "push_front" };
		static constexpr Name container_pop_front{ "pop_front" };
		static constexpr Name container_push_back{ "push_back" };
		static constexpr Name container_pop_back{ "pop_back" };
		static constexpr Name container_push{ "push" };
		static constexpr Name container_pop{ "pop" };
		static constexpr Name container_swap{ "swap" };
		static constexpr Name container_merge{ "merge" };
		static constexpr Name container_extract{ "extract" };

		static constexpr Name container_splice_after{ "splice_after" };
		static constexpr Name container_splice{ "splice" };
		static constexpr Name container_remove{ "remove" };
		static constexpr Name container_reverse{ "reverse" };
		static constexpr Name container_unique{ "unique" };
		static constexpr Name container_sort{ "sort" };

		static constexpr Name container_count{ "count" };
		static constexpr Name container_find{ "find" };
		static constexpr Name container_lower_bound{ "lower_bound" };
		static constexpr Name container_upper_bound{ "upper_bound" };
		static constexpr Name container_equal_range{ "equal_range" };

		static constexpr Name variant_index{ "index" };
		static constexpr Name variant_valueless_by_exception{ "valueless_by_exception" };

		static constexpr Name optional_has_value{ "has_value" };
		static constexpr Name optional_value{ "value" };
		static constexpr Name optional_reset{ "reset" };
	};
	using IDRegistry<NameID, Name>::Register;
};

