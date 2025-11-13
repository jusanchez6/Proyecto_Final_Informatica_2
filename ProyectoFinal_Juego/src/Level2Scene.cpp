#include "Level2Scene.hpp"
#include <QRandomGenerator>
#include <QGraphicsView>
#include <QDebug>
#include <QtMath>

Level2Scene::Level2Scene(QObject *parent)
    : QGraphicsScene(parent),
      timeLeft(25),
      t(0.0f)
{

    setSceneRect(0, 0, 736, 841);

    QPixmap bg("../assets/backgrounds/Bg_level2.jpg");

    if (!bg.isNull())
    {
        QGraphicsPixmapItem *background = addPixmap(bg.scaled(736, 841));
        background->setZValue(-100);
    }
    else
    {
        qWarning() << "No se pudo cargar el fondo.";
    }


    // Jugador
    player = new Player(2);
    addItem(player);
    player->scaleFactor = 2.0f;
    player->setPos(100, 841);
    player->setFlags(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // Texto del tiempo
    timerText = addText("Tiempo: 25", QFont("Arial", 16));
    timerText->setDefaultTextColor(Qt::white);
    timerText->setPos(10, 10);

    // Timers
    connect(&gameLoop, &QTimer::timeout, this, &Level2Scene::updateScene);
    connect(&spawnTimer, &QTimer::timeout, this, &Level2Scene::spawnRock);
    connect(&countdown, &QTimer::timeout, this, &Level2Scene::updateTimer);

    // enemigos
    connect(&enemyTimer, &QTimer::timeout, this, &Level2Scene::spawnEnemy);
    enemyTimer.start(3000);

    gameLoop.start(16);
    spawnTimer.start(1500);
    countdown.start(1000);
}

void Level2Scene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_A:
    case Qt::Key_Left:
        player->setAnimationRow(1);
        playerVelocityX = -moveSpeed;
        break;

    case Qt::Key_D:
    case Qt::Key_Right:
        player->setAnimationRow(2);
        playerVelocityX = moveSpeed;
        break;

    case Qt::Key_W:
    case Qt::Key_Up:
        if (onGround)
        {
            playerVelocityY = -jumpStrength;
            onGround = false;
        }
        break;

    default:
        break;
    }
}

void Level2Scene::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left ||
        event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
    {
        playerVelocityX = 0.0f;
        player->setAnimationRow(0);
    }
}
// Actualiza físicas y colisiones
void Level2Scene::updateScene()
{
    QList<QGraphicsPixmapItem *> toRemove;

    for (auto *p : projectiles)
    {
        auto &data = projectileData[p];
        data.t += 0.016f;

        QPointF newPos = Physics::projectile(data.t, data.origin, data.velocity, data.gravity);
        p->setPos(newPos);

        if (p->y() > 600)
        {
            toRemove.append(p);
            continue;
        }

        if (player->collidesWithItem(p))
        {
            timerText->setPlainText("💥 ¡Golpeado!");
            timerText->setDefaultTextColor(Qt::red);
            gameLoop.stop();
            spawnTimer.stop();
            countdown.stop();
            return;
        }
    }

    for (auto *r : toRemove)
    {
        removeItem(r);
        projectileData.remove(r);
        projectiles.removeOne(r);
        delete r;
    }

    playerVelocityY += gravity;
    player->setPos(player->x() + playerVelocityX, player->y() + playerVelocityY);

    // Colisión con el suelo
    if (player->y() >= groundLevel)
    {
        player->setY(groundLevel);
        playerVelocityY = 0.0f;
        onGround = true;
    }

    for (auto *enemy : enemies)
    {
        enemy->setX(enemy->x() - 2); // velocidad constante hacia la izquierda

        if (player->collidesWithItem(enemy))
        {
            timerText->setPlainText("💀 ¡Te alcanzaron!");
            timerText->setDefaultTextColor(Qt::red);
            gameLoop.stop();
            spawnTimer.stop();
            countdown.stop();
            enemyTimer.stop();
            return;
        }
    }

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                                 [&](QGraphicsPixmapItem *e)
                                 {
                                     if (e->x() < -50)
                                     {
                                         removeItem(e);
                                         delete e;
                                         return true;
                                     }
                                     return false;
                                 }),
                  enemies.end());
}

void Level2Scene::spawnRock()
{
    auto *rock = addPixmap(QPixmap("../assets/sprites/Level2_rock.png").scaled(32, 32));
    float x = QRandomGenerator::global()->bounded(200, 780);
    rock->setPos(x, 0);

    // Datos iniciales
    ProjectileData data;
    data.origin = rock->pos();
    data.velocity = QPointF(
        (QRandomGenerator::global()->bounded(-40, 41) / 10.0f), // vx
        QRandomGenerator::global()->bounded(50, 70) / 10.0f     // vy
    );
    data.t = 0.0f;
    data.gravity = 15.0f;

    projectileData[rock] = data;
    projectiles.append(rock);
}

void Level2Scene::spawnEnemy()
{
    // Crear enemigo animado
    AnimatedSprite *enemy = new AnimatedSprite("../assets/sprites/enemigo.png", 3, 4);
    enemy->setAnimationRow(1);  // fila inicial de animación
    enemy->setScale(1.7);       // ajustá el tamaño según tu sprite
    enemy->start(120);          // velocidad de animación (ms por frame)
    enemy->setPos(800, groundLevel + enemy->boundingRect().height()); // aparece justo sobre el suelo

    addItem(enemy);
    enemies.append(enemy);
}

// Temporizador de nivel
void Level2Scene::updateTimer()
{
    timeLeft--;
    timerText->setPlainText(QString("Tiempo: %1").arg(timeLeft));

    if (timeLeft <= 0)
    {
        timerText->setDefaultTextColor(Qt::green);
        timerText->setPlainText("✅ ¡Nivel superado!");
        gameLoop.stop();
        spawnTimer.stop();
        countdown.stop();
        emit levelCompleted();
    }
}

void Level2Scene::setView(QGraphicsView *view)
{
    view->setFocusPolicy(Qt::StrongFocus); // Permite que el view capture teclas
    view->setScene(this);
    player->setFocus(); // Da el foco al jugador dentro de la escena
}
