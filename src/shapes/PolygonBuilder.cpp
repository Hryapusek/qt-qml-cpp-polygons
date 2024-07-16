#include "shapes/PolygonBuilder.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QPainter>
#include <QPen>
#include <QKeyEvent>
#include <QDebug>

#include "scene/CustomScene.h"

static const qreal POINT_RADIUS = 5;

PolygonBuilder::PolygonBuilder(QQuickItem *parent) :
    SceneItem(parent)
{
}

bool PolygonBuilder::handleMousePress(QMouseEvent *event) {
    QPointF clickPos = event->pos();

    if (!creatingPolygon) {
        creatingPolygon = true;
        tempPoly << clickPos;
    } else {
        if (!tempPoly.isEmpty() && QLineF(clickPos, tempPoly.first()).length() < POINT_RADIUS) {
            emit polygonCreated(tempPoly);
            creatingPolygon = false;
            tempPoly.clear();
            SceneItem::scene()->releaseItem(this);
        } else {
            tempPoly << clickPos;
        }
    }
    update();
    return true;
}

void PolygonBuilder::paintFigure(QPainter *painter) {
    painter->setPen(Qt::black);
    painter->setBrush(Qt::NoBrush);
    if (creatingPolygon)
    {
        painter->drawPolyline(tempPoly);
        painter->setBrush(Qt::red);
        for (const QPointF &point : tempPoly) {
            painter->drawEllipse(point, POINT_RADIUS, POINT_RADIUS);
        }

        if (tempPoly.size() > 1) {
            painter->setPen(Qt::DashLine);
            painter->drawLine(tempPoly.last(), tempPoly.first());
        }
    }
}
