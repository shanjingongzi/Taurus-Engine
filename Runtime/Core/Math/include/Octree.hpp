#pragma once
#include "Array.hpp"
#include "MathSSE.h"
#include "Box.hpp"
#include "glm/glm.hpp"
#include "BoxSphereBounds.hpp"
#include "te_iterator_base.h"
#include "Math.hpp"
#include "OctreePublic.h"
#include <vector>
using Vector4 = glm::tvec4<double>;


#define  FORCEINLINE inline

#ifdef _DEBUG
#define ASSERT(expression) assert((expression))
#else 
#define ASSERT(EXP) 
#endif
namespace 
{
    inline void VectorAbs(Vector4 &vector)
    {
        vector.x=vector.x>0?vector.x:-vector.x;
        vector.y=vector.y>0?vector.y:-vector.y;
        vector.z=vector.z>0?vector.z:-vector.z;
        vector.w=vector.w>0?vector.w:-vector.w;
    }

    FORCEINLINE bool VectorAnyGreaterThan(const Vector4& vec1,const Vector4 &vec2)
    {
        bool ret=false;
        for(int i=0;i<4;++i){
            ret=ret||vec2[i]>vec1[i];
        }
        return ret;
    }
}

using NodeIndex = size_t;

class BoxCenterAndExtent
{
public:
    glm::tvec4<double> center;
    glm::tvec4<double> extent;
    BoxCenterAndExtent(){}
    BoxCenterAndExtent(const Vector &inCenter,const Vector &inExtent):
        center(inCenter.x,inCenter.y,inCenter.z,1.0f),
        extent(inExtent.x,inExtent.y,inExtent.z,1.0f){}
    BoxCenterAndExtent(const Box&box)
    {
        Vector c,e;
        box.GetCenterAndExtent(c,e); 
        center=Vector4(c.x,c.y,c.z,0.0);
        extent=Vector4(e.x,e.y,e.z,0.0);
    }

    explicit BoxCenterAndExtent(const BoxSphereBounds &boxShphere)
    {
        center = Vector4(boxShphere.origin.x,boxShphere.origin.y,boxShphere.origin.z,1.0);
        extent = Vector4(boxShphere.boxExtent.x,boxShphere.boxExtent.y,boxShphere.boxExtent.z,1.0);
    }
    template<typename TExtent>
    explicit BoxCenterAndExtent(const float PositionRadius[4])
    {
        center=Vector4(PositionRadius[0],PositionRadius[1],PositionRadius[2],0.0);
        extent=Vector4(PositionRadius[3],PositionRadius[3],PositionRadius[3],0.0);
    }
    Box GetBox()const
    {
        return Box(center-extent,center+extent);
    }

    //box �ཻ

    FORCEINLINE bool Intersect(const BoxCenterAndExtent&a,const BoxCenterAndExtent &b)
    {
        Vector4 centerDiffernce=a.center-b.center;
        VectorAbs(centerDiffernce);
        Vector4 compositeExtent=a.extent+b.extent;
        return VectorAnyGreaterThan(centerDiffernce,compositeExtent);
    }

    FORCEINLINE bool Intersect(const float a[4],const BoxCenterAndExtent &b)
    {
        Vector4 aCenter=Vector4(a[0],a[1],a[2],0.0f);
        Vector4 centerDifference=aCenter-b.center;
        VectorAbs(centerDifference);
        Vector4 compositeExtent(b.center.x+a[3],b.center.y+a[3],b.center.z+a[3],0.0);
        return VectorAnyGreaterThan(centerDifference,compositeExtent);
    }
};

class OctreeChildNodeRef
{
public:
	int8 index;

    OctreeChildNodeRef() {}

    OctreeChildNodeRef(int inX, int inY, int inZ)
    {
        ASSERT(inX >= 0 && inX <= 1);
        ASSERT(inY >= 0 && inY <= 1);
        ASSERT(inZ >= 0 && inZ <= 1);
        index = int8(inX << 0) | int8(inY << 1) | int8(inZ << 2);
    }

