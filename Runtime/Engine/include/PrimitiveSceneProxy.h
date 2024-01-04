#pragma once
#include "Platform.h"
/*图元场景代理，是PrimitiveComponent在渲染器的代表，镜像了PrimitiveComponent在渲染线程的状态
 *所属线程：渲染
*/
 
class PrimitiveSceneProxy
{
public:
	PrimitiveSceneProxy(const PrimitiveComponent *component);
	PrimitiveSceneProxy(const PrimitiveSceneProxy&) = default;

	virtual ~PrimitiveSceneProxy();

	virtual SIZE_T GetTypeHash()const = 0;
	
	bool IsShown(const SceneView& view)const;

	bool IsShadowCast(const SceneView* view)const;

	 
private:
};

