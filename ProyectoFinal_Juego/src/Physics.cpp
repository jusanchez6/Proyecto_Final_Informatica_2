/**
 * @file Physics.hpp
 * @brief Implementaciones de las utilidades de física para el juego
 * @authors John Tristancho
 *          Julian Sanchez
 * 
 * @date 29/11/2025
 * @version 1.0
 */

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

QPointF Physics::projectile(float t, const QPointF &origin, const QPointF &velocity, float gravity)
{
    float x = origin.x() + velocity.x() * t;
    float y = origin.y() + velocity.y() * t + 0.5f * gravity * t * t;
    return QPointF(x, y);
}

// Devuelve un velocity vector (vx, vy) que apunta hacia 'target' con magnitud speed.
// Esto no resuelve arcos por altura, es dirección simple.
QPointF Physics::velocityToTarget(const QPointF &origin, const QPointF &target, float speed)
{
    QPointF d = target - origin;
    float dist = qSqrt(d.x() * d.x() + d.y() * d.y());
    if (dist <= 1e-6f)
        return QPointF(0, 0);
    return QPointF(d.x() / dist * speed, d.y() / dist * speed);
}
