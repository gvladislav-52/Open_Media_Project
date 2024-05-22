#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <file_processing.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    File_processing file_proc;

    QQmlApplicationEngine engine;

    QQmlContext *rootContext = engine.rootContext();
    rootContext->setContextProperty("file_proc", &file_proc);

    const QUrl url("qrc:/Main.qml");
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
