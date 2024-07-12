#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class CustomGraphicsScene : public QGraphicsScene {
    Q_OBJECT

public:
    CustomGraphicsScene(QObject *parent = nullptr);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
};

#endif // CUSTOMGRAPHICSSCENE_H
