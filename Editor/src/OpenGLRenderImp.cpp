#include "glad.h"
#include "OpenGLRenderImp.h"
#include <glm/gtc/type_ptr.hpp>
#include <CameraComponent.h>
#include <NavigationScene.h>
#include <Cube.h>

void OpenGLRenderImp::InitializedImp(void *graphicsAddrss)
{
    gladLoadGLLoader((GLADloadproc)graphicsAddrss);
}

void OpenGLRenderImp::Render(NavigationScene *scene,Camera *camera)
{
    glClearColor(46/255.0, 47/255.0, 48/255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH);
    for (auto iter = scene->tree()->begin(); iter != scene->tree()->end(); ++iter) {
        auto cube = dynamic_cast<Cube*>(iter->data->sourceObject);
        auto program = cube->program();
        program->Use();
        auto origin = iter->bounds.origin;
        program->setMatrix("model", glm::value_ptr(glm::translate(glm::mat4(1.0),{origin.x,origin.y,origin.z})));
        program->setMatrix("view", glm::value_ptr(camera->GetViewMatrix()));
        program->setMatrix("projection", glm::value_ptr(camera->GetProjectionMatrix()));
        cube->Bind();
        cube->Render();
    }
}
