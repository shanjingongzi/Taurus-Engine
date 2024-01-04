#pragma once
#include <string>
#include "RHIDefinitions.h"
class DynamicRHI
{
public:
    virtual ~DynamicRHI(){}
    virtual void Init()=0;
    virtual void PosInit()=0;
    virtual void ShutDown()=0;
    virtual const std::string &Getname()const;
    virtual ERHIInterfaceType GetInterfaceType() {return ERHIInterfaceType::Hidden;}
    virtual DynamicRHI*GetNonValidationRHI(){return this;}
    void InitPixelformatInfo();
    virtual SamplerStateRef RHICreateSamplerState(const RHISampleStateInitializerRHI&);
    virtual RasterizerStateRHIRef RHICreateRasterizerState(const RasterizerStateInitializerRHI&);
    virtual DepthStencilStateRef RHICreateDepthStencilState(const DepthStencilStateInitializerRHI&);
    virtual BlendStateRHIRef RHICreateBlendState(const BlendStateInitializerRHI *);
    virtual VertexDeclarationRef RHICreateVertexDeclaration(const VertexDeclarationInitializerRHI&); 
private:

};
