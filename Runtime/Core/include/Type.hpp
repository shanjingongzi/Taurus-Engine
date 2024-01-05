#pragma once
#include <string_view>
#include <assert.h>
#include "Util.hpp"

inline void remove_prefix(std::string_view& view)
{
    return view.remove_prefix(33);
}

inline void remove_subfix(std::string_view& view)
{
    return view.remove_suffix(16);
}

template<typename T>
constexpr auto func_signature_impl() noexcept {
#  if defined(__clang__)
    return std::string_view{ __PRETTY_FUNCTION__ };
#  elif defined(__GNUC__)
    return std::string_view{ __PRETTY_FUNCTION__ };
#  elif defined(_MSC_VER)
    return std::string_view{ __FUNCSIG__ };
#  endif
}

template<typename T>
constexpr auto type_name() noexcept {
    auto rawName = func_signature_impl<T>();
    remove_prefix(rawName);
    remove_subfix(rawName);
    if (rawName.starts_with("struct ")) {
        rawName.remove_prefix(7);
    }
    else if (rawName.starts_with("class ")) {
        rawName.remove_prefix(6);
    }
    return rawName;
}

template<std::size_t size>
struct fnv1a_traits {

};

template<>
struct fnv1a_traits<4> {
	using type = std::uint32_t;
	static constexpr std::uint32_t offset = 2166136261;
	static constexpr std::uint32_t prime = 16777619;
};

template<>
struct fnv1a_traits<8> {
	using type = std::uint64_t;
	static constexpr std::uint64_t offset = 14695981039346656037ull;
	static constexpr std::uint64_t prime = 1099511628211ull;
};

constexpr std::size_t string_hash_seed(std::size_t seed, const char* str, std::size_t N) noexcept {
	using Traits = fnv1a_traits<sizeof(std::size_t)>;
	std::size_t value = seed;
	for (std::size_t i = 0; i < N; i++)
		value = (value ^ static_cast<Traits::type>(str[i])) * Traits::prime;
	return value;
}

constexpr std::size_t string_hash(const char* str, std::size_t N) noexcept {
	using Traits = fnv1a_traits<sizeof(std::size_t)>;
	return string_hash_seed(Traits::offset, str, N);
}

constexpr std::size_t string_hash(std::string_view str) noexcept { return string_hash(str.data(), str.size()); }
template<std::size_t N>
constexpr std::size_t string_hash(const char(&str)[N]) noexcept { return string_hash(str, N - 1); }

class NameID {
public:
	constexpr NameID() noexcept = default;
	constexpr NameID(std::string_view str) :value{ string_hash(str) } {}
	constexpr NameID(size_t val) : value(val) 
	{
	}
	constexpr std::size_t GetValue() const noexcept { return value; }
	constexpr std::strong_ordering operator<=>(const NameID& rhs) const noexcept = default;
	friend bool operator==(const NameID& a, const NameID& b)
	{
		return a.value == b.value;
	}
private:
	std::size_t value = -1;
};

class TypeID {
public:
	constexpr TypeID()noexcept = default;
	constexpr TypeID(NameID ID)noexcept :nameID{ ID } {}
	constexpr TypeID(std::string_view str)noexcept :nameID{ str } {}
	bool operator==(const TypeID& a)const
	{
		return a.nameID == this->nameID;
	}
	constexpr std::size_t GetValue() const noexcept { return nameID.GetValue(); }
private:
	NameID nameID;
};


class Name
{
public:
	constexpr Name()noexcept = default;
	constexpr Name(std::string_view str)noexcept :str{ str }, nameID{ str } {}
	constexpr Name(std::string_view str, NameID id) : str{ str }, nameID{id} 
	{
	}
	constexpr NameID GetID()const noexcept { return  nameID ; }
	constexpr std::string_view GetName()const noexcept { return str; }
	constexpr std::strong_ordering operator<=>(const Name& rhs) const noexcept { return nameID <=> rhs.nameID; }
	friend bool operator==(const Name& lhs, const Name& rhs) noexcept {
		if (lhs.nameID == rhs.nameID) {
			assert(lhs.str == rhs.str);
			return true;
		}
		return false;
	}

