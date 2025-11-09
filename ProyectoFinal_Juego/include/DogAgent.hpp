#pragma once
#include "GameObject.hpp"
#include <QList>
#include <QPointF>

class DogAgent : public GameObject {
public:
    DogAgent();
    void update(float dt) override;

    void perceive(const QList<QGraphicsPixmapItem*>& fires, const QPointF& playerPos);
    void act();
    void learn(const QPointF& dangerPos);

private:
    QPointF target;
    QList<QPointF> memory;   // Zonas de fuego recordadas
    bool dangerNearby;
};
