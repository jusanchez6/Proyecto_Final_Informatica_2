#include "Level2Scene.hpp"
#include <QRandomGenerator>
#include <QGraphicsView>
#include <QDebug>
#include <QtMath>

QMediaPlayer *Level2Scene::musicPlayer = nullptr;
QMediaPlaylist *Level2Scene::playlist = nullptr;

Level2Scene::Level2Scene(QObject *parent)
    : QGraphicsScene(parent),
      timeLeft(10),
      t(0.0f)
{

    setSceneRect(0, 0, 736, 841);

    QPixmap bg(":/assets/backgrounds/Bg_level2.jpg");

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

    playerLives = 5;
    invulnerable = false;
    damageTimer.start();

    QString hearts;

    for (int i = 0; i < playerLives; i++)
    {
        hearts += "❤️";
    }
    livesText = addText(hearts, QFont("Arial", 16));
    livesText->setPos(10, 30);
    livesText->setDefaultTextColor(Qt::red);

    damageFlash = addRect(sceneRect(), QPen(Qt::NoPen), QBrush(QColor(255, 0, 0, 0)));
    damageFlash->setZValue(50);

    // Timers
    connect(&gameLoop, &QTimer::timeout, this, &Level2Scene::updateScene);
    connect(&spawnTimer, &QTimer::timeout, this, &Level2Scene::spawnRock);
    connect(&countdown, &QTimer::timeout, this, &Level2Scene::updateTimer);

    // enemigos
    connect(&enemyTimer, &QTimer::timeout, this, &Level2Scene::spawnEnemy);
    enemyTimer.start(2500);

    // musica
    if (!musicPlayer)
    {
        playlist = new QMediaPlaylist();
        QString base = QCoreApplication::applicationDirPath();
        QString soundPath = base + "/resources/music/level_2.wav";

        playlist->addMedia(QUrl::fromLocalFile(soundPath));playlist->setPlaybackMode(QMediaPlaylist::Loop);

        musicPlayer = new QMediaPlayer();
        musicPlayer->setPlaylist(playlist);
        musicPlayer->setVolume(20);
        musicPlayer->play();
    }

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
        playerDirection = -1;
        playerVelocityX = -moveSpeed;
        break;

    case Qt::Key_D:
    case Qt::Key_Right:
        player->setAnimationRow(2);
        playerDirection = 1;
        playerVelocityX = moveSpeed;
        break;

    case Qt::Key_Space:
        shootBullet();
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

        if (p->y() > 841)
        {
            toRemove.append(p);
            continue;
        }

        if (player->collidesWithItem(p))
        {
            if (!invulnerable && damageTimer.elapsed() > 1000)
            {
                invulnerable = true;
                damageTimer.restart();
                QTimer::singleShot(1000, [this]()
                                   { invulnerable = false; });

                damageFlash->setBrush(QColor(255, 0, 0, 100)); // flash rojo
                QTimer::singleShot(150, [this]()
                                   {
                                       damageFlash->setBrush(QColor(255, 0, 0, 0)); // desaparece
                                   });

                // restar la vida y actualizar el HUD
                playerLives = std::max(0, playerLives - 1);
                livesText->setPlainText(QString("❤️").repeated(playerLives));

                // Agrega un segundo de penalización
                timeLeft = std::max(0, timeLeft + 1);
                timerText->setPlainText(QString("Tiempo: %1").arg(timeLeft));

                if (playerLives == 0)
                {
                    timerText->setDefaultTextColor(Qt::red);
                    timerText->setPlainText("¡Has perdido todas tus vidas!");
                    gameLoop.stop();
                    countdown.stop();
                    return;
                }
            }
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

    for (auto *bullet : bullets)
    {
        int dir = bullet->data(0).toInt();
        bullet->moveBy(8 * dir, 0);

        bool hit = false;

        for (auto *enemy : enemies)
        {
            if (bullet->collidesWithItem(enemy))
            {
                hit = true;

                // Invertir dirección actual del enemigo
                int dirEnemy = enemy->data(0).toInt();
                enemy->setData(0, -dirEnemy);

                // Cambiar animación según dirección
                enemy->setAnimationRow(dirEnemy == 1 ? 2 : 1);

                break;
            }
        }

        if (hit || bullet->x() < 0 || bullet->x() > sceneRect().width())
        {
            removeItem(bullet);
            bullets.removeOne(bullet);
            delete bullet;
            break;
        }
    }

    for (auto *enemy : enemies)
    {
        int dir = enemy->data(0).toInt();  // 1 = derecha, -1 = izquierda
        enemy->setX(enemy->x() + 2 * dir); // usa su propia dirección
        enemy->setAnimationRow(dir == 1 ? 2 : 1);

        if (player->collidesWithItem(enemy))
        {
            if (!invulnerable && damageTimer.elapsed() > 1000)
            {
                invulnerable = true;
                damageTimer.restart();
                QTimer::singleShot(1000, [this]()
                                   { invulnerable = false; });

                damageFlash->setBrush(QColor(255, 0, 0, 100)); // flash rojo
                QTimer::singleShot(150, [this]()
                                   {
                                       damageFlash->setBrush(QColor(255, 0, 0, 0)); // desaparece
                                   });

                // restar la vida y actualizar el HUD
                playerLives = std::max(0, playerLives - 1);
                livesText->setPlainText(QString("❤️").repeated(playerLives));

                // Agrega un segundo de penalización
                timeLeft = std::max(0, timeLeft + 1);
                timerText->setPlainText(QString("Tiempo: %1").arg(timeLeft));

                if (playerLives == 0)
                {
                    timerText->setDefaultTextColor(Qt::red);
                    timerText->setPlainText("¡Has perdido todas tus vidas!");
                    gameLoop.stop();
                    countdown.stop();
                    return;
                }
            }
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

void Level2Scene::shootBullet()
{
    auto *bullet = addPixmap(QPixmap(":/assets/sprites/bullet.png").scaled(32, 32));
    bullet->setPos(player->x() + player->boundingRect().width() / 2,
                   player->y() + player->boundingRect().height() / 2);

    bullet->setData(0, QVariant(playerDirection)); // guardar dirección
    bullets.append(bullet);
}

void Level2Scene::spawnRock()
{
    auto *rock = addPixmap(QPixmap(":/assets/sprites/Level2_rock.png").scaled(32, 32));
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
    AnimatedSprite *enemy = new AnimatedSprite(":/assets/sprites/enemigo.png", 3, 4);

    // Elegir lado aleatoriamente (0 = izquierda, 1 = derecha)
    bool fromLeft = QRandomGenerator::global()->bounded(2) == 0;

    int dir = fromLeft ? 1 : -1; // dirección inicial
    enemy->setData(0, dir);      // guardar dirección

    // Crear sprite animado (o pixmap si no usas AnimatedSprite)
    enemy->setScale(1.5);
    enemy->setAnimationRow(fromLeft ? 2 : 1);
    enemy->start(120);

    // Posición inicial
    float x = fromLeft ? -50 : sceneRect().width() + 50;
    enemy->setPos(x, groundLevel + enemy->boundingRect().height());

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
        timerText->setPlainText("¡Nivel superado!");
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

void Level2Scene::stopMusic()
{
    if (musicPlayer) {
        musicPlayer->stop();
        delete musicPlayer;
        musicPlayer = nullptr;

        delete playlist;
        playlist = nullptr;
    }
}
