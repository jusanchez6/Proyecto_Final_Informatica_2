/**
 * @file Plane.hpp
 * @brief Clase para aviones en el juego
 * @authors John Tristancho
 *          Julian Sanchez
 * 
 * @date 29/11/2025
 * @version 1.0
 */

#ifndef PLANE_HPP
#define PLANE_HPP

#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QtMath>

/**
 * @brief Clase que representa un avión en el juego
 */
class Plane : public QGraphicsPixmapItem
{
public:
    /**
     * @brief Estados del avión
     */
    enum State
    {
        Cruising,   ///< Navegando normalmente
        Holding,    ///< En patrón de espera
        Descending  ///< Descendiendo
    };

    /**
     * @brief Constructor del avión
     * @param pix Imagen del avión
     * @param pos Posición inicial
     * @param velocity Velocidad inicial
     */
    Plane(const QPixmap &pix, const QPointF &pos, const QPointF &velocity);

    /**
     * @brief Obtiene la velocidad del avión
     * @return Velocidad actual
     */
    QPointF velocity() const { return m_velocity; }

    /**
     * @brief Establece la velocidad del avión
     * @param v Nueva velocidad
     */
    void setVelocity(const QPointF &v) { m_velocity = v; }

    /**
     * @brief Establece el estado del avión
     * @param s Nuevo estado
     */
    void setState(State s) {m_state = s; }

    /**
     * @brief Obtiene el estado del avión
     * @return Estado actual
     */
    State state() const { return m_state; }

    /**
     * @brief Actualiza el avión
     * @param dt Tiempo transcurrido
     */
    void update(float dt);

    /**
     * @brief Predice la posición futura
     * @param t Tiempo futuro
     * @return Posición predicha
     */
    QPointF predictPos(float t) const;

private:
    QPointF m_velocity;     ///< Velocidad del avión
    State m_state;          ///< Estado actual
    QPointF m_holdCenter;   ///< Centro del patrón de espera

    float m_holdRadius;     ///< Radio del patrón de espera
    float m_holdOmega;      ///< Velocidad angular del patrón
    float m_holdAngle;      ///< Ángulo actual del patrón
};

#endif