    OctreeChildNodeRef(int8 inIndex) :index(inIndex)
    {
        ASSERT(index < 8);
    }

    FORCEINLINE void Advance()
    {
        ++index;
    }

    FORCEINLINE bool IsNull()const
    {
        return index >= 8;
    }

    FORCEINLINE void SetNull()
    {
        index = 8;
    }

    FORCEINLINE int32 x()const
    {
        return (index >> 0) & 1;
    }

    FORCEINLINE int32 y()const
    {
        return (index >> 1) & 1;
    }

    FORCEINLINE int32 z()const
    {
        return (index >> 2) & 1;
    }
};

class OctreeChildNodeSubSet
{
public:
    union 
    {
       struct 
       {
            uint32 bPositiveX:1;
            uint32 bPositiveY:1;
            uint32 bPositiveZ:1;
            uint32 bNegativeX:1;
            uint32 bNegativeY:1;
            uint32 bNegativeZ:1;  
       };
       struct 
       {
            uint32 positiveChildBits:3;
            uint32 negativeChildBits:3;
       };

       uint32 childBits:6;
       uint32 allBits;
    };
    OctreeChildNodeSubSet():allBits(0){}

    OctreeChildNodeSubSet(OctreeChildNodeRef childRef):allBits(0)
    {
        positiveChildBits=childRef.index;
        negativeChildBits=~childRef.index;
    }

    FORCEINLINE bool Contains(OctreeChildNodeRef childRef)
    {
        const OctreeChildNodeSubSet childSubSet(childRef);
        return (childBits & childSubSet.childBits) == childSubSet.childBits;
    }
};

class OctreeNodeContext
{
    using Real = double;
public:
    enum {LoosenessDenominator=16};
    Real childExtent=0.0;
    Real childCenterOffset=0.0;
    uint32 inCullBits;
    uint32 outCullBits;
    BoxCenterAndExtent bounds;
    
    OctreeNodeContext()
    {
    }
    
    OctreeNodeContext(uint32 inInCullBits,uint32 inOutCullBits)
        :inCullBits(inInCullBits),outCullBits(inOutCullBits)
    {
    }

OctreeNodeContext(const BoxCenterAndExtent& inBounds)
    :bounds(inBounds)
{
    const Real TightChildExtent = bounds.extent.x * 0.5;
    const Real LooseChildExtent = TightChildExtent * (1.0f + 1.0f / (Real)LoosenessDenominator);
    childExtent = LooseChildExtent;
    childCenterOffset = bounds.extent.x - LooseChildExtent;
}

FORCEINLINE OctreeNodeContext(const BoxCenterAndExtent& inBounds, uint32 inInCullBits, uint32 inOutCullBits) :
    bounds(inBounds), inCullBits(inInCullBits), outCullBits(inOutCullBits)
{
    const Real TightChildExtent = bounds.extent.x * 0.5f;
    const Real LooseChildExtent = TightChildExtent * (1.0f + 1.0f / (Real)LoosenessDenominator);

    childExtent = LooseChildExtent;
    childCenterOffset = bounds.extent.x - LooseChildExtent;
}

FORCEINLINE VectorRegister GetChildOffsetVec(int i)const
{
    union MaskType {
        VectorRegister4Float v;
        VectorRegister4Int i;
    }Mask;
    Mask.v = MakeVectorRegister(1u, 2u, 4u, 8u);
    VectorRegister4Int X = VectorIntLoad1(&i);
    VectorRegister4Int A = VectorIntAnd(X, Mask.i);
    Mask.i = VectorIntCompareEQ(Mask.i, A);
    return VectorSelect(Mask.v, VectorSetFloat1(childCenterOffset), VectorSetFloat1(-childCenterOffset));
}

FORCEINLINE OctreeNodeContext GetChildContext(const OctreeChildNodeRef& childRef)const
{
    BoxCenterAndExtent localBounds;
    double zeroArray[4] = {1.0,1.0,1.0,0.1};
    VectorRegister ZeroW = VectorLoadAligned(zeroArray);
    VectorRegister4Double childOffect = GetChildOffsetVec(childRef.index);
    auto centerScale=VectorAdd(VectorLoadAligned(&bounds.center), GetChildOffsetVec(childRef.index));
    auto center = VectorMultiply(ZeroW, centerScale);
    VectorStoreAligned(VectorMultiply(ZeroW, centerScale), &(localBounds.center.x));
    VectorStoreAligned(VectorMultiply(ZeroW, VectorSetFloat1(childExtent)), &(localBounds.extent.x));
    return OctreeNodeContext(localBounds);
}

OctreeChildNodeSubSet GetIntersectingChildren(const BoxCenterAndExtent& boundingBox)
{
    return OctreeChildNodeSubSet();
}
OctreeChildNodeRef GetContainingChild(const BoxCenterAndExtent& queryBounds)const
{
    OctreeChildNodeRef result;
    const VectorRegister queryBoundsCenter = VectorLoadAligned(&queryBounds.center);
    const VectorRegister queryBoundsExtent = VectorLoadAligned(&queryBounds.extent);

    const VectorRegister boundsCenter = VectorLoadAligned(&bounds.center);
    const VectorRegister childCenterOffsetVector = VectorLoadFloat1(&childCenterOffset);
    const VectorRegister NegativeCenterDifferce = VectorSubstract(queryBoundsCenter, VectorSubstract(boundsCenter, childCenterOffsetVector));
    const VectorRegister PositiveCenterDifferce = VectorSubstract(VectorAdd(boundsCenter, childCenterOffsetVector), queryBoundsCenter);

    const VectorRegister minDifference = VectorMin(PositiveCenterDifferce, NegativeCenterDifferce);
    if (VectorAnyGreaterThan(VectorAdd(queryBoundsExtent, minDifference), VectorLoadFloat1(&childExtent)))
    {
        result.SetNull();
    }
    else
    {
        result.index = VectorMaskBits(VectorCompareGT(queryBoundsCenter, boundsCenter)) & 0x7;
    }

    return result;

}

};

