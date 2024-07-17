#ifndef POLYGONBUILDER_H
#define POLYGONBUILDER_H

#include <QObject>
#include <QPolygonF>
#include <QList>
#include "scene/SceneItem.h"
#include "scene/CustomScene.h"

class PolygonBuilder : public SceneItem {
    Q_OBJECT

public:
    PolygonBuilder(QQuickItem *parent = nullptr);

signals:
    void polygonCreated(QPolygonF newPolygon);

protected:
    bool handleMousePress(QMouseEvent *event) override;
    bool handleHoverMoveEvent(QHoverEvent *event) override;
    bool handleMouseMove(QMouseEvent *event) override { return true; }
    void paintFigure(QPainter *painter) override;

private:
    CustomScene *scene;
    QPolygonF tempPoly;
    bool creatingPolygon;
    QPointF currentMousePos;
};

#endif // POLYGONBUILDER_H