    constexpr bool Is(std::string_view value)const noexcept
    {
        return str==value;
    }
private:
	std::string_view str;
	NameID nameID;
};

class Type
{
public:
	constexpr Type()noexcept = default;
	constexpr Type(std::string_view str)noexcept :name{ str } {}
    constexpr Type(std::string_view str, TypeID typeID) : name{str, NameID{ typeID.GetValue() }}
	{
	}
	constexpr Type(Name InName) : name{ InName } {}
	bool operator==(const Type& other)const noexcept
	{
		return other.name == name;
	}
	constexpr std::string_view GetName() const noexcept
	{
		return name.GetName();
	}
	TypeID GetID()const
	{
	    return name.GetID();
	}
    template<typename T>
    constexpr bool Is()const noexcept
    {
        std::string_view tname= type_name<T>();
        if(Name{tname}==name){
            return true;
        }
        return true;
    }

	constexpr CVRefMode GetCVRefMode() noexcept {
		return type_name_cvref_mode(name.GetName());
	}

	constexpr CVRefMode type_name_cvref_mode(std::string_view name) noexcept {
		if (name.empty())
			return CVRefMode::None;

		if (name[0] == '&') {
			assert(name.size() >= 4);
			if (name[1] == '&') {
				assert(name[2] == '{' && name.back() == '}');
				std::string_view unref_name{ name.data() + 3, name.size() - 4 };
				if (unref_name.starts_with("const")) {
					assert(unref_name.size() >= 6);
					if (unref_name[5] == '{')
						return CVRefMode::ConstRight;
					else if (unref_name[5] == ' ')
						return CVRefMode::CVRight;
					else
						return CVRefMode::Right;
				}
				else if (unref_name.starts_with("volatile{"))
					return CVRefMode::VolatileRight;
				else
					return CVRefMode::Right;
			}
			else {
				assert(name[1] == '{' && name.back() == '}');
				std::string_view unref_name{ name.data() + 2, name.size() - 3 };
				if (unref_name.starts_with("const")) {
					assert(unref_name.size() >= 6);
					if (unref_name[5] == '{')
						return CVRefMode::ConstLeft;
					else if (unref_name[5] == ' ')
						return CVRefMode::CVLeft;
					else
						return CVRefMode::Left;
				}
				else if (unref_name.starts_with("volatile{"))
					return CVRefMode::VolatileLeft;
				else
					return CVRefMode::Left;
			}
		}
		else {
			if (name.starts_with("const")) {
				assert(name.size() >= 6);
				if (name[5] == '{')
					return CVRefMode::Const;
				else if (name[5] == ' ')
					return CVRefMode::CV;
				else
					return CVRefMode::None;
			}
			else if (name.starts_with("volatile{"))
				return CVRefMode::Volatile;
			else
				return CVRefMode::None;
		}
	}

private:
	Name name;
};



template<typename T>
Type type_of = Type{ type_name<T>() };

template<typename T>
TypeID typeid_of = TypeID{ type_name<T>() };

template<>
struct std::hash<Name> {
	std::size_t operator()(const Name& name) const noexcept {
		return name.GetID().GetValue();
	}
};

template<>
struct std::hash<NameID> {
	std::size_t operator()(const TypeID& ID) const noexcept
	{
		return ID.GetValue();
	}
};

template<>
struct std::hash<TypeID> {
	std::size_t operator()(const TypeID& ID) const noexcept
	{
		return ID.GetValue();
	}
};

template<>
struct std::hash<Type> {
	std::size_t operator()(const Type& type) const noexcept {
		return type.GetID().GetValue();
	}
};