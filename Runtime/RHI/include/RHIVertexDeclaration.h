#pragma once
#include "RHIResource.h"

class RHIVertexDeclartion:public RHIResource
{
public:
    RHIVertexDeclaration():RHIResource(RRT_VertexDeclaration){}
    virtual bool GetInitializer(VertexDeclarationElementList &init){return false;}
    virtual uin32 GetPrecachePSOHash()const{return 0;}
};