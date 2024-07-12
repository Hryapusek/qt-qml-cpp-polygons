#ifndef POLYGONBUILDER_H
#define POLYGONBUILDER_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QPolygonF>
#include <QList>

class PolygonBuilder : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    PolygonBuilder(QGraphicsScene *scene, QObject *parent = nullptr);

signals:
    void polygonCreated(QPolygonF newPolygon);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QGraphicsScene *scene;
    QPolygonF tempPoly;
    bool creatingPolygon;
};

#endif // POLYGONBUILDER_H
