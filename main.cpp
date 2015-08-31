#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "mymodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<MyModel>("mymodell", 1, 0, "MyModell");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
