#pragma once
#include <Array.hpp>
#include "RHIFeatureLevel.h"
#include "MeshElementCollector.h"
#include "SceneView.h"
#include <map>
#include "ShowFlags.h"
#include "SceneTextures.h"
#include "MeshDrawCommand.h"
#include "VirtualShadowMapArray.h"
#include "ShadowSceneRenderer.h"
#include "RHIShaderPlatform.h"
#include "MultiGPU.h"
#include "HitProxies.h"
/*每帧都会被创建，封装帧间临时数据，下派生的DeferredShadingSceneRenderer(延迟着色场景渲染器）和MobileSceneRenderer（移动端场景渲染器），分别代表PC和移动端的默认渲染器
 *所属线程：渲染
 */

class RHICommandListImmediate;
class RDGBuilder;
class SceneViewFamily;
class HitProxyConsumer;
class Scene;
class ViewFamilyInfo:public SceneViewFamily
{
public:
	ViewFamilyInfo(const SceneViewFamily& viewFamily);
	virtual ~ViewFamilyInfo();
	SceneTexturesConfig sceneTextureConfig;
	inline SceneTextures& GetSceneTextures()
	{
		return sceneTextures;
	}

	inline const SceneTextures& GetSceneTextures()const
	{
		return sceneTextures;
	}

	inline SceneTextures& GetSceneTexturesChecked()const
	{
		return bIsSceneTexturesInitialized ? &sceneTextures : nullptr;
	}

	inline SceneTextures& GetSceneTexturesChecked()
	{
		return bIsSceneTexturesInitialized ? &sceneTextures : nullptr;
	}

private:
	friend struct MinimalSceenTextures;
	friend struct SceneTextures;
	SceneTextures sceneTextures;
	bool bIsSceneTexturesInitialized;
};
class ViewInfo :public SceneView
{

};

class VisibleLightInfo
{

};

class SortedShadowMaps
{

};


class SceneRenderer
{
public:
//	SceneRenderingBulkObjectAllocator allocator;
	Scene* scene;
	ViewFamilyInfo viewFamily;
	Array<ViewInfo>views;
	Array<const SceneView*>allFamilyViews;
	MeshElementCollector meshCollector;
	MeshElementCollector rayTacingCollector;
	Array<VisibleLightInfo>visibleLightInfos;
	Array<ParallelMeshDrawCommandPass*>dispatchedShadwDepthPasses;
	SortedShadowMaps soredShadowsForShadowDepthPass;
	VirtualShadowMapArray vistualShadowMapArray;
	std::unique_ptr<ShadowSceneRenderer>shadowSceneRenderer;
	bool hasRequestedToggleFreeze;
	bool usedPrecomputedVisiblity;
	Array<std::string>useWholeScenePointLightNames;
	ERHIFeatureLevel::Type featureLevel;
	EShaderPlatform shaderPlatform;
	bool GPUMasksComputed;
	RHIGPUMask rendererTargetGPUMask;
	bool isFirstSceneRenderer;
	bool isLastSceneRenderer;
#if RHI_RAYTRACING
	bool anyRayTracingPassEnabled = false;
#endif
public:
	SceneRenderer(const SceneViewFamily* viewFamily, HitProxyConsumer* hitProxyConsumer);
	virtual ~SceneRenderer();
	CORE_API void RenderThreadBegin(RHICommandListImmediate& RHICmdList);
	CORE_API void RenderThreadEnd();

	static void RenderThreadBegin(RHICommandListImmediate& RHICmdList, const Array<SceneRenderer*>sceneRenderers);
	static void RenderThreadEnd(RHICommandListImmediate &RHICmdList,const Array<SceneRenderer*>sceneRenderers);
	static void ViewExtensionPreRender_RenderThread(RDGBuilder& graphBuilder, SceneRenderer* sceneRender);
	virtual void Render(RDGBuilder& builder);
	virtual void RenderHitProxies(RDGBuilder& builder);
	virtual void FlushCrossGPUFences(RDGBuilder& graphBuilder);
private:
};

