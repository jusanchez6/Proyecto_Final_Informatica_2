#pragma once
#include <AnimatedSprite.hpp>

#include <QtMath>
#include <QDebug>
#include <QList>
#include <QPointF>
#include <QSoundEffect>

class DogAgent : public AnimatedSprite
{
public:
    DogAgent();
    void update(float dt);

    void perceive(const QList<QGraphicsPixmapItem*> &fires, const QPointF &playerPos, const QGraphicsItem *refuge);
    void act();
    void learn(const QPointF &dangerPos);

private:
    QPointF target;
    QPointF velocity;
    QList<QPointF> memory;//la parte donde sale el fuego en el nivel 1
    bool dangerNearby;

    QPointF lastDir;
    int lastRow = 0;

    QPointF lastTarget;

    QSoundEffect barkSound;
};
