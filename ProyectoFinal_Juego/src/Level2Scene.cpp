#include "Level2Scene.hpp"
#include <QRandomGenerator>
#include <QDebug>
#include <QtMath>

Level2Scene::Level2Scene(QObject *parent)
    : QGraphicsScene(parent),
      timeLeft(25),
      t(0.0f)
{
    setSceneRect(0, 0, 800, 600);
    setBackgroundBrush(Qt::darkBlue);

    // Jugador
    player = new Player(LEVEL_ID);
    addItem(player);
    player->setPos(100, 500);

    // Texto del tiempo
    timerText = addText("Tiempo: 25", QFont("Arial", 16));
    timerText->setDefaultTextColor(Qt::white);
    timerText->setPos(10, 10);

    // Timers
    connect(&gameLoop, &QTimer::timeout, this, &Level2Scene::updateScene);
    connect(&spawnTimer, &QTimer::timeout, this, &Level2Scene::spawnRock);
    connect(&countdown, &QTimer::timeout, this, &Level2Scene::updateTimer);

    gameLoop.start(16);
    spawnTimer.start(1500);
    countdown.start(1000);
}

void Level2Scene::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_W:
    case Qt::Key_Up:    player->setY(player->y() - 10); break;
    case Qt::Key_S:
    case Qt::Key_Down:  player->setY(player->y() + 10); break;
    case Qt::Key_A:
    case Qt::Key_Left:  player->setX(player->x() - 10); break;
    case Qt::Key_D:
    case Qt::Key_Right: player->setX(player->x() + 10); break;
    default: break;
    }
}

// 🪨 Crea nuevas rocas cayendo (física parabólica)
void Level2Scene::spawnRock() {
    auto *rock = addPixmap(QPixmap("../assets/sprites/Level1_debris.png").scaled(32, 32));
    float x = QRandomGenerator::global()->bounded(200, 780);
    rock->setPos(x, 0);
    rocks.append(rock);
}

// ⚙️ Actualiza físicas y colisiones
void Level2Scene::updateScene() {
    QList<QGraphicsPixmapItem*> toRemove;

    for (auto *rock : rocks) {
        // Recuperar o inicializar el tiempo local
        float localTime = rock->data(1).toFloat();
        localTime += 0.1f; // incrementa el tiempo propio de esta roca
        rock->setData(1, localTime);

        // Recuperar o guardar su posición inicial
        QPointF origin = rock->data(0).toPointF();
        if (origin.isNull()) {
            origin = rock->pos();
            rock->setData(0, origin);
        }

        // Calcular nueva posición con física parabólica
        QPointF newPos = Physics::projectile(localTime, origin, 5.0f, 9.8f);
        rock->setPos(newPos);

        // Eliminar si sale de la escena
        if (rock->y() > 600) {
            toRemove.append(rock);
            continue;
        }

        // Colisión con el jugador
        if (player->collidesWithItem(rock)) {
            timerText->setPlainText("💥 ¡Golpeado!");
            timerText->setDefaultTextColor(Qt::red);
            gameLoop.stop();
            spawnTimer.stop();
            countdown.stop();
            return;
        }
    }

    // Eliminar rocas fuera de pantalla
    for (auto *r : toRemove) {
        removeItem(r);
        rocks.removeOne(r);
        delete r;
    }
}



// ⏰ Temporizador de nivel
void Level2Scene::updateTimer() {
    timeLeft--;
    timerText->setPlainText(QString("Tiempo: %1").arg(timeLeft));

    if (timeLeft <= 0) {
        timerText->setDefaultTextColor(Qt::green);
        timerText->setPlainText("✅ ¡Nivel superado!");
        gameLoop.stop();
        spawnTimer.stop();
        countdown.stop();
        emit levelCompleted();
    }
}
