#include <GameObject.hpp>

GameObject::GameObject(const QPixmap &pixmap, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(pixmap) {}
