#include "SceneRendering.h"
//
//static void RenderViewFamilies_RenderThread(RHICommandListImmediate& RHICmdList, const Array<SceneRenderer*>& sceneRenderers)
//{
//	Scene* const scene = sceneRenderers[0]->scene;
//	SceneRenderer::RenderThreadBegin(RHICmdList, sceneRenderers);
//	bool bAnyShowHitProxies = false;
//#if WITH_DEBUG_VIEW_MOdES
//	bool bUpdatedGPUSkinCacheVisualization = false;
//#endif
//	FDeferredUpdateResource::UpdateResources(RHICmdList);
//	for (SceneRenderer* sceneRenderer : sceneRenderers){
//		const ERHIFeatureLevel::Type featureLevel = sceneRenderer->featureLevel;
//		SceneViewFamily viewFamily= sceneRenderer->viewFamily;
//		RDGBuilder graphBuilder(RHICmdList, EDG_EVENT_NAME("SceneRenderer_%s(ViewFamily=%s)", viewFamily.engineShowFlags.hitProxies ? TEXT("RenderHitProxies") : TEXT("Render"),
//			viewFamily.bResolveScene ? TEXT("Primary") : TEXT("Auxiliary")),
//			SceneRenderer::GetRDGParaleExecuteFlags(featureLevel)
//		);
//		SceneRenderer::ViewExtensionPreRender_RenderThread(GrapBuilder, sceneRenderer);
////TODO WITH_DEBUG_VIEW_MODES
//#if WITH_MGPU
//		if (viewFamily.forceCopyCrossGPU) {
//			graphBuilder.EnableForceCopyCrossGPU();
//		}
//#endif
//		if (viewFamily.engineShowFlags.HitProxies) {
//			sceneRenderer->RenderHitProxies(graphBuilder);
//			bAnyShowHitProxies = true;
//		}
//		else {
//			sceneRenderer->Render(graphBuilder);
//		}
//		sceneRenderer->FlushCrossGPUFences(graphBuilder);
//		GraphBuilder->Execute();
//	}
//	SceneRenderer::RenderThreadEnd(RHICmdList, sceneRenderers);
//}
//
//void SceneRenderer::ViewExtensionPreRender_RenderThread(RDGBuilder& graphBuilder, SceneRenderer* sceneRenderer)
//{
//
//}
//
//void SceneRenderer::FlushCrossGPUFences(RDGBuilder& graphBuilder)
//{
//#if WITH_MGPU
//	//TODO 
//#endif
//}
//
//void SceneRenderer::RenderThreadBegin(RHICommandListImmediate& RHICmdList)
//{
//	Array<SceneRenderer*>sceneRenderers;
//	sceneRenderers.push_back(this);
//	RenderThreadBegin(RHICmdList, sceneRenderers);
//}
//
//void SceneRenderer::RenderThreadBegin(RHICommandListImmediate& RHICmdList, const Array<SceneRenderer*>sceneRenderers)
//{
//	CleanUp(RHICmdList);
//	for (auto iter : sceneRenderers){
//		for (const ViewInfo& viewInfo : iter->views) {
//			sceneRenderers[0]->allFamilyViews.push_back(&viewInfo);
//		}
//	}
//	for (int32 rendererIndex = 1; rendererIndex < sceneRenderers.Num(); rendererIndex++) {
//		sceneRenderers[rendererIndex]->allFamilyViews = sceneRenderers[0]->allFamilyViews;
//	}
//	Scene* scene = sceneRenderers[0]->scene;
//	class FXSystemInterface* FXSystem = scene ? scene->FXSystem : nullptr;
//	if (FXSystem && FXSystemn->IsPendingKill()) {
//		FXSystem = nullptr;
//	}
//	for (auto iter : sceneRenderers){
//		iter->FXSystem = FXSystem;
//	}
//}
//
//
//void SceneRenderer::RenderThreadEnd(RHICommandListImmediate& RHICmdList, const Array<SceneRenderer*>sceneRenderers)
//{
//
//}
