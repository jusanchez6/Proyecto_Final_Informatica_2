#include "Physics.hpp"

// Movimiento oscilatorio vertical (humo)
QPointF Physics::oscillatory(float t, float amplitude, float freq, const QPointF &origin)
{
    float dy = amplitude * qSin(freq * t);
    return QPointF(origin.x(), origin.y() + dy);
}

// Movimiento aleatorio amortiguado (fuego)
QPointF Physics::randomDrift(float t, float intensity, const QPointF &origin)
{
    Q_UNUSED(t);
    float dx = ((QRandomGenerator::global()->bounded(2001) - 1000) / 1000.0f) * intensity;
    float dy = ((QRandomGenerator::global()->bounded(2001) - 1000) / 1000.0f) * intensity;

    return QPointF(origin.x() + dx, origin.y() + dy);
}

// Movimiento con amortiguación (inercial)
QPointF Physics::dampedFollow(const QPointF &current, const QPointF &target, float damping)
{
    QPointF delta = target - current;
    return current + delta * damping;
}
