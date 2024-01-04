#include "DeferredShadingSceneRenderer.h"
#include "Scene.h"
#define WITH_EDITOR 1
void DeferredShadingSceneRenderer::RenderHitProxies(RDGBuilder& graphBuilder)
{
	const bool nanitedEnabled = UseNanite(shaderPlatfrom);
	scene->UpdateAllPrimitiveSceneInfos(graphBuilder);

	PrepareViewRectsForRendering(graphBuilder.RHICmdList);

#if WITH_EDITOR
	InitializeSceneTextureConfig(viewFamily.GetSceneTexturesChecked, viewFamily);
	SceneTexturesConfig& sceneTexturesConfig = GetActiveSceneTexturesConfig();
	SceneTexturesConfig::Set(sceneTexturesConfig);

	RDGTextureRef hitProxyTexture = nullptr;
	RDGTextureRef hitProxyDepthTexture = nullptr;

	//初始化命中目标代理color texture 和depth texture
	InitHitProxyRender(graphBuilder, this, hitProxyTexture, hitProxyDepthTexture);

	const IntPoinnt hitProxyTextureSize = hitProxyDepthTexture->desc.extent;

	InstanceCullingManager& instanceCullingManager = *graphBuilder.AllocObject<InstanceCullingManager>(scenej->GPUScene.IsEnable(), graphBuilder);

	//Find this visible primitives

	LumenSceneFrameTemporaries lumenFrameTemporaries;
	ILCUpdatePrimTaskData ILCTaskData;
	RDGExternalAceessQueue externalAccessQueue;
	BeginInitViews(graphBuilder, sceneTextureConfig, FExclusiveDepthStenic::DepthWrite_StencilWrite, ILCTaskData, InstanceCullingManager);

	extern std::set <class IPersitentiveViewUniformBufferExtension*>persistentViewUniformBufferExtensions;
	for (class IPersistentViewUniformBufferExtension* extension : persistentViewUniformBufferExtensions) {
		extension->BeginFrame();
		for (int32 viewIndex = 0; viewindex < views.Num(), viewIndex++) {
			extension->PrepareView(&views[viewIndex]);
		}
	}


	ShaderPrint::BeginViews(graphBuilder, views);

	scene->GPUScene.Update(graphBuilder, *scene, externalAccessQueue);

	for (int32 viewIndex = 0; viewIndex < views.Num(); ++viewIndex) {
		scene->GPUScene.UploadDynamicPrimitiveShaderDataForView(graphBuilder, *scene, views[viewIndex], externalAccessQueue);
	}

	EndInitViews(graphBuilder, LumenFrameTemporaries, ILCTaskData, instanceCullingManager, externalAccessQueue);
	
	externalAccessQueue.Submit(graphBuilder);

	instanceCullingManager.FlushRegisteredViews(graphBuilder);

	if (nanitedEnabled) {

	}

	GEngine->GetPreRenderDelegateEx().Broadcast(graphBuilder);

#endif
}
bool DeferredShadingSceneRenderer::IsNaniteEnable()const
{
	return false;
}

void DeferredShadingSceneRenderer::Render(RDGBuilder& graphBuilder)
{
	const bool bNaniteEnable = IsNaniteEnable();

	ShaderPrint::BeginViews(graphBuilder,views);

	for (int32 viewIndex = 0; viewIndex < views.Num(); viewIndex++) {
		ViewInfo& view = views[viewIndex];
		ShadingEnergyConservation::Init(graphBuilder, view);
	}

	{
		EUpdateAllPrimitiveSceneInfosAsyncOps asyncOps = EUpdateAllPrimitiveSceneInfosAsyncOps::None;
		if (GAsyncCreateLightPrimitiveInteractions > 0) {
			asyncOps |= EUpdateAllPrimitiveSceneInfosAsyncOps::CreateLightPrimitiveInteractions;
		}

		if (GAsyncCacheMeshDrawCommands > 0) {
			asyncOps |= EUpdateAllPrimitiveSceneInfosAsyncOps::CacheMeshDrawCommands;
		}

		scene->UpdateAllPrimitiveSceneInfos(graphBuilder, asyncOps);
	}


	//TODO RHI_RAYTRACING

	GPUSceneScopeBegineEndHelper GPUSceneScopeBgineEndHelper(scene->GPUScene, GPUSceneDynamicContext, scene);

	bool updateNaniteStreaming = false;
	bool bVisualizeNanite = false;
	//TODO naniteEnable

	PrepareViewRectsForRendering(graphBuilder.RHICmdList);

	ComputeGPUMasks(&graphBuilder.RHICmdList);

	//遮挡剔除
	WaitOcclusionTest(graphBuilder.RHICmdList);

	if (!viewFamily.engineShowFlags.Rendering) {
		return;
	}

	{
		GSystemTextures.InitializeTexutres(graphBuilder.RHICmdList, featureLevel);
		UpdateSubsurfaceProfileTexture(graphBuilder, shaderPlatform);
		RectLightAtlas::UpdateAtlasTexutre(graphBuilder, featureLevel);
		IESAltas::UpdateAtlasTexture(graphBuilder, featureLevel);
	}

	InitializedSceneTextureConfig(graphBuilder, featureLevel);
	
	SceneTextureConfig& sceneTextureConfig = GetActiveSceneTextureConfig();
	SceneTexutreConfig::Set(sceneTextureConfig);

	const RDGSystemTextures& systemTextures = RDGSystemTexture::create(graphBuilder);

	const bool hasRayTracedOverlay = HasRayTracedOverlay(viewFamily);
	const bool allowStaticLighting = !hasRayTracedOverlay && IsStaticLightingAllowd();
	const bool useVirtualTexturing = UseVirtualTexturing(featureLevel);

	if (useVirtualTexturing) {
		VirtualTextureFeedbackBegin(graphBuilder, views, sceneTexturesConfig.extent);
	}

	virtualShadowMapArray.Initialize(graphBuilder, scene->GetVirtualShadowMapCache(views[0]), UseVirtualShadowMaps(shaderPlatform, featureLevel), views[0].bIsSceneCapture);

	const bool isEarlyDepthComplete = (depthPass.earlyZPassMode == DDM_AlloOpaque || depthPass.earlyZPassMode == DDM_AllOpaqueNoVelocity);

	const bool allowReadOnlyDepthBasePass = isEarlyDepthComplete
		&& !viewFamily.engineShowFlags.shaderComplexity
		&& !viewFamily.UseDebugViewPS()
		&& !viewFamily.engineShowFlags.wireframe
		&& !viewFamily.engineShowFlags.LightMapDensity;

	const FExcusiveDepthStencil::Type basePassDepthStencilAccess = allowReadOnlyDepthBasePass ?
		ExcusiveDepthStencil::DepthRead_StencilWrite : ExcusiveDepthStencil::DepthWrite_StencilWrite;

	ILCUpdatePrimTaskData ILCTaskData;

	if (GDynamicRHI->RHIIncludeOptionalFlushes()) {
		graphBuilder.RHICmdList.ImmediateFlush(EImmediateFlushType:DispatchToRHIThread);
	}

	InstanceCullingManager &Inst




}
