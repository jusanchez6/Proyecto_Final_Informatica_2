#include <Level1Scene.hpp>


Level1Scene::Level1Scene(QObject *parent)
    : QGraphicsScene(parent), timeLeft(30)
{
    setSceneRect(0, 0, 800, 600);

    // Jugador
    player = new Player();
    addItem(player);
    player->setPos(50, 300);


    dog = new DogAgent();
    addItem(dog);

    // Refugio
    refuge = addPixmap(QPixmap("../assets/sprites/Level1_debris.png").scaled(48, 48));
    refuge->setPos(700, 280);

    // Obstáculos de fuego
    for (int i = 0; i < 5; ++i) {
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

    // Timers
    connect(&gameLoop, &QTimer::timeout, this, &Level1Scene::updateScene);
    connect(&countdown, &QTimer::timeout, this, &Level1Scene::updateTimer);
    gameLoop.start(16);
    countdown.start(1000);
}

void Level1Scene::keyPressEvent(QKeyEvent *event) {
    player->handleInput(event);
}

void Level1Scene::updateScene() {
    static float t = 0;
    t += 0.1f;

    // 🌫️ Física 1: movimiento oscilatorio del humo
    QPointF smokeOrigin(400, 150);
    QPointF newPos = Physics::oscillatory(t, 10.0f, 2.0f, smokeOrigin);
    smoke->setPos(newPos);

    // 🔥 Física 2: vibración leve del fuego
    for (auto *fire : fires) {
        QPointF origin = fire->pos();
        QPointF drifted = Physics::randomDrift(t, 0.5f, origin);
        fire->setPos(drifted);
    }

    // 🐕 Física 3: movimiento inercial del perro (con su IA)
    dog->perceive(fires, player->pos());
    QPointF newDogPos = Physics::dampedFollow(dog->pos(), dog->pos() + (dog->pos() - player->pos()) * -1, 0.05f);
    dog->setPos(newDogPos);
    dog->update(0.016f);

    // 🔍 Colisiones
    for (auto *fire : fires) {
        if (player->collidesWithItem(fire)) {
            qDebug() << "🔥 Tocado por el fuego, pierdes 1 segundo.";
            timeLeft = std::max(0, timeLeft - 1);
        }
    }

    if (player->collidesWithItem(refuge)) {
        qDebug() << "✅ Has llegado al refugio.";
        timerText->setPlainText("¡Has llegado al refugio!");
        emit levelCompleted();
        gameLoop.stop();
        countdown.stop();
    }
}

void Level1Scene::updateTimer() {
    timeLeft--;
    timerText->setPlainText(QString("Tiempo: %1").arg(timeLeft));

    if (timeLeft <= 0) {
        timerText->setDefaultTextColor(Qt::red);
        timerText->setPlainText("⏰ ¡Tiempo agotado!");
        gameLoop.stop();
        countdown.stop();
    }
}
