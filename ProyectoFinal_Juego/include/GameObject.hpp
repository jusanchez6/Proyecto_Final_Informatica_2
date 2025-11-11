#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <QObject>
#include <QGraphicsPixmapItem>

class GameObject : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT  
public:
    explicit GameObject(const QPixmap &pixmap, QObject *parent = nullptr);
    virtual void update(float dt) {}
};

#endif