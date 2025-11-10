#ifndef PHYSICS_HPP

#define PHYSICS_HPP

#include <QPointF>
#include <QtMath>
#include <QRandomGenerator>

class Physics
{
public:
    static QPointF oscillatory(float t, float amplitude, float freq, const QPointF& origin);
    static QPointF randomDrift(float t, float intensity, const QPointF& origin);
    static QPointF dampedFollow(const QPointF& current, const QPointF& target, float damping);
};



#endif