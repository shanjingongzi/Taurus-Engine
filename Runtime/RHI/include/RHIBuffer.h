#pragma once
#include <Platform.h>
#include <Type.hpp>
#include "RHIDefinitions.h"
#include "RHIResource.h"
struct RHIBufferDesc
{
    uint32 size{};
    uint32 stride{};
    EBufferUsageFlags usage{};
    RHIBufferDesc()=default;
    RHIBufferDesc(uint32 size,uint32 stride,EBufferUsageFlags usage):size{size},stride{stride},usage{usage}{}
    static RHIBufferDesc Null(){
        return RHIBufferDesc(0,0,BUF_NullResource);
    }

    bool IsNull(){
        return size==0 &&stride==0 &&usage==BUF_NullResource;
    }
};

class RHIBuffer:public RHIViewableResource{
public:
    RHIBuffer(RHIBufferDesc const &desc);
    RHIBufferDesc const &GetDesc()const {return desc;}
    uint32 GetSize()const {return desc.size;}
    uint32 GetStride()const{return desc.stride;}
    EBufferUsageFlags GetUsage()const{return desc.usage;}
    void SetName(const Name &val){name=val;}
    virtual uint32 GetParentGPUIndex()const {return 0;}
private:
    RHIBufferDesc desc;
};