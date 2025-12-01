/**
 * @file Level1Scene.hpp
 * @brief Escena del primer nivel del juego
 * @authors John Tristancho
 *          Julian Sanchez
 * 
 * @date 29/11/2025
 * @version 1.0
 */

#ifndef LEVEL1SCENE_HPP
#define LEVEL1SCENE_HPP

#include <QCoreApplication>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QKeyEvent>
#include <QElapsedTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "Player.hpp"
#include "DogAgent.hpp"
#include "Physics.hpp"

#define LEVEL_ID 1

/**
 * @brief Escena del primer nivel del juego
 * 
 * Gestiona la lógica, elementos y eventos del nivel 1
 */
class Level1Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @brief Constructor de la escena del nivel 1
     * @param parent Objeto padre
     */
    explicit Level1Scene(QObject *parent = nullptr);

    /**
     * @brief Establece la vista gráfica para la escena
     * @param view Vista gráfica a establecer
     */
    void setView(QGraphicsView *view);

    /**
     * @brief Detiene la música del nivel
     */
    static void stopMusic();

signals:
    /**
     * @brief Señal emitida cuando se completa el nivel
     */
    void levelCompleted();

    /**
     * @brief Señal emitida cuando falla el nivel
     * @param reason Razón del fallo
     */
    void levelFailed(const QString &reason);

private slots:
    /**
     * @brief Actualiza el estado de la escena
     */
    void updateScene();

    /**
     * @brief Actualiza el temporizador del nivel
     */
    void updateTimer();

private:
    Player *player;                     ///< Jugador principal
    DogAgent *dog;                      ///< Agente canino
    QList<QGraphicsPixmapItem *> fires; ///< Lista de fuegos en el nivel
    QList<QGraphicsPixmapItem *> smokes;//esto se añadio en los ultimos commits para poder arreglar que el humo se viera bien
    QGraphicsPixmapItem *smoke;         ///< Humo del nivel
    QGraphicsItem *refuge;              ///< Refugio seguro
    QTimer gameLoop;                    ///< Timer del bucle principal
    QTimer countdown;                   ///< Timer de cuenta regresiva
    int timeLeft;                       ///< Tiempo restante
    int playerLives;                    ///< Vidas del jugador
    bool invulnerable;                  ///< Estado de invulnerabilidad
    QElapsedTimer damageTimer;          ///< Timer de daño
    QGraphicsTextItem *timerText;       ///< Texto del temporizador
    QGraphicsTextItem *livesText;       ///< Texto de vidas
    QGraphicsRectItem *damageFlash;     ///< Efecto visual de daño
    QList<QGraphicsItem *> colliders;   ///< Colisionadores del nivel
    static QMediaPlayer *musicPlayer;   ///< Reproductor de música
    static QMediaPlaylist *playlist;    ///< Lista de reproducción
};

#endif
