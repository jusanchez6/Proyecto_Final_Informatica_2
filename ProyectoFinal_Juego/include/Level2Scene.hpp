#pragma once

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


#include "Player.hpp"
#include "Physics.hpp"
#include "AnimatedSprite.hpp"


struct ProjectileData
{
    QPointF origin;
    QPointF velocity;
    float t;
    float gravity;
};

class Level2Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Level2Scene(QObject *parent = nullptr);

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void setView(QGraphicsView *view);
    void shootBullet();

signals:
    void levelCompleted();

private slots:
    void updateScene();
    void spawnRock();
    void updateTimer();
    void spawnEnemy();

private:
    // Jugador
    Player *player = nullptr;
    float playerVelocityX = 0.0f;
    float playerVelocityY = 0.0f;
    const float gravity = 0.3f;
    const float moveSpeed = 3.0f;
    const float jumpStrength = 10.0f;
    bool onGround = true;
    int playerDirection = 1; // 1 = derecha, -1 = izquierda

    // ⏱Timers
    QTimer gameLoop;
    QTimer spawnTimer;
    QTimer countdown;
    QTimer enemyTimer;

    // Física
    float groundLevel = 680.0f;
    float t = 0.0f; // tiempo acumulado para trayectorias parabólicas

    // HUD
    QGraphicsTextItem *timerText = nullptr;
    int timeLeft = 0;

    int playerLives;

    bool invulnerable;
    QElapsedTimer damageTimer;
    QGraphicsTextItem *livesText;
    QGraphicsRectItem *damageFlash;

    // Proyectiles (rocas que caen)
    QList<QGraphicsPixmapItem *> projectiles;
    QHash<QGraphicsPixmapItem *, ProjectileData> projectileData;

    // Enemigos animados
    QList<AnimatedSprite *> enemies;
    uint velEnemy = -2;

    // Balas del jugador
    QList<QGraphicsPixmapItem *> bullets;
};
