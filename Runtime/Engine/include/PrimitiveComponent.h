#pragma once
#include "SceneComponent.h"
#include "INavRelevantInterface.h"
#include "IAsyncCompilation.h"
#include "PrimitiveSceneProxy.h"

/*图元组件，是所有可渲染或者拥有物理魔力的五级父类，是CPU层裁剪的最小粒度单位
*所属线程：游戏
*/


class PrimitiveComponent:public SceneComponent,public INavRelevantInterface,public IInterface_AsyncCoompilation
{
public:
	virtual PrimitiveSceneProxy* CreateScenePrimitive()
	{
		return nullptr;
	}
};


