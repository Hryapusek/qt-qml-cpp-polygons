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

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private slots:
    void updatePolygonPoint(int index, QPointF newPos);
    void deletePolygon();

private:
    void createDraggablePoints();
    void updateDraggablePoint(int index, QPointF newPos);
    QList<DraggableEllipse*> draggablePoints;
};

#endif // CUSTOMPOLYGONITEM_H
