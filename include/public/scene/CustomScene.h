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
    virtual ~CustomScene();

    Q_INVOKABLE void addItem(SceneItem *item);
    Q_INVOKABLE void removeItem(SceneItem *item);
    Q_INVOKABLE void releaseItem(SceneItem *item);
    const QList<SceneItem *> &getItems() const;

signals:
    void itemAdded(SceneItem *item);

protected:
    void paint(QPainter *painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void hoverMoveEvent(QHoverEvent *event) override;
    void updateZOrders();

private:
    QList<SceneItem *> m_items;
};

#endif // CUSTOMSCENE_H
