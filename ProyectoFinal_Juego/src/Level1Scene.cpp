#include <Level1Scene.hpp>
#include <QGraphicsView>
#include <QDebug>

QMediaPlayer *Level1Scene::musicPlayer = nullptr;
QMediaPlaylist *Level1Scene::playlist = nullptr;

Level1Scene::Level1Scene(QObject *parent)
    : QGraphicsScene(parent), timeLeft(100)
{

    setSceneRect(0, 0, 736, 841);

#ifdef _WIN32
    QPixmap bg(":/assets/backgrounds/Bg_level1.jpg");
#elif defined(__linux__)
    QPixmap bg(":/assets/backgrounds/Bg_level1.jpg");
#endif


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
        QRectF(104, 5, 228, 57),
        QRectF(321, 102, 92, 60),
        QRectF(550, 13, 54, 43),
        QRectF(635, 49, 69, 73),
        QRectF(434, 228, 46, 56),
        QRectF(470, 315, 34, 79),
        QRectF(686, 233, 18, 86),
        QRectF(12, 245, 169, 60),
        QRectF(214, 309, 25, 62),
        QRectF(270, 343, 46, 40),
        QRectF(261, 458, 68, 60),
        QRectF(174, 524, 218, 41),
        QRectF(211, 592, 86, 20),
        QRectF(435, 741, 73, 52),
        QRectF(673, 478, 41, 155),
        QRectF(2, 672, 87, 143),
        QRectF(2, 6, 23, 233),
        QRectF(8, 344, 29, 317)};

    // Guarda estos rectángulos en una lista global
    for (const QRectF &r : blockedZones)
    {
        QGraphicsRectItem *block = addRect(r, QPen(Qt::NoPen), QBrush(Qt::transparent));
        block->setData(0, "blocked"); // marcador para detección
        block->setZValue(5);
        colliders.append(block);
    }

    // Jugador
    player = new Player(LEVEL_ID);
    addItem(player);
    player->setPos(79, 130);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    dog = new DogAgent();
    addItem(dog);
    dog->setPos(200, 400);

    // Obstáculos de fuego
    QList<QPointF> firePositions = {
        // QPointF(67, 431),
        QPointF(412, 43),
        QPointF(479, 130),
        QPointF(531, 196),
        QPointF(615, 412),
        QPointF(490, 554),
        QPointF(164, 761)};

    for (const QPointF &pos : firePositions)
    {
#ifdef _WIN32
        AnimatedSprite *fire = new AnimatedSprite(":/assets/sprites/Level_fire.png", 4, 4);
#elif defined(__linux__)
        AnimatedSprite *fire = new AnimatedSprite(":/assets/sprites/Level_fire.png", 4, 4);
#endif

        fire->setAnimationRow(0);
        fire->setScale(1.5);
        fire->start(270);
        fire->setPos(pos);

        addItem(fire);
        fires.append(fire);
    }

    // Refugio
    QList<QRectF> refugePositions = {
        QRectF(401, 14, 60, 49),
        QRectF(70, 435, 75, 27),
        QRectF(666, 783, 64, 56)};

    // Selecciona un refugio aleatorio
    int randomIndex = QRandomGenerator::global()->bounded(refugePositions.size());
    QRectF chosenArea = refugePositions[randomIndex];

    // Crea un rectángulo negro como refugio
    refuge = addRect(chosenArea, QPen(Qt::NoPen), QBrush(Qt::transparent));
    refuge->setZValue(5);


    // Humo oscilante
#ifdef _WIN32
    smoke = addPixmap(QPixmap(":/assets/sprites/Level1_fire.png").scaled(32, 32));
#elif defined(__linux__)
    smoke = addPixmap(QPixmap(":/assets/sprites/Level1_fire.png").scaled(32, 32));
#endif
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

    // Game loop
    connect(&gameLoop, &QTimer::timeout, this, &Level1Scene::updateScene);
    connect(&countdown, &QTimer::timeout, this, &Level1Scene::updateTimer);
    gameLoop.start(16);
    countdown.start(1000);


    //music
    if (!musicPlayer) {
        playlist = new QMediaPlaylist();

#ifdef _WIN32
        QUrl level1Url("qrc:/assets/sounds/level_1.wav");
#elif defined(__linux__)
        QUrl level1Url("qrc:/assets/sounds/level_1.wav");
#endif

        playlist->addMedia(level1Url);
        playlist->setPlaybackMode(QMediaPlaylist::Loop);

        musicPlayer = new QMediaPlayer();
        musicPlayer->setPlaylist(playlist);
        musicPlayer->setVolume(30);
        musicPlayer->play();
    }

}

void Level1Scene::updateScene()
{
    // Actualiza todos los items que tengan advance()
    advance();

    static float t = 0;
    t += 0.1f;

    // Física 1: movimiento oscilatorio del humo
    QPointF smokeOrigin(400, 150);
    QPointF newPos = Physics::oscillatory(t, 10.0f, 2.0f, smokeOrigin);
    smoke->setPos(newPos);

    // Física 2: vibración leve del fuego
    for (auto *fire : fires)
    {
        QPointF origin = fire->pos();
        QPointF drifted = Physics::randomDrift(t, 0.5f, origin);
        fire->setPos(drifted);
    }

    // Física 3: movimiento inercial del perro
    QPointF followTarget = player->pos() + QPointF(0, 90); // más abajito (aumenta el 40 si quieres más distancia)

    dog->perceive(fires, player->pos(), refuge);

    QPointF newDogPos = Physics::dampedFollow(
        dog->pos(),
        followTarget, 
        0.05f);

    dog->setPos(newDogPos);
    dog->update(0.016f);

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
        timerText->setPlainText("¡Tiempo agotado!");
        gameLoop.stop();
        countdown.stop();
    }
}

void Level1Scene::setView(QGraphicsView *view)
{
    view->setFocusPolicy(Qt::StrongFocus); // Permite que el view capture teclas
    view->setScene(this);
    player->setFocus(); // Da el foco al jugador dentro de la escena
}


void Level1Scene::stopMusic()
{
    if (musicPlayer) {
        musicPlayer->stop();
        delete musicPlayer;
        musicPlayer = nullptr;

        delete playlist;
        playlist = nullptr;
    }
}
