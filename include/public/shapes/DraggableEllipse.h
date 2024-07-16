#ifndef DRAGGABLEELLIPSE_H
#define DRAGGABLEELLIPSE_H

#include "scene/SceneItem.h"
#include <QPointF>

class CustomScene;

class DraggableEllipse : public SceneItem {
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(int pointIndex READ pointIndex WRITE setPointIndex NOTIFY pointIndexChanged)

public:
    DraggableEllipse(qreal x, qreal y, qreal radius, int pointIndex, QQuickItem *parent = nullptr);
    DraggableEllipse(QQuickItem *parent = nullptr);

    qreal radius() const;
    void setRadius(qreal radius);

    int pointIndex() const;
    void setPointIndex(int index);

    void paintFigure(QPainter *painter) override;

    void move(qreal dx, qreal dy);

signals:
    void xChanged();
    void yChanged();
    void radiusChanged();
    void pointIndexChanged();
    void pointClicked(int pointIndex);
    void pointMoved(int pointIndex, QPointF newPos);
    void pointMovedInScene(int pointIndex, QPointF newPos);

protected:
    bool handleMousePress(QMouseEvent *event) override;
    bool handleMouseRelease(QMouseEvent *event) override;
    bool handleMouseMove(QMouseEvent *event) override;

private:
    int m_pointIndex;
    qreal m_radius;
    QPointF m_lastMousePos;
    bool movingPoint;

    bool containsPoint(const QPointF &point);
};

#endif // DRAGGABLEELLIPSE_H
