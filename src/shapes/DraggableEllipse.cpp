#include "shapes/DraggableEllipse.h"
#include "scene/CustomScene.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <cmath>

DraggableEllipse::DraggableEllipse(qreal x, qreal y, qreal radius, int pointIndex, QQuickItem *parent)
    : SceneItem(parent), m_pointIndex(pointIndex), m_radius(radius), movingPoint(false) {
    m_scene = nullptr;
    setX(x - radius);
    setY(y - radius);
    setWidth(radius * 2);
    setHeight(radius * 2);
}

DraggableEllipse::DraggableEllipse(QQuickItem *parent)
    : SceneItem(parent), m_pointIndex(0), m_radius(2), movingPoint(false) {
    m_scene = nullptr;
    setWidth(m_radius * 2);
    setHeight(m_radius * 2);
}

qreal DraggableEllipse::radius() const {
    return m_radius;
}

void DraggableEllipse::setRadius(qreal radius) {
    if (m_radius != radius) {
        m_radius = radius;
        setWidth(radius * 2);
        setHeight(radius * 2);
        emit radiusChanged();
        update();
    }
}

int DraggableEllipse::pointIndex() const {
    return m_pointIndex;
}

void DraggableEllipse::setPointIndex(int index) {
    if (m_pointIndex != index) {
        m_pointIndex = index;
        emit pointIndexChanged();
        update();
    }
}

void DraggableEllipse::paintFigure(QPainter *painter) {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(Qt::red);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(QPointF(x() + m_radius, y() + m_radius), m_radius, m_radius);
    qDebug() << "DraggableEllipse::paint - Drawing at position:" << QPointF(x() + m_radius, y() + m_radius);
}


void DraggableEllipse::move(qreal dx, qreal dy)
{
    setX(x() + dx);
    setY(y() + dy);
    update();
}

bool DraggableEllipse::handleMousePress(QMouseEvent *event) {
    if (not containsPoint(event->pos()))
        return false;
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Moving point START";
        m_lastMousePos = event->pos();
        movingPoint = true;
        pointClicked(m_pointIndex);
        return true;
    }
    qDebug() << "DraggableEllipse::handleMousePress - Click not handled";
    return false;
}

bool DraggableEllipse::handleMouseRelease(QMouseEvent *event) {
    if (movingPoint and event->button() == Qt::LeftButton)
    {
        qDebug() << "Moving point STOP";
        movingPoint = false;
        return true;
    }
    if (not containsPoint(event->pos()))
        return false;
    qDebug() << "DraggableEllipse::handleMouseRelease - Click not handled";
    return false;
}

bool DraggableEllipse::handleMouseMove(QMouseEvent *event) {
    if (not movingPoint and not containsPoint(event->pos()))
        return false;
    if (movingPoint and event->buttons() & Qt::LeftButton) {
        movingPoint = true;
        QPointF delta = event->pos() - m_lastMousePos;
        setX(x() + delta.x());
        setY(y() + delta.y());
        emit pointMoved(m_pointIndex, QPointF(x() + m_radius, y() + m_radius));

        // Explicitly map to the parent item, which is expected to be CustomScene
        if (scene()) {
            QPointF scenePos = mapToItem(scene(), QPointF(x() + m_radius, y() + m_radius));
            emit pointMovedInScene(m_pointIndex, scenePos);
        } else {
            emit pointMovedInScene(m_pointIndex, QPointF(x() + m_radius, y() + m_radius));
        }

        qDebug() << "DraggableEllipse::handleMouseMove - Moved to position:" << QPointF(x(), y());

        // Update last mouse position
        m_lastMousePos = event->pos();
        return true;
    }
    qDebug() << "DraggableEllipse::handleMouseMove - Move not handled";
    return false;
}

bool DraggableEllipse::containsPoint(const QPointF &point)
{
    qDebug() << "Checking if point is in radius " << m_radius;
    qreal x0 = x() + m_radius;
    qreal y0 = y() + m_radius;
    auto distance = (point.x() - x0)*(point.x() - x0) + (point.y() - y0)*(point.y() - y0);
    qDebug() << "Distance is " << distance;
    return distance <= m_radius*m_radius;
}
