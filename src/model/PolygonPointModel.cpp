#include "models/PolygonPointModel.h"

PolygonPointModel::PolygonPointModel(QObject *parent)
    : QAbstractTableModel(parent) {
}

void PolygonPointModel::setPolygon(const QPolygonF &polygon) {
    beginResetModel();
    m_polygon = polygon;
    endResetModel();
}

QPolygonF PolygonPointModel::getPolygon() const {
    return m_polygon;
}

int PolygonPointModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_polygon.size();
}

int PolygonPointModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 2; // x and y coordinates
}

QVariant PolygonPointModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (section < 0 or section >= 2)
        return QVariant();
    if (orientation == Qt::Orientation::Vertical)
        return QVariant();
    switch (section)
    {
    case 0:
        return tr("Широта");
    
    case 1:
        return tr("Долгота");

    default:
        return QVariant();
    }
}

QVariant PolygonPointModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || role != Qt::DisplayRole) {
    return QVariant();
  }

  const QPointF &point = m_polygon.at(index.row());
  if (index.column() == 0) {
    return point.x();
  } else if (index.column() == 1) {
    return point.y();
  }

  return QVariant();
}

bool PolygonPointModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || role != Qt::EditRole) {
        return false;
    }

    QPointF &point = m_polygon[index.row()];
    bool ok;
    double coordinate = value.toDouble(&ok);
    if (!ok) {
        return false;
    }

    if (index.column() == 0) {
        point.setX(coordinate);
    } else if (index.column() == 1) {
        point.setY(coordinate);
    } else {
        return false;
    }

    emit dataChanged(index, index);
    emit pointUpdated(index.row(), point);
    return true;
}

Qt::ItemFlags PolygonPointModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

void PolygonPointModel::updatePoint(int index, const QPointF &newPos) {
    if (index >= 0 && index < m_polygon.size()) {
        m_polygon[index] = newPos;
        QModelIndex modelIndex = createIndex(index, 0);
        emit dataChanged(modelIndex, modelIndex.sibling(index, 1));
    }
}

void PolygonPointModel::selectPolygonItem(PolygonItem * connectedItem) {
    if (m_selectedPolygon)
    {
        QObject::disconnect(this, &PolygonPointModel::updatePoint, m_selectedPolygon, &PolygonItem::updateBothPoints);
        QObject::disconnect(m_selectedPolygon, &PolygonItem::polygonMoved, this, &PolygonPointModel::setPolygon);
    }
    m_selectedPolygon = connectedItem;
    setPolygon(connectedItem->polygon());
    QObject::connect(this, &PolygonPointModel::updatePoint, m_selectedPolygon, &PolygonItem::updateBothPoints);
    QObject::connect(m_selectedPolygon, &PolygonItem::polygonMoved, this, &PolygonPointModel::setPolygon);
}


void PolygonPointModel::connectPolygon(SceneItem *item) {
    PolygonItem *polygon = nullptr;
    if (not (polygon = dynamic_cast<PolygonItem *>(item)))
        return;
    QObject::connect(polygon, &SceneItem::itemSelected, [this, polygon]() {
        this->selectPolygonItem(polygon);
    });
}
