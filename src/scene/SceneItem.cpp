#include "scene/SceneItem.h"
#include "scene/CustomScene.h"

SceneItem::SceneItem(QQuickItem *parent)
    : QQuickPaintedItem(parent), m_zOrder(0), m_scene(nullptr) {
}


SceneItem::SceneItem(CustomScene * scene)
    : QQuickPaintedItem(scene), m_zOrder(0), m_scene(nullptr) {
    setScene(scene);
}

SceneItem::~SceneItem()
{
    if (not m_scene)
        return;
    m_scene->removeItem(this);
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

void SceneItem::setScene(CustomScene* scene) {
    if (m_scene != scene) {
        if (m_scene) {
            m_scene->removeItem(this);
        }
        m_scene = scene;
        if (m_scene) {
            m_scene->addItem(this);
        }
        emit sceneChanged();
    }
}
