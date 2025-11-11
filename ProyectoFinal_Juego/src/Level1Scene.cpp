#include "Level1Scene.hpp"
#include <QGraphicsView>
#include <QDebug>

Level1Scene::Level1Scene(QObject *parent)
    : QGraphicsScene(parent), timeLeft(100)
{

    setSceneRect(0, 0, 736, 841);

    QPixmap bg("../assets/backgrounds/Bg_level1.jpg");

    if (!bg.isNull())
    {
        QGraphicsPixmapItem *background = addPixmap(bg.scaled(736, 841));
        background->setZValue(-100);
    }
    else
    {
        qWarning() << "No se pudo cargar el fondo.";
    }

    QList<QRectF> blockedZones = {
        QRectF(7, 717, 35, 102),
        QRectF(6, 627, 40, 71),
        QRectF(4, 9, 12, 26),
        QRectF(4, 58, 19, 31),
        QRectF(4, 106, 13, 41),
        QRectF(0, 184, 17, 52),
        QRectF(35, 237, 48, 15),
        QRectF(98, 233, 46, 7),
        QRectF(153, 239, 42, 21),
        QRectF(217, 262, 21, 29),
        QRectF(252, 304, 32, 22),
        QRectF(296, 314, 32, 26),
        QRectF(308, 361, 25, 26),
        QRectF(300, 403, 17, 21),
        QRectF(321, 442, 22, 17),
        QRectF(349, 474, 31, 14),
        QRectF(394, 491, 14, 12),
        QRectF(414, 510, 16, 27),
        QRectF(409, 561, 23, 22),
        QRectF(45, 330, 30, 21),
        QRectF(91, 340, 43, 16),
        QRectF(161, 342, 41, 19),
        QRectF(189, 379, 30, 29),
        QRectF(201, 420, 33, 18),
        QRectF(254, 448, 29, 22),
        QRectF(268, 480, 18, 15),
        QRectF(157, 504, 22, 10),
        QRectF(187, 497, 33, 11),
        QRectF(225, 482, 21, 17),
        QRectF(142, 544, 16, 15),
        QRectF(141, 572, 18, 13),
        QRectF(150, 592, 20, 15),
        QRectF(187, 609, 26, 21),
        QRectF(201, 643, 17, 16),
        QRectF(225, 660, 18, 10),
        QRectF(248, 650, 19, 8),
        QRectF(278, 639, 20, 5),
        QRectF(310, 624, 18, 7),
        QRectF(322, 587, 17, 11),
        QRectF(356, 598, 20, 9),
        QRectF(381, 589, 23, 9),
        QRectF(315, 605, 12, 11),
        QRectF(85, 5, 14, 10),
        QRectF(92, 25, 21, 17),
        QRectF(88, 53, 25, 19),
        QRectF(122, 73, 20, 10),
        QRectF(153, 79, 35, 16),
        QRectF(203, 101, 38, 14),
        QRectF(255, 112, 39, 13),
        QRectF(307, 131, 22, 18),
        QRectF(297, 155, 20, 17),
        QRectF(318, 178, 20, 16),
        QRectF(352, 184, 22, 13),
        QRectF(388, 191, 17, 8),
        QRectF(416, 209, 11, 30),
        QRectF(411, 253, 16, 31),
        QRectF(436, 295, 13, 13),
        QRectF(435, 324, 17, 30),
        QRectF(437, 367, 10, 20),
        QRectF(437, 394, 10, 16),
        QRectF(448, 416, 20, 12),
        QRectF(488, 431, 19, 12),
        QRectF(527, 444, 16, 7),
        QRectF(556, 429, 18, 15),
        QRectF(455, 3, 32, 13),
        QRectF(503, 17, 27, 12),
        QRectF(535, 41, 18, 44),
        QRectF(538, 88, 47, 22),
        QRectF(588, 117, 36, 18),
        QRectF(644, 138, 28, 14),
        QRectF(663, 163, 13, 46),
        QRectF(496, 260, 21, 11),
        QRectF(524, 253, 27, 13),
        QRectF(560, 243, 37, 9),
        QRectF(614, 230, 17, 8),
        QRectF(632, 214, 15, 7),
        QRectF(55, 690, 24, 24),
        QRectF(66, 745, 69, 64),
        QRectF(260, 807, 45, 15),
        QRectF(295, 791, 29, 9),
        QRectF(346, 780, 43, 6),
        QRectF(408, 764, 11, 11),
        QRectF(422, 742, 17, 9),
        QRectF(433, 724, 23, 5),
        QRectF(467, 715, 26, 8),
        QRectF(496, 691, 11, 12),
        QRectF(506, 665, 14, 12),
        QRectF(523, 659, 27, 9),
        QRectF(550, 644, 19, 5),
        QRectF(569, 634, 26, 8),
        QRectF(598, 629, 19, 8),
        QRectF(617, 606, 17, 21),
        QRectF(624, 579, 13, 14),
        QRectF(631, 542, 15, 15),
        QRectF(646, 523, 16, 9),
        QRectF(664, 511, 17, 10),
        QRectF(671, 493, 17, 13),
        QRectF(679, 467, 14, 11),
        QRectF(689, 442, 13, 10),
        QRectF(705, 447, 6, 7),
        QRectF(553, 397, 20, 9),
        QRectF(560, 364, 10, 15),
        QRectF(573, 341, 11, 16),
        QRectF(596, 350, 22, 15),
        QRectF(621, 330, 16, 14),
        QRectF(642, 316, 18, 18),
        QRectF(666, 329, 15, 16),
        QRectF(687, 348, 21, 14),
        QRectF(2, 365, 26, 19),
        QRectF(11, 408, 13, 10),
        QRectF(5, 431, 16, 16),
        QRectF(4, 492, 13, 47),
        QRectF(3, 556, 18, 51)
    };

    // Guarda estos rectángulos en una lista global
    for (const QRectF &r : blockedZones)
    {
        QGraphicsRectItem *block = addRect(r, QPen(Qt::NoPen), QBrush(Qt::transparent));
        block->setData(0, "blocked"); // marcador para detección
        block->setZValue(5);
        colliders.append(block); // 👉 colliders: QList<QGraphicsItem*> en tu clase
    }

    // Jugador
    player = new Player();
    addItem(player);
    player->setPos(79, 130);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    dog = new DogAgent();
    addItem(dog);
    dog->setPos(200, 400);

    // Refugio
    refuge = addPixmap(QPixmap("../assets/sprites/Level1_debris.png").scaled(48, 48));
    refuge->setPos(700, 280);

    // Obstáculos de fuego
    for (int i = 0; i < 5; ++i)
    {
        auto *fire = addPixmap(QPixmap("../assets/sprites/Level1_fire.png").scaled(32, 32));
        fire->setPos(QRandomGenerator::global()->bounded(150, 700),
                     QRandomGenerator::global()->bounded(100, 500));
        fires.append(fire);
    }

    // Humo oscilante
    smoke = addPixmap(QPixmap("../assets/sprites/Level1_fire.png").scaled(32, 32));
    smoke->setOpacity(0.3);
    smoke->setPos(400, 150);

    // Texto del tiempo
    timerText = addText("Tiempo: 30", QFont("Arial", 16));
    timerText->setPos(10, 10);
    timerText->setDefaultTextColor(Qt::white);

    // Texto de vidas
    playerLives = 5;
    invulnerable = false;
    damageTimer.start();
    QString hearts;
    for (int i = 0; i < playerLives; ++i)
        hearts += "❤️";

    livesText = addText(hearts, QFont("Arial", 16));
    livesText->setPos(10, 30);
    livesText->setDefaultTextColor(Qt::red);

    // Pantalla de daño (transparente al inicio)
    damageFlash = addRect(sceneRect(), QPen(Qt::NoPen), QBrush(QColor(255, 0, 0, 0)));
    damageFlash->setZValue(50);

    // 🔁 Game loop
    connect(&gameLoop, &QTimer::timeout, this, &Level1Scene::updateScene);
    connect(&countdown, &QTimer::timeout, this, &Level1Scene::updateTimer);
    gameLoop.start(16);
    countdown.start(1000);
}

