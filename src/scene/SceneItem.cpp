#include "scene/SceneItem.h"
#include "scene/CustomScene.h"

SceneItem::SceneItem(QQuickItem *parent)
    : QQuickPaintedItem(parent), m_zOrder(0), m_scene(nullptr) {
}

int SceneItem::zOrder() const {
    return m_zOrder;
}

void SceneItem::setZOrder(int zOrder) {
    if (m_zOrder != zOrder) {
        m_zOrder = zOrder;
        emit zOrderChanged();
        update();
    }
}

CustomScene* SceneItem::scene() const {
    return m_scene;
}

void SceneItem::setScene(CustomScene *scene) {
    if (m_scene != scene) {
        m_scene = scene;
        setParentItem(scene);
        update();
    }
}
