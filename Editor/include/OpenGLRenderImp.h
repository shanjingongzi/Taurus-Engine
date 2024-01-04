#pragma once

class NavigationScene;
class Camera;
class OpenGLRenderImp
{
public:
    static void InitializedImp(void *);
    void Render(NavigationScene *scene,Camera *camera);
};
