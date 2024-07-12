#include "shapes/PolygonItem.h"
#include <QDebug>

PolygonItem::PolygonItem(QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent) {
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void PolygonItem::setPolygon(const QPolygonF &polygon) {
    QGraphicsPolygonItem::setPolygon(polygon);
    createDraggablePoints();
}

void PolygonItem::updatePolygonPoint(int index, QPointF newPos) {
    QPolygonF poly = polygon();
    if (index >= 0 && index < poly.size()) {
        qDebug() << "Updating polygon point" << index << "to new position" << newPos;
        poly[index] = newPos;
        QGraphicsPolygonItem::setPolygon(poly);
        updateDraggablePoint(index, newPos);
    } else {
        qDebug() << "Invalid point index" << index;
    }
}

void PolygonItem::createDraggablePoints() {
    qDebug() << "Creating draggable points";
    for (auto pointItem : draggablePoints) {
        delete pointItem;
    }
    draggablePoints.clear();

    QPolygonF poly = polygon();
    for (int i = 0; i < poly.size(); ++i) {
        DraggableEllipse *ellipse = new DraggableEllipse(poly[i].x(), poly[i].y(), POINT_RADIUS, i, this);
        connect(ellipse, &DraggableEllipse::pointMoved, this, &PolygonItem::updatePolygonPoint);
        draggablePoints.append(ellipse);
        qDebug() << "Created draggable point" << i << "at position" << poly[i];
    }
}

void PolygonItem::updateDraggablePoint(int index, QPointF newPos) {
    if (index >= 0 && index < draggablePoints.size()) {
        // qDebug() << "Updating draggable point" << index << "to new position" << newPos;
        // draggablePoints[index]->setPos(newPos);
    } else {
        qDebug() << "Invalid draggable point index" << index;
    }
}
