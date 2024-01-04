#pragma once
#include "ActorComponent.h"
#include "SceneComponent.h"
#include <vector>
#include <set>
class Actor
{
public:
    Actor();
    ~Actor();
private:
    std::set<ActorComponent>ownedComponents;
    SceneComponent*rootComponent;
    std::vector<ActorComponent*>instanceComponents;
    
};
