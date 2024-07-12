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

#include "scene/CustomGraphicsScene.h"
#include "view/CustomGraphicsView.h"

int main(int argc, char *argv[])
{
    // QQmlApplicationEngine engine;
    // const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    // QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
    //                  &app, [url](QObject *obj, const QUrl &objUrl) {
    //     if (!obj && url == objUrl)
    //         QCoreApplication::exit(-1);
    // }, Qt::QueuedConnection);
    // engine.load(url);

    QApplication qapp(argc, argv);


    // Create main window
    QWidget window;
    QVBoxLayout layout(&window);

    // Create a splitter to separate the view and the table
    QSplitter *splitter = new QSplitter;

    // Create the scene and view
    CustomGraphicsScene *scene = new CustomGraphicsScene();
    scene->setSceneRect(0, 0, 400, 400);
    CustomGraphicsView *view = new CustomGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setRenderHint(QPainter::Antialiasing);

    // Add the view to the splitter
    splitter->addWidget(view);

    // Create a table view and model for editing polygon points
    QTableView *tableView = new QTableView();
    PolygonPointModel *model = new PolygonPointModel();
    tableView->setModel(model);

    // Add the table view to the splitter
    splitter->addWidget(tableView);

    // Add the splitter to the layout
    layout.addWidget(splitter);

    // Create a polygon
    QPolygonF polygon;
    polygon << QPointF(100, 100) << QPointF(200, 100) << QPointF(150, 200);

    // Create a PolygonItem and add it to the scene
    PolygonItem *polygonItem = new PolygonItem();
    polygonItem->setPolygon(polygon);
    scene->addItem(polygonItem);

    // Set the initial polygon in the model
    model->setPolygon(polygon);

    // Connect polygon item selection to the model
    QObject::connect(polygonItem, &PolygonItem::polygonSelectedInScene, model, &PolygonPointModel::setPolygon);

    // Connect point updates from polygon item to the model
    QObject::connect(polygonItem, &PolygonItem::pointUpdatedInScene, model, &PolygonPointModel::updatePoint);

    // Connect polygon movement to update the model
    QObject::connect(polygonItem, &PolygonItem::polygonMovedInScene, [model](const QPolygonF &polygon) {
        model->setPolygon(polygon);
    });

    // Connect point updates in the model to the polygon item
    QObject::connect(model, &PolygonPointModel::pointUpdated, [polygonItem](int index, const QPointF &newPos) {
        polygonItem->updateBothPointsInScene(index, newPos);
    });

    // Set up and show the main window
    window.setLayout(&layout);
    window.resize(600, 600);
    window.show();

    return qapp.exec();
}
