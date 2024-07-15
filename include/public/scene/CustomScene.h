#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QQuickPaintedItem>
#include <QList>
#include <QPointer>
#include "SceneItem.h"

class CustomScene : public QQuickPaintedItem {
    Q_OBJECT

public:
    CustomScene(QQuickItem *parent = nullptr);

    void addItem(SceneItem *item);
    void removeItem(SceneItem *item);

protected:
    void paint(QPainter *painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QList<QPointer<SceneItem>> m_items;
};

#endif // CUSTOMSCENE_H
