#pragma once
#include <Platform.h>
#include "RHIDefinitins.h"
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
        return size==0 &&stride= =0 &&usage==BUF_NullResource;
    }
};

class RHIBuffer{
public:
private:
    RHIBufferDesc desc;
};