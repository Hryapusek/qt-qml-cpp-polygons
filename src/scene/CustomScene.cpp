#include "scene/CustomScene.h"
#include "shapes/PolygonItem.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <algorithm>

CustomScene::CustomScene(QQuickItem *parent)
    : QQuickPaintedItem(parent) {
    qDebug() << "CustomScene initialized";
    setAcceptedMouseButtons(Qt::AllButtons); // Accept all mouse buttons
    setFlag(ItemHasContents, true);
}

void CustomScene::addItem(SceneItem *item) {
    if (!m_items.contains(item)) {
        m_items.append(item);
        item->setScene(this);
        qDebug() << "Item added to CustomScene:" << item;

        // Connect z-order signals
        connect(item, &SceneItem::zOrderLiftUpOne, this, [this](SceneItem *item) {
            int index = m_items.indexOf(item);
            if (index > 0) {
                m_items.swapItemsAt(index, index - 1);
                update();
            }
        });
        connect(item, &SceneItem::zOrderPutOnTop, this, [this](SceneItem *item) {
            m_items.removeOne(item);
            m_items.append(item);
            update();
        });
        connect(item, &SceneItem::zOrderLowerDownOne, this, [this](SceneItem *item) {
            int index = m_items.indexOf(item);
            if (index < m_items.size() - 1) {
                m_items.swapItemsAt(index, index + 1);
                update();
            }
        });
        connect(item, &SceneItem::zOrderPutOnBottom, this, [this](SceneItem *item) {
            m_items.removeOne(item);
            m_items.prepend(item);
            update();
        });

        update();
    }
}

void CustomScene::removeItem(SceneItem *item) {
    if (m_items.removeOne(item)) {
        item->setScene(nullptr);
        qDebug() << "Item removed from CustomScene:" << item;
        update();
    }
}

void CustomScene::paint(QPainter *painter) {
    painter->setRenderHint(QPainter::Antialiasing);

    // Set background color
    painter->fillRect(boundingRect(), Qt::yellow);

    std::sort(m_items.begin(), m_items.end(), [](const QPointer<SceneItem> &a, const QPointer<SceneItem> &b) {
        return a->zOrder() < b->zOrder();
    });

    for (SceneItem *item : qAsConst(m_items)) {
        item->paintFigure(painter);
    }
}

void CustomScene::mousePressEvent(QMouseEvent *event) {
    qDebug() << "CustomScene::mousePressEvent - Click registered at position:" << event->pos();

    std::sort(m_items.begin(), m_items.end(), [](const QPointer<SceneItem> &a, const QPointer<SceneItem> &b) {
        return a->zOrder() > b->zOrder();
    });

    for (SceneItem *item : m_items) {
        if (item->handleMousePress(event)) {
            qDebug() << "CustomScene::mousePressEvent - Event handled by item:" << item;
            break;  // Stop processing if the event was handled
        }
        qDebug() << "CustomScene::mousePressEvent - Event not handled by item:" << item;
    }
    update();
}

void CustomScene::mouseReleaseEvent(QMouseEvent * event)
{
    qDebug() << "CustomScene::mousePressEvent - Click registered at position:" << event->pos();

    std::sort(m_items.begin(), m_items.end(), [](const QPointer<SceneItem> &a, const QPointer<SceneItem> &b) {
        return a->zOrder() > b->zOrder();
    });

    for (SceneItem *item : m_items) {
        if (item->handleMouseRelease(event)) {
            qDebug() << "CustomScene::mousePressEvent - Event handled by item:" << item;
            break;  // Stop processing if the event was handled
        }
        qDebug() << "CustomScene::mousePressEvent - Event not handled by item:" << item;
    }
    update();
}

void CustomScene::mouseMoveEvent(QMouseEvent *event) {
    qDebug() << "CustomScene::mouseMoveEvent - Move registered at position:" << event->pos();
    for (SceneItem *item : qAsConst(m_items)) {
        if (item->handleMouseMove(event)) {
            qDebug() << "CustomScene::mouseMoveEvent - Event handled by item:" << item;
            break;  // Stop processing if the event was handled
        }
    }
    update();
}