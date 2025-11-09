#ifndef PLAYER_HPP

#define PLAYER_HPP
#include "GameObject.hpp"
#include <QKeyEvent>

class Player : public GameObject {
public:
    Player();
    void handleInput(QKeyEvent *event);
};

#endif