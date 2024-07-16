#include "shapes/PolygonItem.h"
#include <QPainter>
#include <QMouseEvent>
#include <QQuickItem>

#include <algorithm>
#include <iterator>

#include "geometry/Geometry.h"

#include "scene/CustomScene.h"

PolygonItem::PolygonItem(QQuickItem *parent)
	: SceneItem(parent), m_selectedLineIndex(-1) {
}

QVector<QPointF> PolygonItem::polygonPoints() const
{
	return m_polygon.toList().toVector();
}

QPolygonF PolygonItem::polygon() const {
	return m_polygon;
}

void PolygonItem::setPolygon(const QPolygonF &polygon) {
	if (m_polygon != polygon) {
		qDebug() << "Got new polygon " << polygon;
		m_polygon = polygon;
		m_points = polygon.toList();
		createDraggablePoints();
		emit polygonChanged();
		std::for_each(m_draggablePoints.begin(), m_draggablePoints.end(),
		              [](DraggableEllipse *el) {
			el->update();
		});
		update();
	}
}

void PolygonItem::setPolygonFromVector(const QVector<QPointF>& polygon)
{
	setPolygon(QPolygonF(polygon));
}

void PolygonItem::createDraggablePoints() {
	// Clear any existing draggable points
	std::for_each(m_draggablePoints.begin(), m_draggablePoints.end(), [](DraggableEllipse * pointer) {
		pointer->deleteLater();
	});
	m_draggablePoints.clear();

	// Create new draggable points
	for (int i = 0; i < m_points.size(); ++i) {
		QPointF point = m_points[i];
		DraggableEllipse *ellipse = new DraggableEllipse(point.x(), point.y(), POINT_RADIUS, i, this);
		ellipse->setScene(scene());
		ellipse->zOrderPutOnTop(ellipse);
		connect(ellipse, &DraggableEllipse::pointMoved, this, &PolygonItem::updatePolygonPoint);
		connect(ellipse, &DraggableEllipse::pointClicked, [this]() {
			itemSelected(this);
		});
		m_draggablePoints.append(ellipse);
	}
}

void PolygonItem::updateBothPoints(int index, QPointF newPos)
{
	updateDraggablePoint(index, newPos);
	updatePolygonPoint(index, newPos);
}

void PolygonItem::updateDraggablePoint(int index, QPointF newPos) {
	if (index >= 0 && index < m_draggablePoints.size()) {
		m_draggablePoints[index]->setX(newPos.x() - POINT_RADIUS);
		m_draggablePoints[index]->setY(newPos.y() - POINT_RADIUS);
		m_draggablePoints[index]->update();
	}
}

void PolygonItem::updatePolygonPoint(int index, QPointF newPos) {
	if (index >= 0 && index < m_points.size()) {
		m_points[index] = newPos;
		m_polygon.replace(index, newPos);
		emit pointUpdated(index, newPos);
		update();
	}
}

void PolygonItem::paintFigure(QPainter *painter) {
	painter->setRenderHint(QPainter::Antialiasing);

	// Draw the polygon
	painter->setPen(Qt::black);
	painter->setBrush(Qt::transparent);
	painter->drawPolygon(m_polygon);

	for (auto draggablePoint : m_draggablePoints) {
		draggablePoint->paintFigure(painter);
	}
}

void PolygonItem::setScene(CustomScene *scene)
{
	SceneItem::setScene(scene);
	for (auto point : m_draggablePoints)
	{
		point->setScene(scene);
	}
}

bool PolygonItem::handleMousePress(QMouseEvent *event) {
	QPointF clickPos = event->pos();
	if (event->buttons() & Qt::LeftButton)
	{
		for (int i = 0; i < m_points.size() - 1; ++i) {
			if (Geometry().shortestDistanceToSegment(clickPos, m_points[i], m_points[i+1]) < ACTIVATE_LINE_DISTANCE) {
				m_selectedLineIndex = i;
				m_oldPos = clickPos;
				itemSelected(this);
				return true;
			}
		}
		if (m_points.size() >= 2 and Geometry().shortestDistanceToSegment(clickPos, m_points.first(), m_points.last()) < ACTIVATE_LINE_DISTANCE) {
			m_selectedLineIndex = m_points.size() - 1;
			m_oldPos = clickPos;
			itemSelected(this);
			return true;
		}
	}
	m_selectedLineIndex = -1;
	return false;
}

bool PolygonItem::handleMouseMove(QMouseEvent *event) {
	if (event->buttons() & Qt::LeftButton and m_selectedLineIndex >= 0 && m_selectedLineIndex < m_points.size()) {
		moveToNewPosition(event->pos());
		return true;
	}
	return false;
}

void PolygonItem::moveToNewPosition(QPointF newPos)
{
	auto oldPolygon = polygon();
	QPolygonF newPolygon;
	auto diff = newPos - m_oldPos;
	std::transform(oldPolygon.begin(), oldPolygon.end(), std::back_inserter(newPolygon), [&newPos, this](QPointF point){
		return point + newPos - m_oldPos;
	});

	m_oldPos = newPos;
	m_polygon = newPolygon;
	m_points = newPolygon.toList();
	emit polygonChanged();
	std::for_each(m_draggablePoints.begin(), m_draggablePoints.end(), [&diff](DraggableEllipse * el){
		el->move(diff.x(), diff.y());
	});
	update();
}

namespace json
{
	Json::Value toJson(const PolygonItem &item)
	{
		Json::Value value;
		value["x"] = item.x();
		value["y"] = item.y();
		value["points"] = Json::Value(Json::arrayValue);
		auto &pointsJson = value["points"];
		for (auto point : item.polygon())
		{
			Json::Value pointJson;
			pointJson["x"] = point.x();
			pointJson["y"] = point.y();
			pointsJson.append(pointJson);
		}
		return value;
	}

    std::unique_ptr<PolygonItem> fromJson(const Json::Value &value)
    {
        auto item = std::make_unique<PolygonItem>();
		item->setX(value["x"].asDouble());
		item->setX(value["y"].asDouble());
		auto &pointsJson = value["points"];
		QPolygonF polygon;
		for (const auto &pointJson : pointsJson)
		{
			polygon.append(QPointF(pointJson["x"].asDouble(), pointJson["y"].asDouble()));
		}
		item->setPolygon(polygon);
		return item;
    }
}
