#include "Player.hpp"

Player::Player()
    : AnimatedSprite("../assets/sprites/personaje_1.png", 3, 4),
      velocity(0, 0), moving(false)
{
    setCharacterIndex(0);
    setAnimationRow(0); // mira hacia abajo por defecto
    scaleFactor = 1.0f; // ajusta el tamaño general
    start(120);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Player::keyPressEvent(QKeyEvent *event)
{
    moving = true;

    switch (event->key())
    {
    case Qt::Key_W:
        velocity.setY(-3);
        setAnimationRow(3); // fila 3 = arriba
        break;
    case Qt::Key_S:
        velocity.setY(3);
        setAnimationRow(0); // fila 0 = abajo
        break;
    case Qt::Key_A:
        velocity.setX(-3);
        setAnimationRow(1); // fila 1 = izquierda
        break;
    case Qt::Key_D:
        velocity.setX(3);
        setAnimationRow(2); // fila 2 = derecha
        break;
    default:
        break;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
    moving = false;
    velocity = QPointF(0, 0);
}

void Player::advance(int phase)
{
    if (!phase)
        return;
    if (moving)
        moveBy(velocity.x(), velocity.y());

    if (scene())
    {
        QRectF bounds = scene()->sceneRect();
        QRectF spriteRect = boundingRect().translated(pos());

        // Ajustar posición si se sale
        QPointF p = pos();
        if (spriteRect.left() < bounds.left())
            p.setX(bounds.left());
        if (spriteRect.right() > bounds.right())
            p.setX(bounds.right() - boundingRect().width());
        if (spriteRect.top() < bounds.top())
            p.setY(bounds.top());
        if (spriteRect.bottom() > bounds.bottom())
            p.setY(bounds.bottom() - boundingRect().height());

        setPos(p);
    }
}
