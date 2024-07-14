#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class CustomGraphicsScene : public QGraphicsScene {
    Q_OBJECT

public:
    CustomGraphicsScene(QObject *parent = nullptr);

signals:
    void sceneRectChanged(const QRectF &rect);

};

#endif // CUSTOMGRAPHICSSCENE_H
