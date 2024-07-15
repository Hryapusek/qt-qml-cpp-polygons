#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QPointF>

class Geometry
{
public:
    // Function to calculate the squared distance between two points
	double distanceSquared(const QPointF& p1, const QPointF& p2);

    // Function to calculate the shortest distance from a point to a finite line segment
	double shortestDistanceToSegment(const QPointF& point, const QPointF& lineStart, const QPointF& lineEnd);
};

#endif
