#pragma once
#include <string>
#include "EnumAsByte.hpp"
#include "RHIFeatureLevel.h"
#include "CoreMiscDefines.h"
#include "Platform.h"
#include "RHIFwd.h"
enum class ERenderResourceState :uint8
{
	Default,
	BatchReleased,
	Deleted
};

enum class ERayTracintMode :uint8
{
	Disabled,
	Enabled,
	Dynamic
};

class RenderResource
{
public:
	static void ReleaseRHIForAllResources();
	static void InitPreRHIResources();
	static void CoalesceResourceList();
	static void ChangedFeatureLevel();
	RenderResource();
	RenderResource(ERHIFeatureLevel::Type featurelevel);
	virtual ~RenderResource();
	virtual void InitDynamicRHI() {}
	virtual void ReleaseDynamicRHI() {}
	virtual void InitRHI() {}
	virtual void ReleaseRHI() {}
	virtual void InitResource() {};
	virtual void ReleaseResource() {};
	virtual std::string GetFriendlyName()const;
	void UpdateRHI();
	inline bool IsInitialized()const { return listIndex != INDEX_NONE; }
	uint32 GetListIndex()const {
		return listIndex;
	}
protected:


private:
	TEnumAsByte<ERHIFeatureLevel::Type>featureLevel;
	int32 listIndex;
public:
	ERenderResourceState resourceState = ERenderResourceState::Default;
};

class VertexBuffer :public RenderResource
{
public:
	VertexBuffer();
	virtual ~VertexBuffer();
	virtual void ReleaseRHI()override;
	virtual std::string GetFriendlyName()const override;
	BufferRHIRef vertexBufferRHI;
};

class IndexBuffer :public RenderResource
{
public:
	IndexBuffer();
	virtual ~IndexBuffer();
	virtual void ReleaseRHI()override;
	virtual std::string GetFriendlyName()const override;
	BufferRHIRef indexBufferRHI;
};

