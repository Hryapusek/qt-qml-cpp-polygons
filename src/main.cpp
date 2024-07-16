#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTableView>
#include <QSplitter>
#include <QQmlContext>

#include "helpers/OtherFunctions.h"

#include "shapes/DraggableEllipse.h"
#include "shapes/PolygonBuilder.h"
#include "shapes/PolygonItem.h"

#include "models/PolygonPointModel.h"

#include "scene/CustomScene.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const QUrl toggleButtonUrl(QStringLiteral("qrc:/qml/ToggleButton.qml"));
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));

    // Register C++ classes with QML
    qmlRegisterType<CustomScene>("Shapes", 1, 0, "CustomScene");
    qmlRegisterType<DraggableEllipse>("Shapes", 1, 0, "DraggableEllipse");
    qmlRegisterType<PolygonItem>("Shapes", 1, 0, "PolygonItem");
    qmlRegisterType<PolygonBuilder>("Shapes", 1, 0, "PolygonBuilder");
    qmlRegisterType<PolygonPointModel>("Shapes", 1, 0, "PolygonPointModel");

    auto otherFunctions = OtherFunctions::instance();
    engine.rootContext()->setContextProperty("otherFunctions", otherFunctions);
    
    engine.load(toggleButtonUrl);
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
