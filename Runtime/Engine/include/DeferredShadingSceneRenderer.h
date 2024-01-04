#pragma once
#include "SceneRendering.h"
class DeferredShadingSceneRenderer :public SceneRenderer
{
public:
	DepthPassInfo depthPass;
	LumenCardRenderer lumenCardRenderer;
	bool shouldUpdateRayTracingScene = false;
	
	virtual void RenderHitProxies(RDGBuilder& graphBuilder)override;
	virtual void Render(RDGBuilder& graphBuilder);
	virtual void FlushCrossGPUFences(RDGBuilder& graphBuilder)override;

	bool IsNaniteEnable()const;

private:
};