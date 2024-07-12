#include "shapes/DraggableEllipse.h"
#include <QBrush>
#include <QDebug>

DraggableEllipse::DraggableEllipse(qreal x, qreal y, qreal radius, int pointIndex, QGraphicsItem *parent)
    : QGraphicsEllipseItem(-radius, -radius, 2 * radius, 2 * radius, parent), pointIndex(pointIndex) {
    setBrush(QBrush(Qt::red));
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setPos(x, y);
}

QVariant DraggableEllipse::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        qDebug() << "Draggable point" << pointIndex << "moved to" << newPos;
        emit pointMoved(pointIndex, newPos);
        emit pointMovedInScene(pointIndex, mapToScene(newPos)); // Scene coordinates
    }
    return QGraphicsEllipseItem::itemChange(change, value);
}
