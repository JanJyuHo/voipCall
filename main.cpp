#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "VoipManager.h"

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"wsock32.lib")
#pragma comment(lib,"ole32.lib")
#pragma comment(lib,"dsound.lib")

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    voip::VoipManager main_voip;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("voip", &main_voip);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
