#include "shapes/PolygonBuilder.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QPainter>
#include <QPen>
#include <QKeyEvent>
#include <QDebug>

static const qreal POINT_RADIUS = 5;

PolygonBuilder::PolygonBuilder(QGraphicsScene *scene, QObject *parent)
    : QObject(parent), QGraphicsRectItem(), scene(scene), creatingPolygon(false) {
    setRect(scene->sceneRect());
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
}

void PolygonBuilder::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPointF clickPos = event->pos();

    if (!creatingPolygon) {
        creatingPolygon = true;
        tempPoly.clear();
        tempPoly << clickPos;
    } else {
        if (!tempPoly.isEmpty() && QLineF(clickPos, tempPoly.first()).length() < POINT_RADIUS) {
            emit polygonCreated(tempPoly);
            creatingPolygon = false;
        } else {
            tempPoly << clickPos;
        }
    }
    update();
}

void PolygonBuilder::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::black);
    painter->setBrush(Qt::NoBrush);
    painter->drawPolyline(tempPoly);

    painter->setBrush(Qt::red);
    for (const QPointF &point : tempPoly) {
        painter->drawEllipse(point, POINT_RADIUS, POINT_RADIUS);
    }

    if (creatingPolygon && tempPoly.size() > 1) {
        painter->setPen(Qt::DashLine);
        painter->drawLine(tempPoly.last(), tempPoly.first());
    }
}

void PolygonBuilder::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape && creatingPolygon) {
        qDebug() << "Cancelling polygon creation";
        creatingPolygon = false;
        tempPoly.clear();
        update();
    }
    QGraphicsRectItem::keyPressEvent(event);
}