struct Node {
    Node() {
        childNodes = INDEX_NONE;
        inclusiveNumElements = 0;
    }
    Node(const Node& other)
    {
        childNodes = other.childNodes;
        inclusiveNumElements = other.inclusiveNumElements;
    }
    NodeIndex childNodes = INDEX_NONE;
    uint32 inclusiveNumElements = 0;

    bool IsLeaf()const
    {
        return childNodes == INDEX_NONE;
    }
};

template<typename Tp>
struct octree_iterator
{
    typedef octree_iterator<Tp> self;
    typedef typename Array<Tp>::iterator internal_iterator;
    octree_iterator() :iterator_cursor(0) {}
    octree_iterator(size_t inIterCursor,std::vector<internal_iterator>inInternalIters)
        : iterator_cursor(inIterCursor), internalIters(inInternalIters)
    {
    }

    ~octree_iterator()
    {
        internalIters.clear();
    }

	inline self& operator++()
	{
        ++iterator_cursor;
        return *this;
	}

    inline self& operator--()
    {
        --iterator_cursor;
        return *this;
    }

    inline self& operator+(int n) 
    {
        iterator_cursor += n;
        return *this;
    }

    inline self& operator-(int n)
    {
        iterator_cursor -= n;
        return *this;
    }

    inline internal_iterator operator->()
    {
        return internalIters[iterator_cursor];
    }

    inline Tp operator*()
    {
        return *internalIters[iterator_cursor];
    }

    inline bool operator!=(const self& other)
    {
        return iterator_cursor != other.iterator_cursor&&internalIters.size()!=0;
    }
    
    inline bool operator ==(const self& other)
    {
        return iterator_cursor == other.iterator_cursor||internalIters.size()==0;
    }
private:
    size_t iterator_cursor;
    std::vector <internal_iterator> internalIters;
};

