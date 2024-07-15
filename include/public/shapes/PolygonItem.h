#ifndef POLYGONITEM_H
#define POLYGONITEM_H

#include "scene/SceneItem.h"
#include "shapes/DraggableEllipse.h"
#include <QPolygonF>
#include <QList>
#include <QPointF>

class PolygonItem : public SceneItem {
    Q_OBJECT
    Q_PROPERTY(QVector<QPointF> polygon READ polygonPoints WRITE setPolygonFromVector NOTIFY polygonChanged)

public:
    const qreal POINT_RADIUS = 5.0;
    const qreal ACTIVATE_LINE_DISTANCE = 2.0;

    PolygonItem(QQuickItem *parent = nullptr);

    QPolygonF polygon() const;
    QVector<QPointF> polygonPoints() const;
    void setPolygon(const QPolygonF &polygon);
    void setPolygonFromVector(const QVector<QPointF> &polygon);
    void paintFigure(QPainter *painter) override;

signals:
    void polygonChanged();
    void polygonSelected(const QPolygonF &polygon);
    void pointUpdated(int index, const QPointF &newPos);
    void polygonMoved(const QPolygonF &polygon);
    void pointUpdatedInScene(int index, const QPointF &newPos);
    void polygonMovedInScene(const QPolygonF &polygon);

public slots:
    void updatePolygonPoint(int index, QPointF newPos);
    void updateBothPoints(int index, QPointF newPos);

protected:
    bool handleMousePress(QMouseEvent *event) override;
    bool handleMouseMove(QMouseEvent *event) override;
    void moveToNewPosition(QPointF newPos);

private:
    void createDraggablePoints();
    void updateDraggablePoint(int index, QPointF newPos);
    QList<QPointF> m_points;
    QPolygonF m_polygon;
    QPointF m_oldPos;
    int m_selectedLineIndex;
    QList<DraggableEllipse*> m_draggablePoints;
};

#endif // POLYGONITEM_H
