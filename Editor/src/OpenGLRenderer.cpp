#include "OpenGLRenderer.h"
#include "qopenglframebufferobject.h"
#include <QOpenGLContext>
#include "OpenGLRenderImp.h"

QOpenGLContext*OpenGLRenderer::context;
void* GetGraphicsApiAddress(const char *name)
{
    return (void*) QOpenGLContext::currentContext()->getProcAddress(name);
}



OpenGLRenderer::OpenGLRenderer(NavigationScene* scene, Camera* camera) :scene{ scene },camera { camera }
{
}

OpenGLRenderer::~OpenGLRenderer()
{
}
void OpenGLRenderer::render()
{
   renderImp->Render(scene,camera);
   update();
}

QOpenGLFramebufferObject* OpenGLRenderer::createFramebufferObject(const QSize& size)
{
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(8);
    return new QOpenGLFramebufferObject(size, format);
}

void OpenGLRenderer::InitGraphicsApi()
{
    OpenGLRenderImp::InitializedImp((void*)GetGraphicsApiAddress);
}
