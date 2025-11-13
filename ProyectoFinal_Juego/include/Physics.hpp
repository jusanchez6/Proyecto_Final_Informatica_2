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
    static QPointF projectile(float t, const QPointF &origin, const QPointF &velocity, float gravity = 9.8f);
    static QPointF velocityToTarget(const QPointF &origin, const QPointF &target, float speed);


};



#endif