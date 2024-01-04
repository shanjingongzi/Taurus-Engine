#ifndef OCTREE_PUBLIC_H
#define OCTREE_PUBLIC_H

#include "Core.h"
#include "Platform.h"
#include "CoreMiscDefines.h"
class OctreeElementId2
{
    public:
        template<typename ,typename>
        friend class Octree;

        OctreeElementId2() :nodeIndex(INDEX_NONE),elementIndex(INDEX_NONE){}
        bool IsValidId()const{
            return nodeIndex!=INDEX_NONE; 
        }
        unsigned int GetNodeIndex()const{
            return nodeIndex;
        }
    private:
        int32 nodeIndex;
        int32 elementIndex;
        OctreeElementId2(unsigned int inNodeIndex,unsigned int inElementIndex):nodeIndex(inNodeIndex),elementIndex(inElementIndex){}
        operator int()const
        {
            return elementIndex;
        }
};

class OctreeElementId
{
    public:
        template<typename ,typename>
        friend class Octree_DEPRECATED;
        OctreeElementId():node(nullptr),elementIndex(INDEX_NONE){}
        bool IsValidId()const 
        {
            return node!=nullptr;
        }

    private:
        const void *node;
        int elementIndex;
        OctreeElementId(const void *node,int inElementIndex):node(node),elementIndex(inElementIndex){}
        operator int()const
        {
            return elementIndex;
        }
};
#endif