template<typename ElementType,typename OctreeSemantics,typename InAllocatorType=TE::MEMORY::Allocator<ElementType>>
class Octree
{
    using ElementArrayType=Array<ElementType>;
    typedef ElementType Element;
    typedef ElementType value_type;
    typedef ElementType* pointer;
    typedef ElementType& refernce;
    typedef ptrdiff_t differnce_type;
    typedef octree_iterator<ElementType> iterator;
    friend class NavigationScene;
public:
    Octree()
    {
        treeNodes.AddDefaulted();
        treeElements.AddDefaulted();
    }

    Octree(const Vector& inOrigin, const Real inExtent)
        :rootNodeContext(BoxCenterAndExtent(inOrigin, Vector(inExtent, inExtent, inExtent)), 0, 0),
        minLeafExtent(0)
    {
        treeNodes.AddDefaulted();
        treeElements.AddDefaulted();
    }
    

public:


    inline size_t size()
    {
        size_t count= 0;
        for (auto iter = treeElements.begin(); iter != treeElements.end(); ++iter) {
            count += iter->size();
        }
        return count;
    }
   
    inline iterator begin()
    {
        typedef typename iterator::internal_iterator internalIter;
        std::vector<internalIter>internalIters;
        for (auto &iter : treeElements) {
            for (auto citer = iter.begin(); citer != iter.end(); ++citer) {
                internalIters.push_back(citer);
            }
        }
        return iterator(0, internalIters);
    }

    inline iterator end()
    {
        typedef typename iterator::internal_iterator internalIter;
        std::vector<internalIter>internalIters;
        for (auto &iter : treeElements) {
            for (auto citer = iter.begin(); citer != iter.end(); ++citer) {
                internalIters.push_back(citer);
            }
        }
        size_t iterCursor = internalIters.size();
        return iterator(iterCursor,internalIters);
    }

    Array<ElementArrayType> &Elements()
    {
        return treeElements;
    }
 
    class FreeList
    {
		struct Span
		{
			NodeIndex start;
			NodeIndex end;
		};
	Array<Span>freeList;
	public:
		FreeList()
		{
			reset();
		}
		void Push(NodeIndex nodeIndex)
		{
            int index = 1;
            int size = freeList.Num();
            while (size > 32) {
                const int leftoverSize = size % 2;
                size = size / 2;
                const int checkIndex = index + size;
                const int indexIfless = checkIndex + leftoverSize;
                index = freeList[checkIndex].start > nodeIndex ? indexIfless : index;
            }
            int arrayEnd = Min(index + size + 1, freeList.Num());
            while (index < arrayEnd) {
                if (freeList[index].start < nodeIndex) {
                    break;
                }
                index++;
            }
            if (index < freeList.Num() && freeList[index].end + 1 == nodeIndex) {
                freeList[index].end = nodeIndex;
                if (freeList[index - 1].start - 1 == nodeIndex) {
                    freeList[index - 1].start = freeList[index].start;
                    freeList.removeAt(index);
                }
                return;
            }

            if (freeList[index - 1].start == nodeIndex) {
                freeList[index - 1].start = nodeIndex;
                return;
            }
            freeList.insert(Span{ nodeIndex,nodeIndex }, index);
		}

		NodeIndex Pop()
		{
            Span& span = freeList.back();
            NodeIndex index = span.start;
            ASSERT(index != INDEX_NONE);
            if (span.start == span.end)
            {
                freeList.erase(freeList.end() - 1);
                return index;
            }
            else {
                span.start++;
                return index;
            }

		}


		void reset()
		{
            freeList.resize(1);
            freeList[0] = (Span{ INDEX_NONE,INDEX_NONE });
		}

        int Num()
        {
            return freeList.size() - 1;
        }
	};

    NodeIndex AllocateEightNodes()
    {
        NodeIndex index= INDEX_NONE;
        if (freeList.Num()) {
            index = (freeList.Pop() * 8) + 1;
        }
        else {
            index = treeNodes.AddDefaulted(8);
            parentLinks.AddDefaulted();
            NodeIndex elementIndex = treeElements.AddDefaulted(8);
        }
        return index;
    }


