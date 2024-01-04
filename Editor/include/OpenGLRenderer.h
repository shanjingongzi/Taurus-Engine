#pragma once
#include <QQuickFramebufferObject>
#include <OpenGLRenderImp.h>
#include <QOpenGLContext>
class Camera;
class Cube;
class OpenGLRenderer :public QQuickFramebufferObject::Renderer
{
public:
	OpenGLRenderer(NavigationScene*scene,Camera *camera);
	~OpenGLRenderer();
	void render() override;
	QOpenGLFramebufferObject *createFramebufferObject(const QSize &size)override;
	static void InitGraphicsApi();
private:
	NavigationScene* scene;
	Camera* camera;
	QSize size;
    OpenGLRenderImp*renderImp;
public:
    static QOpenGLContext *context;
};
