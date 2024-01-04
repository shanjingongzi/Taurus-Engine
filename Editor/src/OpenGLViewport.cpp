#include "OpenGLViewport.h"
#include "OpenGLRenderer.h"
#include <CameraComponent.h>
#include <NavigationScene.h>
#include <QQuickWindow>
#include <Cube.h>
OpenGLViewport::OpenGLViewport(QQuickItem* parent) :QQuickFramebufferObject(parent), camera(new Camera({0.0f,0.0f,10.0}))
{
	connect(this, &OpenGLViewport::widthChanged, [this]() {
		camera->setWidth(width());
		});
	connect(this, &OpenGLViewport::heightChanged, [this]() {
		camera->setHeight(height());
		});
	this->setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton|Qt::MiddleButton);
}

NavigationScene* OpenGLViewport::LoadScene(int count)const
{
	auto scene = new NavigationScene();
	srand((int)time(0));
	for (int i = 0; i < count; ++i) {
		int rx = rand(), ry = rand(), rz = rand();
		int x = 5 * sin(rx);
		int y = 5 * cos(ry);
		int z = 5 * sin(rz);
		int xextend = 1;
		int yextend = 1;
		int zextend = 1;
		BoxSphereBounds bounds(Vector(x, y, z), Vector(xextend, yextend, zextend), 1);
		scene->tree()->AddElement(NavigationOctreeElement(new Cube(), bounds));
	}
	return scene;
}
OpenGLViewport::~OpenGLViewport()
{

}

QQuickFramebufferObject::Renderer* OpenGLViewport::createRenderer()const
{
	return new OpenGLRenderer(scene, camera);
}

void OpenGLViewport::wheelEvent(QWheelEvent* event)
{
	auto delta = event->angleDelta();
	camera->ProcessMouseScroll(delta.y()*0.01);
}
void OpenGLViewport::mousePressEvent(QMouseEvent* event)
{
	prePoint = event->pos();
	enableMove = false;
	if (event->button() == Qt::LeftButton) {
		auto devicePixelRadio = window()->devicePixelRatio();
		auto ray=camera->CreateRay(prePoint.x()*devicePixelRadio,prePoint.y()*devicePixelRadio, width()* devicePixelRadio, height()* devicePixelRadio);
		scene->IntersectRayAABB(ray);
		auto selections = scene->Selected();
		for (auto iter:selections) {
			auto cube = dynamic_cast<Cube*>(iter.data->sourceObject);
			cube->lineColor = glm::vec4(1.0, 0.0, 1.0, 1.0);
		}
	}
	else if (event->button() == Qt::RightButton) {
		enableMove = true;
	}
	else {
		Super::mousePressEvent(event);
	}
	event->setAccepted(true);
	setFocus(true);
}

void OpenGLViewport::mouseReleaseEvent(QMouseEvent* event)
{
	Super::mouseReleaseEvent(event);
}

void OpenGLViewport::mouseMoveEvent(QMouseEvent* event)
{
	auto button = event->button();
	if (enableMove) {
		QPointF offset = prePoint-event->pos();
		camera->ProcessMouseMovement(offset.x(), offset.y());
		prePoint = event->pos();
	}
	else {
		Super::mouseMoveEvent(event);
	}
}
void OpenGLViewport::keyPressEvent(QKeyEvent* event)
{
	float delta = 0.1f;
	switch (event->key()) {
	case Qt::Key_W:
		camera->ProcessKeyboard(Camera::FORWARD, delta);
		break;
	case Qt::Key_S:
		camera->ProcessKeyboard(Camera::BACKWARD, delta);
		break;
	case Qt::Key_A:
		camera->ProcessKeyboard(Camera::LEFT, delta);
		break;
	case Qt::Key_D:
		camera->ProcessKeyboard(Camera::RIGHT, delta);
		break;
	default:
		break;
	}
}

void OpenGLViewport::SetScene(NavigationScene* scene)
{
	this->scene = scene;
}