#include "geometry/Geometry.h"

#include <cmath>

// Function to calculate the squared distance between two points
double Geometry::distanceSquared(const QPointF& p1, const QPointF& p2) {
    double dx = p2.x() - p1.x();
    double dy = p2.y() - p1.y();
    return dx * dx + dy * dy;
}

// Function to calculate the shortest distance from a point to a finite line segment
double Geometry::shortestDistanceToSegment(const QPointF& point, const QPointF& lineStart, const QPointF& lineEnd) {
    double x1 = lineStart.x();
    double y1 = lineStart.y();
    double x2 = lineEnd.x();
    double y2 = lineEnd.y();
    double x3 = point.x();
    double y3 = point.y();

    // Calculate the squared length of the line segment
    double segmentLengthSquared = distanceSquared(lineStart, lineEnd);

    // Handle the case when the line segment is a point
    if (segmentLengthSquared == 0.0) {
        return std::sqrt(distanceSquared(point, lineStart));
    }

    // Project point onto the line (parameterized)
    double t = ((x3 - x1) * (x2 - x1) + (y3 - y1) * (y2 - y1)) / segmentLengthSquared;

    // Clamp t to the range [0, 1] to find the closest point on the segment
    t = std::max(0.0, std::min(1.0, t));

    // Calculate the closest point on the segment
    QPointF closestPoint(x1 + t * (x2 - x1), y1 + t * (y2 - y1));

    // Return the distance from the point to the closest point on the segment
    return std::sqrt(distanceSquared(point, closestPoint));
}
