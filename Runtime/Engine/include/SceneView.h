#pragma once
#include "Platform.h"
#include <memory>
#include <Vector.hpp>
#include "ShowFlags.h"
/*描述了Scene内单个视图，Scene允许有多个View,换言之，一个场景可被多个view绘制，或者多个view同时被绘制，每一帧都会新建一个view实例
 *所属线程：渲染
 */

class RenderTarget;
class SceneInterface;

class SceneView
{
public:
	const SceneViewFamily* family;
	//SceneViewStateInterface* state;
	//std::unique_ptr<ViewUniformShaderParameters>viewUniformBuffer;
private:
	//const ConvexVolume* dynamicMeshElementsShadowCullFrustum;
	Vector preshadowTranslation;
public:
	//SceneViewInitOptions sceneViewInitOptionis;
	//const Actor* viewActor;
	int32 playerIndex;
	//ViewElementDrawer* drawer;
private:
};

class SceneViewFamily
{
public:
	struct ConstructionValues
	{
		ConstructionValues(const RenderTarget* renderTarget, SceneInterface* inScene, const EngineShowFlags& engineShowFlags);
		const RenderTarget* renderTarget;
		SceneInterface* scene;
		EngineShowFlags engineShowFlags;
		int32 viewModeParam;
	};
	bool bResolveScene;
	EngineShowFlags engineShowFlags;
};
