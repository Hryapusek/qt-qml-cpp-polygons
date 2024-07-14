#ifndef SCENEITEM_H
#define SCENEITEM_H

#include <QQuickPaintedItem>
#include <QMouseEvent>

class CustomScene;  // Forward declaration

// FIXME: check if item actually contains click event position and move position

class SceneItem : public QQuickPaintedItem {
    Q_OBJECT
    Q_PROPERTY(int zOrder READ zOrder WRITE setZOrder NOTIFY zOrderChanged)

public:
    SceneItem(QQuickItem *parent = nullptr);

    int zOrder() const;
    void setZOrder(int zOrder);

    CustomScene* scene() const;
    void setScene(CustomScene *scene);

signals:
    void zOrderChanged();
    void zOrderLiftUpOne(SceneItem *item);
    void zOrderPutOnTop(SceneItem *item);
    void zOrderLowerDownOne(SceneItem *item);
    void zOrderPutOnBottom(SceneItem *item);

public:
    virtual bool handleMousePress(QMouseEvent *event) = 0;
    virtual bool handleMouseMove(QMouseEvent *event) = 0;

private:
    int m_zOrder;
    CustomScene *m_scene;
};

#endif // SCENEITEM_H