void Level1Scene::updateScene()
{
    // 🔄 Actualiza todos los items que tengan advance()
    advance();

    static float t = 0;
    t += 0.1f;

    // 🌫️ Física 1: movimiento oscilatorio del humo
    QPointF smokeOrigin(400, 150);
    QPointF newPos = Physics::oscillatory(t, 10.0f, 2.0f, smokeOrigin);
    smoke->setPos(newPos);

    // 🔥 Física 2: vibración leve del fuego
    for (auto *fire : fires)
    {
        QPointF origin = fire->pos();
        QPointF drifted = Physics::randomDrift(t, 0.5f, origin);
        fire->setPos(drifted);
    }

    // 🐕 Física 3: movimiento inercial del perro
    QPointF followTarget = player->pos() + QPointF(0, 90); // 👈 más abajito (aumenta el 40 si quieres más distancia)

    dog->perceive(fires, player->pos());

    QPointF newDogPos = Physics::dampedFollow(
        dog->pos(),
        followTarget, // 👈 el nuevo target está debajo del jugador
        0.05f);

    dog->setPos(newDogPos);
    dog->update(0.016f);

    // 🔍 Colisiones
    for (auto *fire : fires)
    {
        if (player->collidesWithItem(fire))
        {
            if (!invulnerable && damageTimer.elapsed() > 1000)
            {
                invulnerable = true;
                damageTimer.restart();

                QTimer::singleShot(1000, [this]()
                                   { invulnerable = false; });

                // Efecto visual de daño
                damageFlash->setBrush(QColor(255, 0, 0, 100)); // flash rojo
                QTimer::singleShot(150, [this]()
                                   {
                                       damageFlash->setBrush(QColor(255, 0, 0, 0)); // desaparece
                                   });

                // Resta vida y actualiza HUD

                playerLives = std::max(0, playerLives - 1);
                livesText->setPlainText(QString("❤️").repeated(playerLives));

                // Penaliza también con 1 segundo
                timeLeft = std::max(0, timeLeft - 1);
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

    if (player->collidesWithItem(refuge))
    {
        qDebug() << "Has llegado al refugio.";
        timerText->setPlainText("¡Has llegado al refugio!");
        emit levelCompleted();
        gameLoop.stop();
        countdown.stop();
    }

    for (auto *block : colliders)
    {
        if (player->collidesWithItem(block))
        {
            // Revertir el último movimiento (sencillo pero efectivo)
            player->moveBy(-player->getVelocity().x(), -player->getVelocity().y());
            break;
        }
    }

    if (playerLives == 1)
    {
        static bool blink = false;
        blink = !blink;
        livesText->setDefaultTextColor(blink ? Qt::red : Qt::white);
    }
    else
    {
        livesText->setDefaultTextColor(Qt::white);
    }
}

void Level1Scene::updateTimer()
{
    timeLeft--;
    timerText->setPlainText(QString("Tiempo: %1").arg(timeLeft));

    if (timeLeft <= 0)
    {
        timerText->setDefaultTextColor(Qt::red);
        timerText->setPlainText("⏰ ¡Tiempo agotado!");
        gameLoop.stop();
        countdown.stop();
    }
}

// 🚀 NUEVO: importante para que las teclas funcionen
void Level1Scene::setView(QGraphicsView *view)
{
    view->setFocusPolicy(Qt::StrongFocus); // Permite que el view capture teclas
    view->setScene(this);
    player->setFocus(); // Da el foco al jugador dentro de la escena
}
