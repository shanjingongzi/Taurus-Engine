#ifndef VAR_RANGE_H
#define VAR_RANGE_H
#include <tuple>
#include "ObjectTree.h"
#include <unordered_map>
class VarRange
{
public:
	class iterator
	{
	public:
		using value_type = std::tuple<Name, ObjectView>;
		using reference = const value_type&;
		using pointer = const value_type*;
		using iterator_category = std::forward_iterator_tag;
		struct Derived {
			Type type;
			TypeInfo* typeInfo;
			std::unordered_map<Type, BaseInfo>::iterator curbase;
		};
		iterator(ObjectTree::iterator typeiter, CVRefMode cvRefMode = CVRefMode::None, FieldFlag flat = FieldFlag::All);
		iterator& operator++();
		iterator operator++(int n);
		reference operator*() { return value; }
		pointer operator->() { return &value; }
		friend bool operator==(const iterator& lhs, const iterator& rhs);
		friend bool operator!=(const iterator& lhs, const iterator& rhs);
		bool Valid()const noexcept { return mode != -1; }
	private:
		void update();

		CVRefMode cvref_mode;
		FieldFlag flag;
		ObjectTree::iterator typeiter;
		std::unordered_map<Name, FieldInfo>::iterator curfield;
		int mode;
		value_type value;
	};
	constexpr VarRange(ObjectView obj, FieldFlag inFlag)noexcept:
		objectTree{ ObjectTree{obj} }, flag(inFlag), cvref_mode{ obj.GetType().GetCVRefMode() }
	{

	}
	constexpr explicit VarRange(ObjectView obj) :VarRange{ obj,FieldFlag::All } {}
	constexpr VarRange(Type type)noexcept :VarRange{ ObjectView{type},FieldFlag::UnOwned  } {}
	constexpr VarRange(Type type, FieldFlag flag) : VarRange{ ObjectView{type},flag } {}
	iterator begin()const noexcept {
		return { objectTree.begin(), cvref_mode, flag };
	}

	iterator end()const noexcept {
		return { objectTree.end(),cvref_mode,flag };
	}
private:
	ObjectTree objectTree;
	FieldFlag flag;
	CVRefMode cvref_mode;

};

template<typename T,FieldFlag flag=FieldFlag::UnOwned>
static constexpr VarRange VarRange_of = VarRange{ ObjectView_of<T>,flag };

#endif
