#include <DogAgent.hpp>
#include <QtMath>
#include <QDebug>

DogAgent::DogAgent()
    : GameObject(QPixmap("../assets/sprites/Level1_dog.png").scaled(32, 32)),
      dangerNearby(false)
{
    setPos(100, 320);
}

// 1) Percepción: detecta fuego cerca y jugador
void DogAgent::perceive(const QList<QGraphicsPixmapItem*>& fires, const QPointF& playerPos) {
    dangerNearby = false;

    for (auto *fire : fires) {
        if (QLineF(pos(), fire->pos()).length() < 120) {
            dangerNearby = true;
            learn(fire->pos());
        }
    }

    // Sigue al jugador si no hay fuego
    if (!dangerNearby) {
        target = playerPos;
    } else {
        // Si hay fuego cerca, se aleja un poco
        target = QPointF(pos().x() - 40, pos().y() - 40);
    }
}

// 2) Acción: movimiento suave hacia el objetivo
void DogAgent::act() {
    QPointF dir = target - pos();
    qreal dist = qSqrt(dir.x()*dir.x() + dir.y()*dir.y());
    if (dist > 2.0) {
        dir /= dist;
        setPos(pos() + dir * 2.0);
    }

    if (dangerNearby){
        qDebug() << "🐕 Ladrando: ¡Fuego detectado!";
        setOpacity(0.6);
    } else {
        setOpacity(1.0);
    }
}

// 3) Aprendizaje: memoriza posición peligrosa
void DogAgent::learn(const QPointF& dangerPos) {
    if (!memory.contains(dangerPos))
        memory.append(dangerPos);
}

// 4) Lógica de actualización general
void DogAgent::update(float dt) {
    Q_UNUSED(dt);
    act();
}
