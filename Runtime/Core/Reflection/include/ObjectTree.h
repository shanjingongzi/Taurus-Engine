#ifndef OBJECT_TREE_H
#define OBJECT_TREE_H
#include "Object.hpp"
#include "TField.h"
#include <tuple>

namespace Ranges
{
    struct Derived {
        ObjectView obj;
        TypeInfo* typeinfo;
        std::unordered_map<Type, BaseInfo>::iterator curbase;
        friend bool operator==(const Derived& lhs, const Derived& rhs)
        {
            return lhs.obj.GetType() == rhs.obj.GetType() &&
                lhs.obj.GetPtr() == rhs.obj.GetPtr() &&
                lhs.curbase == rhs.curbase;
        }
    };
}
class ObjectTree
{
public:
    class iterator{
    public:
        using value_type=std::tuple<TypeInfo *,ObjectView>;
        using reference =const value_type &;
        using pointer=const value_type *;
        using iterator_category =std::forward_iterator_tag;
        iterator(ObjectView obj,bool begin_or_end);
        iterator& operator++();
        reference operator*()const noexcept{return value;}
        pointer operator->()const noexcept{return &value;}
        friend bool operator==(const iterator &lhs,const iterator &rhs);
        friend bool operator!=(const iterator&lhs,const iterator &rhs);
        bool Vaild()const noexcept{return mode!=-1;}
        //std::span<const Ranges::Derived>GetDeriveds()const noexcept { return { deriveds.begin(),deriveds.end() }; }
    private:
        friend ObjectTree;
        void update();
        std::vector<Type>visitedVBs;
        std::vector<Ranges::Derived>deriveds;
        bool curbase_valid;
        int mode;
        value_type value;
    };
    constexpr explicit ObjectTree(ObjectView InObj)noexcept :obj{ InObj } {}
    constexpr explicit ObjectTree(Type type)noexcept:ObjectTree{ObjectView{type}}{}
    iterator begin()const noexcept
    {
        return { obj,true };
    }
    iterator end()const noexcept
    {
        return { obj,false };
    }
private:
    ObjectView obj;
};

template<typename T>
static constexpr ObjectTree ObjectTree_of=ObjectTree{ObjectView_of<T>};

#endif
