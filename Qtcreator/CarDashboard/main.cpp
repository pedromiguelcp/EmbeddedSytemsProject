#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickStyle>
#include <QtQml>
#include "dash.h"
#include <signal.h>

using namespace std;


int main(int argc, char *argv[])
{
    Dash myClass;

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    qmlRegisterType<Dash>("MyClassLib", 1, 0, "MyClass");

    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myclass", &myClass);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    myClass.SetPthreads();

    app.exec();

    myClass.JoinPthreads();

    myClass.DestroyMutexes();

    return 0;
}
