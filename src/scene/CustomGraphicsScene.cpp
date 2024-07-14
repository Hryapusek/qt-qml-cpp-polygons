#include "scene/CustomGraphicsScene.h"
#include <QDebug>

CustomGraphicsScene::CustomGraphicsScene(QObject *parent)
    : QGraphicsScene(parent) {
    // Set an initial scene rect
    setSceneRect(0, 0, 800, 600);
    emit sceneRectChanged(sceneRect());
}
