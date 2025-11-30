/**
 * @file Player.hpp
 * @brief Clase del jugador principal
 * @authors John Tristancho
 *          Julian Sanchez
 * 
 * @date 29/11/2025
 * @version 1.0
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <AnimatedSprite.hpp>
#include <QKeyEvent>
#include <QGraphicsScene>

/**
 * @brief Clase del jugador principal del juego
 */
class Player : public AnimatedSprite {
public:
    /**
     * @brief Constructor del jugador
     * @param level Nivel actual del jugador
     */
    Player(int level);

    /**
     * @brief Maneja eventos de teclas presionadas
     * @param event Evento de tecla
     */
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief Maneja eventos de teclas liberadas
     * @param event Evento de tecla
     */
    void keyReleaseEvent(QKeyEvent *event) override;

    /**
     * @brief Actualiza el estado del jugador
     * @param phase Fase de actualización
     */
    void advance(int phase) override;

    /**
     * @brief Obtiene la velocidad del jugador
     * @return Velocidad actual
     */
    QPointF getVelocity() const { return velocity; }

private:
    QPointF velocity;   ///< Velocidad del jugador
    bool moving;        ///< Indica si el jugador se está moviendo
};

#endif