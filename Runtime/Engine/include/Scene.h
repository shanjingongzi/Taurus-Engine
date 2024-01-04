#pragma once
/*是world 在渲染模块的代表，只有加入到Scene的物体才会被渲染器感知到，渲染线程拥有scene的所有状态（游戏线程不可直接修改）
 */
#include <map>
#include <set>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "SceneInterface.h"
#include <Array.hpp>
class Camera;

class Scene:public SceneInterface
{
public:
    void ActiveCamera(const Camera*);
private:
    World* world;
    class FXSystemInterface* FXSystem;
    Array<SceneViewState*>viewStates;
    PersistenUniformBuffers uniforBuffers;

};
