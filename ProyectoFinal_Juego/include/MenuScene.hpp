/**
 * @file MenuScene.hpp
 * @brief Escena del menú principal del juego
 * @authors John Tristancho
 *          Julian Sanchez
 * 
 * @date 29/11/2025
 * @version 1.0
 */

#ifndef MENUSCENE_HPP
#define MENUSCENE_HPP

#include <QCoreApplication>

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsPathItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QFont>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <functional>

/**
 * @brief Escena del menú principal del juego
 */
class MenuScene : public QGraphicsScene
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la escena del menú
     * @param startCallback Función para iniciar el juego
     * @param parent Objeto padre
     */
    MenuScene(std::function<void()> startCallback, QObject *parent = nullptr);

    /**
     * @brief Detiene la música del menú
     */
    static void stopMusic();

private:
    std::function<void()> m_startCallback;  ///< Callback para iniciar juego
    static QMediaPlayer *musicPlayer;       ///< Reproductor de música
    static QMediaPlaylist * playlist;       ///< Lista de reproducción

protected:
    /**
     * @brief Maneja eventos de clic del mouse
     * @param event Evento del mouse
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif