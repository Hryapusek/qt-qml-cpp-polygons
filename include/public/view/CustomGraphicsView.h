#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>

class CustomGraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    CustomGraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // CUSTOMGRAPHICSVIEW_H
