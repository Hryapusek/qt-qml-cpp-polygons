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
    setAcceptHoverEvents(true);
    setFlag(ItemHasContents, true);
}


CustomScene::~CustomScene()
{
    while (not m_items.empty())
    {
        auto item = m_items.last();
        removeItem(item);
    }
}

void CustomScene::addItem(SceneItem *item) {
    if (!m_items.contains(item)) {
        m_items.prepend(item);
        item->setScene(this);
        qDebug() << "Item added to CustomScene:" << item;

        // Connect z-order signals
        connect(item, &SceneItem::zOrderLiftUpOne, this, [this](SceneItem *item) {
            int index = m_items.indexOf(item);
            if (index > 0) {
                m_items.swapItemsAt(index - 1, index);
                updateZOrders();
                update();
            }
        });
        connect(item, &SceneItem::zOrderPutOnTop, this, [this](SceneItem *item) {
            m_items.removeOne(item);
            m_items.prepend(item);
            updateZOrders();
            update();
        });
        connect(item, &SceneItem::zOrderLowerDownOne, this, [this](SceneItem *item) {
            int index = m_items.indexOf(item);
            if (index < m_items.size() - 1) {
                m_items.swapItemsAt(index, index + 1);
                updateZOrders();
                update();
            }
        });
        connect(item, &SceneItem::zOrderPutOnBottom, this, [this](SceneItem *item) {
            m_items.removeOne(item);
            m_items.append(item);
            updateZOrders();
            update();
        });

        emit itemAdded(item);
        update();
    }
}

void CustomScene::updateZOrders() {
    for (int i = 0; i < m_items.size(); ++i) {
        m_items[i]->m_zOrder = i;
    }
}

void CustomScene::removeItem(SceneItem *item) {
    if (m_items.removeOne(item)) {
        item->setScene(nullptr);
        item->deleteLater();
        qDebug() << "Item removed from CustomScene:" << item;
        update();
    }
}

Q_INVOKABLE void CustomScene::releaseItem(SceneItem *item)
{
    m_items.removeOne(item);
    item->setScene(nullptr);
    qDebug() << "Item released from CustomScene:" << item;
    update();
}

const QList<SceneItem *> &CustomScene::getItems() const
{
    return m_items;
}

void CustomScene::paint(QPainter *painter) {
    painter->setRenderHint(QPainter::Antialiasing);

    // Set background color
    painter->fillRect(boundingRect(), Qt::lightGray);

    for (SceneItem *item : qAsConst(m_items)) {
        item->paintFigure(painter);
    }
}

void CustomScene::mousePressEvent(QMouseEvent *event) {
    qDebug() << "CustomScene::mousePressEvent - Click registered at position:" << event->pos() << " Elemnts count: " << m_items.size();

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
    qDebug() << "CustomScene::mouseReleaseEvent - Click registered at position:" << event->pos();

    for (SceneItem *item : m_items) {
        if (item->handleMouseRelease(event)) {
            qDebug() << "CustomScene::mouseReleaseEvent - Event handled by item:" << item;
            break;  // Stop processing if the event was handled
        }
        qDebug() << "CustomScene::mouseReleaseEvent - Event not handled by item:" << item;
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

void CustomScene::hoverMoveEvent(QHoverEvent *event)
{
    qDebug() << "CustomScene::hoverMoveEvent - Hover registered at position:" << event->pos(); 
    for (SceneItem *item : qAsConst(m_items)) {
        if (item->handleHoverMoveEvent(event)) {
            qDebug() << "CustomScene::hoverMoveEvent - Event handled by item:" << item;
            break;  // Stop processing if the event was handled
        }
    }
    update();
}
