/**
 * @file Plane.hpp
 * @brief Implementación de la clase para aviones en el juego
 * @authors John Tristancho
 *          Julian Sanchez
 * 
 * @date 29/11/2025
 * @version 1.0
 */
#include <Plane.hpp>

Plane::Plane(const QPixmap &pix, const QPointF &pos, const QPointF &velocity)
    : QGraphicsPixmapItem(pix), m_velocity(velocity), m_state(Cruising),
      m_holdCenter(pos), m_holdRadius(60.0f), m_holdOmega(1.0f), m_holdAngle(0.0f)
{
    setPos(pos);
    setTransformOriginPoint(boundingRect().center());
}

void Plane::update(float dt)
{

    if (m_state == Cruising)
    {
        QPointF p = pos() + m_velocity * dt;
        setPos(p);
    }
    else if (m_state == Holding)
    {
        m_holdAngle += m_holdOmega * dt;
        QPointF p = m_holdCenter + QPointF(m_holdRadius * qCos(m_holdAngle), m_holdRadius * qSin(m_holdAngle));
        
        setPos(p);
    } else if (m_state == Descending) {

        QPointF v = m_velocity + QPointF(0, 30.0f * dt);
        QPointF p = pos() + v * dt;
        m_velocity = v;
        setPos(p);
    }
}

QPointF Plane::predictPos(float t) const {
    if (m_state == Cruising) {
        return pos() + m_velocity * t;
    } else if (m_state == Holding)
    {
        float futureAngle = m_holdAngle + m_holdOmega * t;
        return m_holdCenter + QPointF(m_holdRadius * qCos(futureAngle), m_holdRadius * qSin(futureAngle));
    } else {
        return pos() + m_velocity * t + QPointF(0, 0.5f * 30.0f * t * t);
    }   
}