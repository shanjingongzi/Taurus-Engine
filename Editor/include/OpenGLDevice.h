#ifndef VIEWPORT_H
#define VIEWPORT_H
#include <QWindow>
#include <QOffscreenSurface>
#include <IProgram.h>
#include <CameraComponent.h>
#include <Cube.h>
class QOpenGLContext;
class OpenGLDevice:public QWindow
{
    Q_OBJECT
public:
    OpenGLDevice();
    QOpenGLContext *OpenGLContext();
    bool MakeOffscreenCurrent();
    bool MakeCurrent();
    void SwapBuffers();
    void SwapOffscreenBuffers();
    void Initialized();
    void Render(uint texture);
    void InitFramebuffer();
    void DeviceRender(unsigned int);
protected:
    void exposeEvent(QExposeEvent *)override;
    void resizeEvent(QResizeEvent*event)override;
signals:
    void Start();
    void Resize(int w, int h);
private:
    QOpenGLContext* context;
    QOffscreenSurface* offscreenSurface;
    IProgram* program;
    uint VAO;
    uint VBO;
    uint EBO;
    bool initialized{ false };
    Camera* camera;
    Cube* cube;
};

#endif // VIEWPORT_H
