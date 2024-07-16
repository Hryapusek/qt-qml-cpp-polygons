#ifndef POLYGONPOINTMODEL_H
#define POLYGONPOINTMODEL_H

#include <QAbstractTableModel>
#include <QPolygonF>
#include "shapes/PolygonItem.h"

class PolygonPointModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit PolygonPointModel(QObject *parent = nullptr);

    QPolygonF getPolygon() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

public slots:
    void setPolygon(const QPolygonF &polygon);
    void selectPolygonItem(PolygonItem *connectedItem);
    void updatePoint(int index, const QPointF &newPos);
    void connectPolygon(SceneItem *item);

signals:
    void polygonUpdated(const QPolygonF &polygon);
    void pointUpdated(int index, const QPointF &newPos);

private:
    QPolygonF m_polygon;
    PolygonItem *m_selectedPolygon;
};

#endif // POLYGONPOINTMODEL_H
