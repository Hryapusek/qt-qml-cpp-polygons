#ifndef SCENEITEM_H
#define SCENEITEM_H

#include <QQuickPaintedItem>
#include <QMouseEvent>

class CustomScene;  // Forward declaration

// FIXME: check if item actually contains click event position and move position

class SceneItem : public QQuickPaintedItem {
    Q_OBJECT
    Q_PROPERTY(int zOrder READ zOrder WRITE setZOrder NOTIFY zOrderChanged)
    Q_PROPERTY(CustomScene* scene READ scene WRITE setScene NOTIFY sceneChanged)

    friend class CustomScene;
public:
    SceneItem(QQuickItem *parent = nullptr);
    SceneItem(CustomScene *scene = nullptr);

    virtual ~SceneItem();

    int zOrder() const;
    void setZOrder(int zOrder);

    virtual CustomScene* scene() const;
    virtual void setScene(CustomScene *scene);

    virtual void paintFigure(QPainter *) {};
    virtual void paint(QPainter *) final {};

signals:
    void sceneChanged();
    void zOrderChanged();
    void zOrderLiftUpOne(SceneItem *item);
    void zOrderPutOnTop(SceneItem *item);
    void zOrderLowerDownOne(SceneItem *item);
    void zOrderPutOnBottom(SceneItem *item);

public:
    virtual bool handleMousePress(QMouseEvent *event) { return false; };
    virtual bool handleMouseRelease(QMouseEvent *event)  { return false; };
    virtual bool handleMouseMove(QMouseEvent *event)  { return false; };

protected:
    CustomScene *m_scene;
    int m_zOrder;

};

#endif // SCENEITEM_H
