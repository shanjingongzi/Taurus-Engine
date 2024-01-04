#pragma once
#include <QQuickFramebufferObject>
class Camera;
class NavigationScene;
class OpenGLViewport :public QQuickFramebufferObject
{
	Q_OBJECT
private:
	using Super = QQuickFramebufferObject;
public:
	OpenGLViewport(QQuickItem* parent = nullptr);
	~OpenGLViewport();
	QQuickFramebufferObject::Renderer* createRenderer()const override;
	NavigationScene* LoadScene(int)const;
	void SetScene(NavigationScene* scene);
	void wheelEvent(QWheelEvent* event)override;
	void mousePressEvent(QMouseEvent* event)override;
	void mouseReleaseEvent(QMouseEvent* event)override;
	void mouseMoveEvent(QMouseEvent* event)override;
	void keyPressEvent(QKeyEvent* event)override;
protected:
private:
	QPoint prePoint;
	Camera* camera;
	NavigationScene* scene;
	bool enableMove;
};
