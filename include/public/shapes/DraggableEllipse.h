#ifndef DRAGGABLEELLIPSE_H
#define DRAGGABLEELLIPSE_H

#include "scene/SceneItem.h"
#include <QPointF>

const qreal POINT_RADIUS = 5.0;

class CustomScene;

class DraggableEllipse : public SceneItem {
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(int pointIndex READ pointIndex WRITE setPointIndex NOTIFY pointIndexChanged)
    Q_PROPERTY(CustomScene* scene READ scene WRITE setScene NOTIFY sceneChanged)

public:
    DraggableEllipse(qreal x, qreal y, qreal radius, int pointIndex, QQuickItem *parent = nullptr);
    DraggableEllipse(QQuickItem *parent = nullptr);

    qreal radius() const;
    void setRadius(qreal radius);

    int pointIndex() const;
    void setPointIndex(int index);

    CustomScene* scene() const;
    void setScene(CustomScene* scene);

signals:
    void xChanged();
    void yChanged();
    void radiusChanged();
    void pointIndexChanged();
    void sceneChanged();
    void pointMoved(int pointIndex, QPointF newPos);
    void pointMovedInScene(int pointIndex, QPointF newPos);

protected:
    void paint(QPainter *painter) override;
    bool handleMousePress(QMouseEvent *event) override;
    bool handleMouseMove(QMouseEvent *event) override;

private:
    int m_pointIndex;
    qreal m_radius;
    QPointF m_lastMousePos;
    CustomScene* m_scene;
};

#endif // DRAGGABLEELLIPSE_H
