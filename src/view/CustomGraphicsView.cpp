#include "view/CustomGraphicsView.h"
#include <QResizeEvent>

CustomGraphicsView::CustomGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent) {
}

void CustomGraphicsView::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    if (scene()) {
        QRectF newSceneRect(0, 0, event->size().width(), event->size().height());
        scene()->setSceneRect(newSceneRect);
        fitInView(newSceneRect, Qt::KeepAspectRatio); // Optional: Fit the view to the scene rect
    }
}
