#pragma once
#include "RenderResource.h"
#include "Noncopyable.h"
#include "Array.hpp"

enum class EMaterialParameterType :uint8;

struct UniformExpressionCache
{
	~UniformExpressionCache();
	void ResetAllocatedVTs();

	UniformBufferRHIRef uniformBuffer;
	Array<class IAllocatedVirtualTexture*>allocatedVTs;
	Array<class IAllocatedVirtualTexture*>ownedAllocatedVTs;
	Array<Guid>ParameterCollections;
	const class MaterialShaderMap* cachedUniformExpressionShaderMap = nullptr;
};

struct UniformExpressionCacheContainer
{
	inline UniformExpressionCache& operator[](int index)
	{
		return Elements[index];
	}

private:
	UniformExpressionCache Elements;
};

class UniformExpressionCacheAsyncUpdateScope
{
public:
	UniformExpressionCacheAsyncUpdateScope();
	~UniformExpressionCacheAsyncUpdateScope();
	static void WaitForTask();
};

class MaterialRenderProxy :public RenderResource, public NonCopyable 
{
public:
	mutable UniformExpressionCacheContainer uniformExpressionCache;
	mutable ImmutableSamplerState immutableSamplerState;
	MaterialRenderProxy(std::string materialName);
	virtual ~MaterialRenderProxy();
	void EvaluateUniformExpressions(UniformExpressionCache& outUniformExpressionCache, const MaterialRenderContext& context, class RHIComputeCommandList*)const;
	void EvaluateUniformExpressions(UniformExpressionCache& outUniformExpressionCache, const MaterialRenderContext& context, UniformExpressionCacheAsyncUpdater* updater = nullptr)const;
	void CacheUniformExpressions(bool recreateUniformBuffer);
	void CancelCacheUniformExpressions();
	void CacheUniformExpressions_GameThread(bool recreateUnformBuffer);
	void InvaliddateUniformExpressionCache(bool recreateUniformBuffer);
	void updateUniformExpressionCacheIfNeeded(ERHIFeatureLevel::Type feature)const;
	void const Material* GetMaterialNoFallback(ERHIFeatureLevel::Type feature)const;
	void const MaterialRenderProxy* GetFallback(EHIFeatureLevel::Type feature)const;
	virtual MaterialInterface* GetMaterialInterface()const {
		return nullptr;
	}

	bool GetVectorValue(const HashedMaterialParameterInfo& parameterInfo, LinearColor* outValue, const MaterialRenderProxyContext& context)const;
	bool GetScalarValue();
	bool GetTexTureValue();
	bool GetTextureValue();
	bool GetTextureValue();
	virtual bool GetParameterValue();
	bool IsDeleted()const;
	void MarkForGarbageCollection()
	{
		markedForGarbageCollection = 1;
	}

	bool IsMarkedForGarbageCollection()const
	{

	}

	virtual void InitDynamicRHI()override;
	virtual void ReleaseDynamicRHI()override;
	virtual void ReleaseResource()override;

	void SetSubsurfaceProfileRT(const SubsurfaceProfile* ptr) { subsurfaceProfileRT = ptr; }

	const SubsurfaceProfileRT()const { return subsurfaceProfileRT; }

	static void UpdateDeferredCachedUniformExpression();

	static bool HasDeferredUniformExpressionCacheRequests();

	int32 GetExpressionCacheSerialNumber()const { return uniformExpressionCacheSerialNumber; }

	const std::string& GetMerialName()const { return maiterlName; }

private:
	IAllocatedVirtualTexture* GetPreallocatedVTStack(const MaterialRenderContext& context, const UnformExpressionSet& uniformExpressionSet, const MaterialVirtualTextureStack& VTStack)const;
	IAllocatedVirtualTexture* AllocateVTStack(const MaterialRenderContext& context, const UniformExpressionSet& uniformExpressionSet, const MaterialVirtualTextureStatck& VTStack);

	virtual void StartCackeUniformExpressions()const {}
	virtual void FinishCacheUniformExpressions()const {}
	const SubsurfaceProfile* subsurfaceProfielRT;
	std::string materialName;
	mutable int32 uniformExpressionCacheSerialNumber = 0;
	mutable int8 markedForGarbageCollection : 1;
	mutable int8 DeletedFlag : 1;
	mutable int8 releaseResourceFlag : 1;
	mutable int8 hasVirtualTextureCallback : 1;
	static std::set<MaterialRenderProxy*>deferredUniformExpressionCacheRequests;
};

class ColoredMaterialRenderProxy :public MaterialRenderProxy
{
	const MaterialRenderProxy* const parent;
	const LinearColor color;
};

class ColoredTexturedMaterialRenderProxy :public ColoredMaterialRenderProxy
{

};

class OverrideSelectionColorMaterialRenderProxy :public MaterialRenderProxy
{

};

class LightingDensityMaterialRenderProxy :public ColoredMaterialRenderProxy
{

};