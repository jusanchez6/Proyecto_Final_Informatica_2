#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "GameObject.hpp"
#include <AnimatedSprite.hpp>
#include <QKeyEvent>
#include <QGraphicsScene>

class Player : public AnimatedSprite {
public:
    Player(int level);

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void advance(int phase) override;

    QPointF getVelocity() const { return velocity; }

private:
    QPointF velocity;
    bool moving;
};

#endif