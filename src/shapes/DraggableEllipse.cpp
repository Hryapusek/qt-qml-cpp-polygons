#include "shapes/DraggableEllipse.h"
#include "scene/CustomScene.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

DraggableEllipse::DraggableEllipse(qreal x, qreal y, qreal radius, int pointIndex, QQuickItem *parent)
    : SceneItem(parent), m_pointIndex(pointIndex), m_radius(radius), m_scene(nullptr) {
    setX(x - radius);
    setY(y - radius);
    setWidth(radius * 2);
    setHeight(radius * 2);
}

DraggableEllipse::DraggableEllipse(QQuickItem *parent)
    : SceneItem(parent), m_pointIndex(0), m_radius(POINT_RADIUS), m_scene(nullptr) {
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

CustomScene* DraggableEllipse::scene() const {
    return m_scene;
}

void DraggableEllipse::setScene(CustomScene* scene) {
    if (m_scene != scene) {
        if (m_scene) {
            m_scene->removeItem(this);
        }
        m_scene = scene;
        if (m_scene) {
            m_scene->addItem(this);
        }
        emit sceneChanged();
    }
}

void DraggableEllipse::paint(QPainter *painter) {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(Qt::red);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(boundingRect());
    qDebug() << "DraggableEllipse::paint - Drawing at position:" << QPointF(x(), y());
}

bool DraggableEllipse::handleMousePress(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        qDebug() << "DraggableEllipse::handleMousePress - Click registered at position:" << event->pos();
        m_lastMousePos = event->pos();
        return true;
    }
    qDebug() << "DraggableEllipse::handleMousePress - Click not handled";
    return false;
}

bool DraggableEllipse::handleMouseMove(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        QPointF delta = event->pos() - m_lastMousePos;
        setX(x() + delta.x());
        setY(y() + delta.y());
        emit pointMoved(m_pointIndex, QPointF(x(), y()));

        // Explicitly map to the parent item, which is expected to be CustomScene
        if (scene()) {
            QPointF scenePos = mapToItem(scene(), QPointF(x(), y()));
            emit pointMovedInScene(m_pointIndex, scenePos);
        } else {
            emit pointMovedInScene(m_pointIndex, QPointF(x(), y()));
        }

        qDebug() << "DraggableEllipse::handleMouseMove - Moved to position:" << QPointF(x(), y());

        // Update last mouse position
        m_lastMousePos = event->pos();
        return true;
    }
    qDebug() << "DraggableEllipse::handleMouseMove - Move not handled";
    return false;
}
