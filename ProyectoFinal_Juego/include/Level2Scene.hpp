/**
 * @file Level2Scene.hpp
 * @brief Escena del segundo nivel del juego
 * @authors John Tristancho
 *          Julian Sanchez
 *
 * @date 29/11/2025
 * @version 1.0
 */

#ifndef LEVEL2SCENE_HPP
#define LEVEL2SCENE_HPP

#include <QCoreApplication>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QList>
#include <QKeyEvent>
#include <QHash>
#include <QGraphicsView>
#include <QElapsedTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QString>
#include "Player.hpp"
#include "Physics.hpp"
#include "AnimatedSprite.hpp"

/**
 * @brief Datos de proyectiles en movimiento parabólico
 */
struct ProjectileData
{
    QPointF origin;   ///< Punto de origen del proyectil
    QPointF velocity; ///< Velocidad inicial del proyectil
    float t;          ///< Tiempo transcurrido
    float gravity;    ///< Gravedad aplicada
};

/**
 * @brief Escena del segundo nivel del juego
 *
 * Nivel con mecánicas de plataformas, enemigos y proyectiles
 */
class Level2Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la escena del nivel 2
     * @param parent Objeto padre
     */
    explicit Level2Scene(QObject *parent = nullptr);

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
     * @brief Establece la vista gráfica para la escena
     * @param view Vista gráfica a establecer
     */
    void setView(QGraphicsView *view);

    /**
     * @brief Dispara una bala desde el jugador
     */
    void shootBullet();

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
     * @brief Genera una nueva roca en el nivel
     */
    void spawnRock();

    /**
     * @brief Actualiza el temporizador del nivel
     */
    void updateTimer();

    /**
     * @brief Genera un nuevo enemigo en el nivel
     */
    void spawnEnemy();

private:
    Player *player;                   ///< Jugador principal
    float playerVelocityX = 0.0f;     ///< Velocidad horizontal del jugador
    float playerVelocityY = 0.0f;     ///< Velocidad vertical del jugador
    const float gravity = 0.3f;       ///< Gravedad del nivel
    const float moveSpeed = 3.0f;     ///< Velocidad de movimiento
    const float jumpStrength = 10.0f; ///< Fuerza de salto
    bool onGround = true;             ///< Indica si el jugador está en el suelo
    int playerDirection = 1;          ///< Dirección del jugador

    QTimer gameLoop;   ///< Timer del bucle principal
    QTimer spawnTimer; ///< Timer de generación de rocas
    QTimer countdown;  ///< Timer de cuenta regresiva
    QTimer enemyTimer; ///< Timer de generación de enemigos

    float groundLevel = 680.f; ///< Nivel del suelo
    float t = 0.0f;            ///< Tiempo acumulado para trayectorias

    QGraphicsTextItem *timerText; ///< Texto del temporizador
    int timeLeft = 0;             ///< Tiempo restante

    int playerLives;                ///< Vidas del jugador
    bool invulnerable;              ///< Estado de invulnerabilidad
    QElapsedTimer damageTimer;      ///< Timer de daño
    QGraphicsTextItem *livesText;   ///< Texto de vidas
    QGraphicsRectItem *damageFlash; ///< Efecto visual de daño

    QList<QGraphicsPixmapItem *> projectiles;                    ///< Lista de proyectiles
    QHash<QGraphicsPixmapItem *, ProjectileData> projectileData; ///< Datos de proyectiles

    QList<AnimatedSprite *> enemies; ///< Lista de enemigos
    uint velEnemy = -2;              ///< Velocidad de enemigos

    QList<QGraphicsPixmapItem *> bullets; ///< Lista de balas del jugador

    static QMediaPlayer *musicPlayer; ///< Reproductor de música
    static QMediaPlaylist *playlist;  ///< Lista de reproducción
};

#endif