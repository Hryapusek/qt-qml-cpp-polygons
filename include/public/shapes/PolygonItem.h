#ifndef CUSTOMPOLYGONITEM_H
#define CUSTOMPOLYGONITEM_H

#include <QGraphicsPolygonItem>
#include <QObject>
#include "shapes/DraggableEllipse.h"

class PolygonItem : public QObject, public QGraphicsPolygonItem {
    Q_OBJECT

public:
    PolygonItem(QGraphicsItem *parent = nullptr);

    void setPolygon(const QPolygonF &polygon);

signals:
    void polygonSelected(const QPolygonF &polygon);
    void polygonSelectedInScene(const QPolygonF &polygon);
    void pointUpdated(int index, const QPointF &newPos);
    void pointUpdatedInScene(int index, const QPointF &newPos);
    void polygonMoved(const QPolygonF &polygon);
    void polygonMovedInScene(const QPolygonF &polygon);

public slots:
    void updatePolygonPoint(int index, QPointF newPos);
    void updatePolygonPointInScene(int index, QPointF newPos);
    void updateBothPoints(int index, QPointF newPos);
    void updateBothPointsInScene(int index, QPointF newPos);

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private slots:
    void deletePolygon();

private:
    void createDraggablePoints();
    void updateDraggablePoint(int index, QPointF newPos);
    QList<DraggableEllipse*> draggablePoints;
};

#endif // CUSTOMPOLYGONITEM_H