	void FreeEightNodes(NodeIndex index)
	{
		for (int i = 0; i < 8; ++i) {
			treeNodes[index + i] = Node();
		}
		parentLinks[(index - 1) / 8] = INDEX_NONE;
        freeList.Push((index - 1) / 8);
	}

    void SetElementId(const ElementType& element, OctreeElementId2 id) 
    {
        //SetOctreeSemanticesElementId<OctreeSemantics>(element, id);
    }

    inline void AddElement(ElementType element)
    {
        ElementArrayType tempElementStorage;
        const BoxCenterAndExtent elementBounds(OctreeSemantics::GetBoundingBox(element));
        AddElementInternal(0, rootNodeContext, elementBounds, element, tempElementStorage);
    }

	void AddElementInternal(NodeIndex currentNodeIndex, const OctreeNodeContext& nodeContext, const BoxCenterAndExtent& elementBounds, ElementType element, ElementArrayType& tempElementStorage)
	{
        ASSERT(currentNodeIndex != INDEX_NONE);
		treeNodes[currentNodeIndex].inclusiveNumElements++;
		if (treeNodes[currentNodeIndex].IsLeaf()) {
			if (treeElements[currentNodeIndex].Num() + 1 > OctreeSemantics::MaxElementPerLeaf && nodeContext.bounds.extent.x > minLeafExtent) {
				tempElementStorage = treeElements[currentNodeIndex];
                treeElements[currentNodeIndex].resize(0);
				NodeIndex childStartIndex = AllocateEightNodes();
                parentLinks[(childStartIndex - 1) / 8] = currentNodeIndex;
				treeNodes[currentNodeIndex].childNodes = childStartIndex;
				treeNodes[currentNodeIndex].inclusiveNumElements = 0;
				for (auto childElement : tempElementStorage) {
					const BoxCenterAndExtent childElementBounds(OctreeSemantics::GetBoundingBox(childElement));
					AddElementInternal(currentNodeIndex, nodeContext, childElementBounds, childElement, tempElementStorage);
				}
				tempElementStorage.resize(0);
				AddElementInternal(currentNodeIndex, nodeContext, elementBounds, element,tempElementStorage);
				return;
			}
			else {
				int elementIndex = treeElements[currentNodeIndex].Emplace(element);
			//	SetElementId(element, OctreeElementId2(currentNodeIndex, elementIndex));
			}

		}
		else {
			OctreeChildNodeRef childRef = nodeContext.GetContainingChild(elementBounds);
			if (childRef.IsNull()) {
				int elementIndex = treeElements[currentNodeIndex].Emplace(element);
			//	SetElementId(element, OctreeElementId2(currentNodeIndex, elementIndex));
				return;
			}
			else {
				NodeIndex childNodexIndex = treeNodes[currentNodeIndex].childNodes + childRef.index;
				OctreeNodeContext chilNodeContext = nodeContext.GetChildContext(childRef);
				AddElementInternal(childNodexIndex, chilNodeContext, elementBounds, element, tempElementStorage);
				return;
			}
		}
	}

    template<typename IteratorAllElementFunc>
    inline void FindAllElements(const IteratorAllElementFunc & Func)
    {
        for (auto& iter : treeElements) {
            for (auto& element : iter) {
                Func(element);
            }
        }
    }

    template<typename PredicateFunc,typename IterateFunc>
    inline void FindNodesWithPredicate(const PredicateFunc& predicate, const IterateFunc& func)
    {
        FindNodeWithPredicateInternal(INDEX_NONE, 0, rootNodeContext, predicate, func);
    }

