#include <Player.hpp>

Player::Player()
    : GameObject(QPixmap("../assets/sprites/Level1_player.png").scaled(48, 48)) {}

void Player::handleInput(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_W: case Qt::Key_Up:    setY(y() - 10); break;
    case Qt::Key_S: case Qt::Key_Down:  setY(y() + 10); break;
    case Qt::Key_A: case Qt::Key_Left:  setX(x() - 10); break;
    case Qt::Key_D: case Qt::Key_Right: setX(x() + 10); break;
    }
}
