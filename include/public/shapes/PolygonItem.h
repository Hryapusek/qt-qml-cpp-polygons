#ifndef POLYGONITEM_H
#define POLYGONITEM_H

#include "scene/SceneItem.h"
#include "shapes/DraggableEllipse.h"
#include <QPolygonF>
#include <QList>
#include <QPointF>

class PolygonItem : public SceneItem {
    Q_OBJECT
    Q_PROPERTY(QPolygonF polygon READ polygon WRITE setPolygon NOTIFY polygonChanged)

public:
    PolygonItem(QQuickItem *parent = nullptr);

    QPolygonF polygon() const;
    void setPolygon(const QPolygonF &polygon);

signals:
    void polygonChanged();
    void polygonSelected(const QPolygonF &polygon);
    void pointUpdated(int index, const QPointF &newPos);
    void polygonMoved(const QPolygonF &polygon);

public slots:
    void updatePolygonPoint(int index, QPointF newPos);

protected:
    void paint(QPainter *painter) override;
    bool handleMousePress(QMouseEvent *event) override;
    bool handleMouseMove(QMouseEvent *event) override;

private:
    void createDraggablePoints();
    void updateDraggablePoint(int index, QPointF newPos);
    QList<QPointF> m_points;
    QPolygonF m_polygon;
    int m_selectedPointIndex;
    QList<DraggableEllipse*> m_draggablePoints;
};

#endif // POLYGONITEM_H
