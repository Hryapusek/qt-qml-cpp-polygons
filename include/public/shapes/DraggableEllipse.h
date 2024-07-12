#ifndef DRAGGABLEELLIPSE_H
#define DRAGGABLEELLIPSE_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QPointF>

const qreal POINT_RADIUS = 5.0;

class DraggableEllipse : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT

public:
    DraggableEllipse(qreal x, qreal y, qreal radius, int pointIndex, QGraphicsItem *parent = nullptr);

signals:
    void pointMoved(int pointIndex, QPointF newPos);
    void pointMovedInScene(int pointIndex, QPointF newPos);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    int pointIndex;
};

#endif // DRAGGABLEELLIPSE_H
