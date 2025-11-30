/**
 * @file GameController.hpp
 * @brief Controlador principal del juego
 * @authors John Tristancho
 *          Julian Sanchez
 * 
 * @date 29/11/2025
 * @version 1.0
 */

#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <QObject>
#include <QGraphicsView>
#include <QString>
#include <Level1Scene.hpp>
#include <Level2Scene.hpp>
#include <Level3Scene.hpp>
#include <MenuScene.hpp>
#include <InstructionScene.hpp>

/**
 * @brief Controlador principal del juego
 * 
 * Gestiona la navegación entre escenas y niveles del juego
 */
class GameController : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor del controlador del juego
     */
    GameController();

    /**
     * @brief Muestra la escena del menú principal
     */
    void showMenu();

    /**
     * @brief Muestra las instrucciones del nivel
     * @param level Nivel del que mostrar instrucciones
     */
    void showInstructions(int level);

    /**
     * @brief Inicia un nivel del juego
     * @param level Nivel a iniciar
     */
    void startLevel(int level);

    /**
     * @brief Muestra la escena final del juego
     */
    void showEnding();

    /**
     * @brief Muestra la pantalla de game over
     * @param reason Razón del game over
     */
    void showGameOver(const QString &reason);

private:
    QGraphicsView *m_view;      ///< Vista gráfica del juego
};

#endif