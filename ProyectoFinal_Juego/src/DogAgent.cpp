#include <DogAgent.hpp>

DogAgent::DogAgent()
    : AnimatedSprite("../assets/sprites/Level1_dog.png", 3, 4),
      dangerNearby(false)
{
    setAnimationRow(0); // primera fila del spritesheet
    scaleFactor = 1.0f;
    start(150); // animación cada 150 ms
    setZValue(10);
    setPos(150, 320);
}

// 1) Percepción: detecta fuego cerca y jugador
void DogAgent::perceive(const QList<QGraphicsPixmapItem *> &fires, const QPointF &playerPos)
{
    dangerNearby = false;

    for (auto *fire : fires)
    {
        if (QLineF(pos(), fire->pos()).length() < 120)
        {
            dangerNearby = true;
            learn(fire->pos());
        }
    }

    // Sigue al jugador si no hay fuego
    if (!dangerNearby)
    {
        target = playerPos;
    }
    else
    {
        // Si hay fuego cerca, se aleja un poco
        target = QPointF(pos().x() - 40, pos().y() - 40);
    }
}

// 2) Acción: movimiento suave hacia el objetivo
void DogAgent::act()
{
    QPointF dir = target - pos();
    qreal dist = qSqrt(dir.x()*dir.x() + dir.y()*dir.y());

    if (dist > 1.0) {
        dir /= dist;
        setPos(pos() + dir * 2.0);

        // Guarda dirección para mantener orientación estable
        lastDir = dir;

        // Basado en la dirección del jugador
        QPointF playerVel = target - lastTarget;
        lastTarget = target;

        int newRow = lastRow;

        // Si el jugador realmente se mueve, usa su dirección como referencia
        if (qAbs(playerVel.x()) > 1.0 || qAbs(playerVel.y()) > 1.0) {
            if (qAbs(playerVel.x()) > qAbs(playerVel.y())) {
                newRow = (playerVel.x() > 0) ? 2 : 1; // derecha / izquierda
            } else {
                newRow = (playerVel.y() > 0) ? 0 : 3; // abajo / arriba
            }
        }

        if (newRow != lastRow) {
            setAnimationRow(newRow);
            lastRow = newRow;
        }
    } else {
        setAnimationRow(lastRow); // idle en última dirección
    }

    // Efecto visual (alerta)
    setOpacity(dangerNearby ? 0.6 : 1.0);
}

// 3) Aprendizaje: memoriza posición peligrosa
void DogAgent::learn(const QPointF &dangerPos)
{
    if (!memory.contains(dangerPos))
        memory.append(dangerPos);
}

// 4) Lógica de actualización general
void DogAgent::update(float dt)
{
    Q_UNUSED(dt);
    act();
}
