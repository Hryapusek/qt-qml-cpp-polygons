#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>


#include "shapes/DraggableEllipse.h"
#include "shapes/PolygonBuilder.h"
#include "shapes/PolygonItem.h"


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

    // Create the scene and view
    QGraphicsScene *scene = new QGraphicsScene(0, 0, 400, 400);
    QGraphicsView *view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);

    // Add the view to the layout
    layout.addWidget(view);

    // Create PolygonBuilder
    PolygonBuilder *builder = new PolygonBuilder(scene);
    builder->setRect(scene->sceneRect());

    // Add toggle button
    QPushButton *toggleBuilderButton = new QPushButton("Toggle Polygon Builder");
    layout.addWidget(toggleBuilderButton);

    // Variable to keep track of builder state
    bool builderEnabled = true;
    scene->addItem(builder);

    QObject::connect(toggleBuilderButton, &QPushButton::clicked, [&]() {
        if (builderEnabled && builder) {
            scene->removeItem(builder);
        } else {
            builder = new PolygonBuilder(scene); 
            scene->addItem(builder);
        }
        builderEnabled = !builderEnabled;
    });

    // Connect the polygonCreated signal to the slot that adds the polygon to the scene
    QObject::connect(builder, &PolygonBuilder::polygonCreated, [&](QPolygonF newPolygon) {
        PolygonItem *polygonItem = new PolygonItem();
        polygonItem->setPolygon(newPolygon);
        scene->addItem(polygonItem);
        builder->deleteLater();
        builder = nullptr;
        qDebug() << "Polygon created with points:" << newPolygon;
    });

    // Create a button to allow creating new polygons
    QPushButton *createPolygonButton = new QPushButton("Create New Polygon");
    layout.addWidget(createPolygonButton);

    // Connect the button click to reset the builder for a new polygon
    QObject::connect(createPolygonButton, &QPushButton::clicked, [&]() {
        builder = new PolygonBuilder(scene);
        builder->setRect(scene->sceneRect());
        scene->addItem(builder);
        QObject::connect(builder, &PolygonBuilder::polygonCreated, [&](QPolygonF newPolygon) mutable {
            PolygonItem *polygonItem = new PolygonItem();
            polygonItem->setPolygon(newPolygon);
            scene->addItem(polygonItem);
            builder->deleteLater();
            builder = nullptr;
            qDebug() << "Polygon created with points:" << newPolygon;
        });
    });

    // Set up and show the main window
    window.setLayout(&layout);
    window.resize(400, 450);
    window.show();

    return qapp.exec();
}
