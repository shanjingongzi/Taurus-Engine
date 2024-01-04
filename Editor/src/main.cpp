// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"
#include "OpenGLViewport.h"
#include "Cube.h"
#include <OpenGLDevice.h>
#include <OpenGLRenderer.h>
#include <qquickwindow.h>
#include <qquickview.h>
void Initialized(char* argv[])
{
    std::string execPath = argv[0];
#ifdef _MSC_VER
    int pos = execPath.find_last_of("\\");
    execPath = execPath.substr(0, pos);
#elif __clang__
    int pos = execPath.find("/Bin");
    execPath = execPath.substr(0, pos + 4);
#endif
    Cube::execPath = execPath;
    QSurfaceFormat format;
    format.setDepthBufferSize(16);
    format.setStencilBufferSize(8);
    format.setVersion(4, 5);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);
}

void RegisterQuickItem()
{
    qmlRegisterType<OpenGLViewport>("OpenGLViewport", 6, 0, "Viewport");
}
int main(int argc, char *argv[])
{
    RegisterQuickItem();
    set_qt_environment();

    QGuiApplication app(argc, argv);
#ifdef VIEW
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl(u"qrc:Main/main.qml"_qs));
    view.show();
    QObject::connect(&view, &QQuickView::sceneGraphInitialized, [&view]() {
        //auto viewport = view.rootObject()->findChild<OpenGLViewport*>("sceneItem");
        //OpenGLRenderer::InitGraphicsApi();
        //auto scene = viewport->LoadScene(8);
        //viewport->SetScene(scene);
        });

#else 
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:Main/main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl) {
            auto name = url.toString();
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");

    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }
#endif
    return app.exec();
}
