#pragma once
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QList>
#include <QKeyEvent>
#include "Player.hpp"
#include "Physics.hpp"

#define LEVEL_ID 2

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
    void setView(QGraphicsView *view); // nuevo método
    void keyReleaseEvent(QKeyEvent *event);


signals:
    void levelCompleted();

private slots:
    void updateScene();
    void spawnRock();
    void updateTimer();
    void spawnEnemy();

private:
    Player *player;
    QGraphicsTextItem *timerText;
    QTimer gameLoop;
    QTimer spawnTimer;
    QTimer countdown;
    QList<QGraphicsPixmapItem *> projectiles;
    QHash<QGraphicsPixmapItem *, ProjectileData> projectileData;
    int timeLeft;

    float playerVelocityY = 0.0f;
    float groundLevel = 680.0f;
    float playerVelocityX = 0.0f;
    const float gravity = 0.3f;
    const float moveSpeed = 3.0f;
    const float jumpStrength = 9.0f;
    bool onGround = false;

    QList<QGraphicsPixmapItem *> enemies;
    QTimer enemyTimer;

    float t; // tiempo acumulado para la física parabólica
};
