#include "scene/CustomGraphicsScene.h"
#include <QDebug>

CustomGraphicsScene::CustomGraphicsScene(QObject *parent)
    : QGraphicsScene(parent) {
}

void CustomGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(painter);
    Q_UNUSED(rect);
    
    // Always set the scene rect to start at (0, 0)
    setSceneRect(0, 0, width(), height());
}
