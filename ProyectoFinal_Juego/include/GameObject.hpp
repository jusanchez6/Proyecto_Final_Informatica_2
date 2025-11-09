#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include <QGraphicsPixmapItem>

class GameObject : public QGraphicsPixmapItem {
public:
    GameObject(const QPixmap &pixmap);
    virtual void update(float dt) {}
    virtual ~GameObject() = default;
};

#endif