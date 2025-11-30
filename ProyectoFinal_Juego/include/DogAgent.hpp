/**
 * @file DogAgent.hpp
 * @brief Clase para el agente canino inteligente en el juego
 * @authors John Tristancho
 *          Julian Sanchez
 * 
 * @date 29/11/2025
 * @version 1.0
 */

#ifndef DOGAGENT_HPP

#define DOGAGENT_HPP

#include <AnimatedSprite.hpp>
#include <QtMath>
#include <QDebug>
#include <QList>
#include <QPointF>
#include <QSoundEffect>

/**
 * @brief Agente canino con comportamiento inteligente
 * 
 * Representa un perro que puede percibir el entorno, tomar decisiones
 * y aprender de experiencias peligrosas.
 * 
 * @inherits AnimatedSprite
 */
class DogAgent : public AnimatedSprite
{
public:
    /**
     * @brief Constructor del agente canino
     */
    DogAgent();

    /**
     * @brief Actualiza el estado del agente
     * @param dt Tiempo transcurrido desde la última actualización
     */
    void update(float dt);

    /**
     * @brief Percibe el entorno del agente
     * @param fires Lista de fuegos en el escenario
     * @param playerPos Posición del jugador
     * @param refuge Refugio seguro
     */
    void perceive(const QList<QGraphicsPixmapItem*> &fires, const QPointF &playerPos, const QGraphicsItem *refuge);

    /**
     * @brief Ejecuta la acción decidida por el agente
     */
    void act();

    /**
     * @brief Aprende de una posición peligrosa
     * @param dangerPos Posición del peligro a recordar
     */
    void learn(const QPointF &dangerPos);

private:
    QPointF target;             ///< Objetivo actual del movimiento
    QPointF velocity;           ///< Velocidad actual del agente
    QList<QPointF> memory;      ///< Memoria de posiciones peligrosas
    bool dangerNearby;          ///< Indica si hay peligro cercano

    QPointF lastDir;            ///< Última dirección de movimiento
    int lastRow;                ///< Última fila de animación usada
    QPointF lastTarget;         ///< Último objetivo perseguido

    QSoundEffect barkSound;     ///< Efecto de sonido de ladrido
};

#endif