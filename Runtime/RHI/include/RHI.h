#pragma once
#include <Type.hpp>
#include <Platform.h>
#include "RHIDefinitions.h"

struct ViewportBounds
{
    float topLeftX;
    float topLeftY;
    float width;
    float height;
    float minDepth;
    float maxDepth;

    ViewportBounds(){}
    ViewportBounds(float tlX,float tlY,float width,float height,float minDepth,float maxMaxDepth)
        :topLeftX{tlX},topLeftY{tlY},width{width},height{height},minDepth{minDepth},maxDepth{maxDepth}
    {

    }
};

struct VRamAllocation
{
    VRamAllocation()=default;
    VRamAllocation(uint64 start,uint32 size):allocationStart{start},allocationSize(size){}
    bool IsValid(){return allocationSize>0;}
    uint64 allocationStart;
    uint64 allocationSize;
};

struct RHIResourceInfo
{
    Name name;
    ERHIResourceType type{RRT_None};
    VRamAllocation vramAllocation;
    bool isTransient{false};
    bool valid{true};
    bool resident{true};
};