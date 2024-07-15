#include "shapes/PolygonItem.h"
#include <QPainter>
#include <QMouseEvent>
#include <QQuickItem>

PolygonItem::PolygonItem(QQuickItem *parent)
    : SceneItem(parent), m_selectedPointIndex(-1) {
}

QPolygonF PolygonItem::polygon() const {
    return m_polygon;
}

QVector<QPointF> PolygonItem::polygonPoints() const
{
    return m_polygon.toList().toVector();
}

void PolygonItem::setPolygon(const QPolygonF &polygon) {
    if (m_polygon != polygon) {
        m_polygon = polygon;
        m_points = polygon.toList();
        createDraggablePoints();
        emit polygonChanged();
        std::for_each(m_draggablePoints.begin(), m_draggablePoints.end(), [](DraggableEllipse * el){ el->update(); });
        update();
    }
}


void PolygonItem::setPolygonFromVector(const QVector<QPointF>& polygon)
{
    setPolygon(QPolygonF(polygon));
}

void PolygonItem::createDraggablePoints() {
    // Clear any existing draggable points
    std::for_each(m_draggablePoints.begin(), m_draggablePoints.end(), [](DraggableEllipse * pointer) { pointer->deleteLater(); });
    m_draggablePoints.clear();

    // Create new draggable points
    for (int i = 0; i < m_points.size(); ++i) {
        QPointF point = m_points[i];
        DraggableEllipse *ellipse = new DraggableEllipse(point.x(), point.y(), POINT_RADIUS, i, this);
        ellipse->setScene(scene());
        connect(ellipse, &DraggableEllipse::pointMoved, this, &PolygonItem::updatePolygonPoint);
        m_draggablePoints.append(ellipse);
    }
}

void PolygonItem::updateBothPoints(int index, QPointF newPos)
{
    updateDraggablePoint(index, newPos);
    updatePolygonPoint(index, newPos);
}

void PolygonItem::updateDraggablePoint(int index, QPointF newPos) {
    if (index >= 0 && index < m_draggablePoints.size()) {
        m_draggablePoints[index]->setX(newPos.x() - POINT_RADIUS);
        m_draggablePoints[index]->setY(newPos.y() - POINT_RADIUS);
        m_draggablePoints[index]->update();
    }
}

void PolygonItem::updatePolygonPoint(int index, QPointF newPos) {
    if (index >= 0 && index < m_points.size()) {
        m_points[index] = newPos;
        m_polygon.replace(index, newPos);
        emit pointUpdated(index, newPos);
        update();
    }
}

void PolygonItem::paintFigure(QPainter *painter) {
    painter->setRenderHint(QPainter::Antialiasing);

    // Draw the polygon
    painter->setPen(Qt::black);
    painter->setBrush(Qt::transparent);
    painter->drawPolygon(m_polygon);

    for (auto draggablePoint : m_draggablePoints) {
        draggablePoint->paintFigure(painter);
    }
}

bool PolygonItem::handleMousePress(QMouseEvent *event) {
    QPointF clickPos = event->pos();
    for (int i = 0; i < m_points.size(); ++i) {
        if (QLineF(clickPos, m_points[i]).length() < 5) {
            m_selectedPointIndex = i;
            return true;
        }
    }
    return false;
}

bool PolygonItem::handleMouseMove(QMouseEvent *event) {
    if (m_selectedPointIndex >= 0 && m_selectedPointIndex < m_points.size()) {
        updatePolygonPoint(m_selectedPointIndex, event->pos());
        return true;
    }
    return false;
}
