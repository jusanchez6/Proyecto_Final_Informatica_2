#ifndef PLANE_HPP
#define PLANE_HPP

#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QtMath>

class Plane : public QGraphicsPixmapItem
{
 

public:
    enum State
    {
        Cruising,
        Holding,
        Descending
    };

    Plane(const QPixmap &pix, const QPointF &pos, const QPointF &velocity);

    QPointF velocity() const { return m_velocity; }
    void setVelocity(const QPointF &v) { m_velocity = v; }

    void setState(State s) {m_state = s; }
    State state() const { return m_state; }

    void update(float dt);

    QPointF predictPos(float t) const;


private:
    QPointF m_velocity;
    State m_state;
    QPointF m_holdCenter;

    float m_holdRadius;
    float m_holdOmega;
    float m_holdAngle;
   

};

#endif