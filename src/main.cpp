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

#include "shapes/DraggableEllipse.h"
#include "shapes/PolygonBuilder.h"
#include "shapes/PolygonItem.h"

#include "models/PolygonPointModel.h"

#include "scene/CustomScene.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));

    // Register C++ classes with QML
    qmlRegisterType<CustomScene>("Shapes", 1, 0, "CustomScene");
    qmlRegisterType<DraggableEllipse>("Shapes", 1, 0, "DraggableEllipse");
    
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
