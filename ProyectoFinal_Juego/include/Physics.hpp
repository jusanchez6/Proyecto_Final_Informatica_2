/**
 * @file Physics.hpp
 * @brief Utilidades de física para el juego
 * @authors John Tristancho
 *          Julian Sanchez
 * 
 * @date 29/11/2025
 * @version 1.0
 */

#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <QPointF>
#include <QtMath>
#include <QRandomGenerator>

/**
 * @brief Clase de utilidades de física para movimientos y cálculos
 */
class Physics
{
public:
    /**
     * @brief Calcula movimiento oscilatorio
     * @param t Tiempo
     * @param amplitude Amplitud de oscilación
     * @param freq Frecuencia de oscilación
     * @param origin Punto de origen
     * @return Posición oscilatoria
     */
    static QPointF oscillatory(float t, float amplitude, float freq, const QPointF& origin);
    
    /**
     * @brief Calcula movimiento de deriva aleatoria
     * @param t Tiempo
     * @param intensity Intensidad de la deriva
     * @param origin Punto de origen
     * @return Posición con deriva aleatoria
     */
    static QPointF randomDrift(float t, float intensity, const QPointF& origin);
    
    /**
     * @brief Calcula seguimiento con amortiguación
     * @param current Posición actual
     * @param target Posición objetivo
     * @param damping Factor de amortiguación
     * @return Nueva posición amortiguada
     */
    static QPointF dampedFollow(const QPointF& current, const QPointF& target, float damping);
    
    /**
     * @brief Calcula trayectoria de proyectil
     * @param t Tiempo
     * @param origin Punto de origen
     * @param velocity Velocidad inicial
     * @param gravity Gravedad aplicada
     * @return Posición del proyectil
     */
    static QPointF projectile(float t, const QPointF &origin, const QPointF &velocity, float gravity = 9.8f);
    
    /**
     * @brief Calcula velocidad hacia un objetivo
     * @param origin Punto de origen
     * @param target Punto objetivo
     * @param speed Velocidad deseada
     * @return Vector velocidad normalizado
     */
    static QPointF velocityToTarget(const QPointF &origin, const QPointF &target, float speed);
};

#endif