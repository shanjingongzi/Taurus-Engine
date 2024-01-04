#pragma once

class RenderTarget
{
public:
    RenderTarget(){}
    virtual ~RenderTarget(){}

    virtual const TextureRHIRef &GetRenderTargetTexture()const;

    virtual RDTextureRef GetRenderTargetTexture(FRDGBuilder &graphBuilder)const;
};