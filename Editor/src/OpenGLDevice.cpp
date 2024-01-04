#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include "glShader.h"
#include "glProgram.h"
#include "OpenGLDevice.h"
#include "Cube.h"
#include "glm/gtc/type_ptr.hpp"
#include "OpenGLRenderer.h"
OpenGLDevice::OpenGLDevice():QWindow()
{
    setSurfaceType(QSurface::OpenGLSurface);
    QSurfaceFormat format;
    format.setDepthBufferSize(16);
    format.setStencilBufferSize(8);
    format.setVersion(3,3);
    setFormat(format);
    context=new QOpenGLContext();
    context->setFormat(format);
    context->create();
    offscreenSurface = new QOffscreenSurface();
    offscreenSurface->setFormat(context->format());
    offscreenSurface->create();
    if (!context->makeCurrent(offscreenSurface)) {
        return;
    } 
    OpenGLRenderer::context=context;
}

void OpenGLDevice::Initialized()
{
    context->makeCurrent(this);
    QOpenGLFunctions* f = context->functions();
    InitFramebuffer();
    program = new glProgram();
    program->AddShader(new glShader(GL_VERTEX_SHADER, Cube::execPath + std::string("\\shader\\drawImage.vs")));
    program->AddShader(new glShader(GL_FRAGMENT_SHADER, Cube::execPath + std::string("\\shader\\drawImage.fs")));
    program->Link();
    camera = new Camera({ 0.0,0.0,5.0 });
    initialized = true;
}
void OpenGLDevice::Render(uint texture)
{
    if (!context->makeCurrent(this))
        return;
   // auto factor = devicePixelRatio();
    auto f=context->functions();
    f->glViewport(0, 0, width()*devicePixelRatio(), height()*devicePixelRatio());
    f->glClearColor(1.0, 1.0, 1.0, 1.0);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program->Use();
    if (texture) {
        DeviceRender(texture);
    }

    context->swapBuffers(this);
}

void OpenGLDevice::exposeEvent(QExposeEvent*)
{
    if (isExposed()&&!initialized) {
		emit Start();
		Initialized();
    }
}

QOpenGLContext* OpenGLDevice::OpenGLContext()
{
    return context;
}

void OpenGLDevice::resizeEvent(QResizeEvent* event)
{
    emit Resize(width(), height());
  //  QWindow::resizeEvent(event);
}

bool OpenGLDevice::MakeCurrent()
{
    return context->makeCurrent(this);
}

bool OpenGLDevice::MakeOffscreenCurrent()
{
    return context->makeCurrent(offscreenSurface);
}

void OpenGLDevice::SwapBuffers()
{
    context->swapBuffers(this);
}

void OpenGLDevice::SwapOffscreenBuffers()
{
    context->swapBuffers(offscreenSurface);
}
