#pragma once
#include "TObject.h"
#include "BoxSphereBounds.hpp"
#include "Core.h"
#include "Octree.hpp"
#include <memory>


struct NavigationOctreeFilter
{

};

struct CompositeNavModifier {

};


struct NavigationRelevantData
{
    TObject* sourceObject;
    BoxSphereBounds bounds;
    explicit NavigationRelevantData(TObject* inSourceObject) :sourceObject(inSourceObject) {}
    FORCEINLINE bool IsEmpty()
    {
        return sourceObject == nullptr;
    }
    
    FORCEINLINE bool IsMatchingFilter(const NavigationOctreeFilter& filter)const
    {
        return false;
    }
    
    FORCEINLINE  CompositeNavModifier GetModifierForAgent()
    {
        return  CompositeNavModifier();
    }

    void Shrink()
    {

    }
    
    void ValidateAndSharink()
    {

    }


};

struct NavigationOctreeElement
{
    BoxSphereBounds bounds;
    int32 ownerUniqueId=INDEX_NONE;
    NavigationRelevantData *data;
public:
    NavigationOctreeElement() {}
    explicit NavigationOctreeElement(TObject *sourceObject):data(new NavigationRelevantData(sourceObject)),ownerUniqueId(sourceObject->GetUniqueID()){}
    NavigationOctreeElement(TObject* sourceObject, const BoxSphereBounds& bounds)
        :data(new NavigationRelevantData(sourceObject)), ownerUniqueId(sourceObject->GetUniqueID()), bounds(bounds)
    {

    }
    NavigationOctreeElement(const NavigationOctreeElement& other)
        :bounds(other.bounds), data(other.data), ownerUniqueId(other.ownerUniqueId)
    {

    }

    NavigationOctreeElement operator=(const NavigationOctreeElement& other)
    {
        new (this) NavigationOctreeElement(other);
        return *this;
    }

    FORCEINLINE bool IsEmpty()const
    {
        auto box = bounds.GetBox();
        return data->IsEmpty() && (box.IsValid == 0 || box.GetSize().IsNearlyZero());
    }

    FORCEINLINE bool IsMatchingFilter(const NavigationOctreeFilter& filter)const
    {
        return data->IsMatchingFilter(filter);
    }

    int Num()const
    {
        return 1;
    }



    inline void Shrink()
    {
        return data->Shrink();
    }

    FORCEINLINE void ValidateAndShrink()
    {
        return data->ValidateAndSharink();
    }

    FORCEINLINE TObject* GetOwner(bool EventIfPendingKill = false)const
    {
        return data->sourceObject;
    }

    
};

struct NavigationOctreeSemantics
{
    using NOctree=Octree<NavigationOctreeElement,NavigationOctreeSemantics>;
    enum { MaxElementPerLeaf = 16 };
    enum { MinInclusiveElementPreNode = 7 };
    enum { MaxNodeDepth = 12 };
    inline static BoxSphereBounds GetBoundingBox(const NavigationOctreeElement& navData)
    {
        return navData.bounds;
    }

    inline static bool AreElementEqual(const NavigationOctreeElement& A, const NavigationOctreeElement& B)
    {
        return  A.data->sourceObject == B.data->sourceObject;
    }

    inline static void ApplyOffset(NavigationOctreeElement& element, const Vector& inOffset)
    {

    }

    static int  maxElementPerLeaf;
     
};
