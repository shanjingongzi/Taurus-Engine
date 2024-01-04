#pragma once
#include "Core.h"
#include <vector>
class ICollisionDetection;
class IGraphics;
class SceneComponent;
class AActor;

/*
 * 演员分为行为和展示
 */

class Actor
{
	public:
		Actor();
		~Actor();
	private:
		IGraphics *graphics;
		ICollisionDetection *cllisonDetection;
		SceneComponent* rootComponent{ nullptr };
		std::vector<AActor *>children;
};
