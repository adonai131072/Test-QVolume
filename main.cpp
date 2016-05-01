#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSharedPointer>

#if defined Q_OS_WIN
#include "qvolumechangerwin.h"
#elif defined Q_OS_LINUX
#include "qvolumechangeralsa.h"
#endif

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QVolumeChanger *v = 0;
#if defined Q_OS_WIN
    v = new QVolumeChangerWin;
#elif defined Q_OS_LINUX
    v = new QVolumeChangerAlsa;
#endif

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("volumeChanger", QVariant::fromValue(v));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    int ret = app.exec();

    delete v;
    return ret;
}
