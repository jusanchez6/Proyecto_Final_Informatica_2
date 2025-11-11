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
    QList<QPointF> memory; // Zonas de fuego recordadas
    bool dangerNearby;

    QPointF lastDir;
    int lastRow = 0;

    QPointF lastTarget;

    QSoundEffect barkSound;
};
