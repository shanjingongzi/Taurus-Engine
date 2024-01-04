#include "RHICommandList.h"
#include "RenderGraphDefinitins.h"
#include "RefCounting.h"

class RDGBuilder
{
	RDGBuilder(RHICommandListImmediate& RHICmdList, RDGEventName Name = {}, ERDGBuilderFlags flags=ERDGBuilderFlags::None);
	RDGBuilder(const RDGBuilder&) = delete;
	~RDGBuilder();

	RDGTexture* FindExternalTexture(RHITexture* text)const;
	RDGTexture* FindExternalTexture(IPooledRenderTarget* externalPooledTexture)const;

	RDGBuffer* FindExternalBuffer(RHIBuffer* buffer)const;
	RDGBuffer* FindExternalBuffer(IRDGPooledBuffer* externalPooledBuffer)const;

	RDGTextureRef RegisterExternalTexture(const TRefCountPtr<IPooledRenderTarget>& externalPooledTexture, ERDGTextureFlags flag = ERDGTextureFlag::None);



};