    template<typename PredicateFunc,typename IterateFunc>
    void FindNodeWithPredicateInternal(NodeIndex parentNodeIndex, NodeIndex currentIndex, const OctreeNodeContext& nodeContext, const PredicateFunc& predicate, const IterateFunc& func)const
    {
        if (treeNodes[currentIndex].inclusiveNumElements > 0) {
            if (predicate(parentNodeIndex, currentIndex, nodeContext.bounds)) {
                func(parentNodeIndex, currentIndex, treeNodes[currentIndex]);
                if (!treeNodes[currentIndex].IsLeaf()) {
                    NodeIndex childStartIndex = treeNodes[currentIndex].childNodes;
                    for (int8 i = 0; i < 8; ++i) {
                        OctreeNodeContext childContext = nodeContext.GetChildContext(OctreeChildNodeRef(i));
                        FindNodeWithPredicateInternal(currentIndex, childStartIndex + i, childContext, predicate, func);
                    }
                }
            }
        }
    }
/*
    template<typename PredicateFunc,typename IterateFunc>
    void IteratorNode(PredicateFunc predicate, const IterateFunc& func)
    {
        IteratorNodeInternal(INDEX_NONE, 0, rootNodeContext, predicate, func);
    }

    template<typename PredicateFunc,typename IterateFunc>
    void IteratorNodeInternal(NodeIndex parentNodeIndex, NodeIndex currentIndex, const OctreeNodeContext& nodeContext, const PredicateFunc& pridicate, const IterateFunc& func)
    {

    }
    */


/*
	void CollapseNodeInternal(NodeIndex currentIndex, ElementArrayType& collapseNodeElements)
	{
		CollapseElements.Append(MoveTemp(treeElements[currentIndex]));
		treeElements[currentIndex].Reset();
		if (!treeElements[currentIndex].IsLeaf())
		{
			NodeIndex childStartIndex = treeNodes[currentIndex].childNodes;
			for (int i = 0; i < 8; ++i) {
				CollapseNodeInternal(childStartIndex + i, collapseNodeElements);
			}
			FreeEightNodes(childStartIndex);
		}
	}

	template<typename  PredicateFunc, typename IterateFunc>
	void FindElementsWithPredicateInternal(NodeIndex parentIndex, NodeIndex currentNodeIndex, const OctreeNodeContext& nodeContext, const PredicateFunc& predicate, const IterateFunc& func)const
	{
		if (treeNodes[currentNodeIndex].inclusiveNumElements > 0) {
			if (predicate(parentIndex, currentNodeIndex, nodeContext.bounds)) {
				Func(parentIndex, currentNodeIndex, nodeContext);
				if (!treeNodes[currentNodeIndex].IsLeaf()) {
					NodeIndex childStartIndex = treeNodes[currentNodeIndex];
					for (int i = 0; i < 8; i++) {
						FindElementsWithPredicateInternal(currentNodeIndex, childStartIndex + i, nodeContext.GetChildContext(OctreeChildNodeRef(i)), predicate, func);
					}
				}
			}
		}
	}

	template<typename IterateFunc>
	void FindElementWithBoundsTestInternal(NodeIndex currentNodeInex, const OctreeNodeContext& nodeContext, const BoxCenterAndExtent& boxBounds, const IterateFunc& func)const
	{
		if (treeNodes[currentNodeInex].inclusiveNumElements > 0) {
			for (auto element : treeElements[currentNodeInex]) {
				if (Intersect(OctreeSemantics::GetBoundingBox(element).boxBounds)) {
				Func(Element);
			}
		}
	}
	if (!treeNodes[currentNodeInex].IsLeaf()) {
		const OctreeChildNodeSubset intersectingChildSubset = nodeContext.GetIntersectingChildren(BoxBounds);
		for (int i = 0; i < 8; ++i) {
			if (IntersctionChildSet.Contains(OctreeChildNodeRef(i))) {
				FindElementsWithBoundsTestInternal(childStartIndex + 9, nodeContext.GetChildContext(OctreeChildNodeRef(i)), boxBounds, Func);
			}
		}
	}
}

template<typename IterateFunc>
void FindFirstElementWithBoundsTestInternal(NodeIndex currentIndex, const OctreeNodeContext& nodeContext, const BoxCenterAndExtent& boxBounds, const IterateFunc& func, bool& contineTraversal)
{
	if (continueTraversal && treeNodes[currentIndex].inclusiveNumElements > 0) {
		for (int index = 0; continueTraversal && index < treeElements[currentIndex].Num(); index++) {
			ElementType element = treeElements[currentIndex][index];
			if (intersect(OCtreeSemantics::GetBoundingBox(element), boxBounds)) {
				continueTraversal &= func(element);
			}
		}
		if (!treeNodes[currentIndex].IsLeaf()) {
			const OctreeNodeSubSet intersectingChildSubset = nodeContext.GetIntersectingChildren(boxBounds);
			NodeIndex childStartIndex;
			if (intersectingChildSubset.Contains(OctreeChildNodeRef(i))) {
				FindFirstElementWithBoundsTestInternal(childStartIndex + i, nodeContext.GetChildContext(OctreeChildNodeRef(i)), boxBounds, func, continueTraversal);
			}
		}
	}
}

template<typename IterateFunc>
void FindNearByElementsInternal(NodeIndex currentNodeIndex, const OctreeNodeContext& nodeContext, const BoxCenterAndExtent& boxBounds, const IterateFunc& func)const
{
	if (treeNodes[currentNodeIndex].inclusiveNumElements > 0) {
		for (int index = 0; index < 8; ++index) {
			func(treeElements[currentNodeIndex][Index]);
		}
		if (!treeNodes[currentNodeIndex].IsLeaf()) {
			OctreeChildNodeRef childRef = nodeContext.GetContainngChild(boxBounds);
			if (!childRef.IsNull()) {
				NodeIndex childStartIndex = treeNodes[currentNodeIndex].childNodes;
				if (treeNodes[childStartIndex + childRef.index].inclusiveNumElement > 0) {
					FindNearByElementsInternal(childStartIndex + childRef.index, NodeContext.GetChildContext(childRef), boxBounds, func);
				}
				else {
					for (int i = 0; i < 8; ++i) {
						FindNearByElementsInternal(childStartIndex + i, nodeContext.GetChildContext(OctreeChildNodeRef(i)), boxBounds, func);
					}
				}
			}
		}
	}
}
public:
    int GetNumNode()const
    {
        return treeNodes.Num();
    }

    template<typename IterateAllElementFunc>
    inline void FindAllElements(const IterateAllElementFunc& func)const
    {
    	for (const ElementArrayType& elements : treeElements)
    	{
    		for (auto iter : elements) {
    			func(iter);
    		}
    	}
    }
    template<typename PredicateFunc, typename IterateFunc>
    inline void FineElementByPredicate(const PredicateFunc& predicate, const IterateFunc& func)const
    {
    	FindElementsWithPredicateInternal(INDEX_NONE, 0, RootNodeContext, predicate, [&func, this](NodeIndex nodexIndex, const  BoxCenterAndExtent&)
    		{
    			for (typename TCallTraits<ElementType>::ConstReference element : treeElements[nodexIndex]) {
    				func(NodeIndex, Element);
    			}
    		});
    }

    template<typename IterateBounsTest>
    inline void FindFirstElementsWithBounsTest(const BoxCenterAndExtent& boxBounds, const IterateBounsTest& func)const
    {
    	bool ContinueTraversal = true;
    	FindFirstElementWithBoundsItestInternal(0, rootNodeContext, boxBounds, func, ContinueTraversal);
    }
    */

   

private:
    //struct COctreeSemanticsV2
    //{
    //    template<typename Semantics>
    //    auto Requires(typename Semantics::FOctree& OctreeInstance, const ElementType& element, OctreeElementId2 id)
    //    {
    //        Semantics::SetElementId(element, id)
    //    }
    //};
    //
    //template<typename Semantics>
    //std::enable_if<true, Semantics>::value::Type SetOctreeSemanticsElementId(const ElementType& elment, OctreeElementId2 id)
    //{
    //    Semantics::SetElementId(elment, id);
    //}

    Array<NodeIndex>freeList;
    int minLeafExtent;
    OctreeNodeContext rootNodeContext;
    Array<Node>treeNodes;
    Array<NodeIndex>parentLinks;
    Array<ElementArrayType>treeElements;
    uint32 IncludesiveNumElements = 0;
};
