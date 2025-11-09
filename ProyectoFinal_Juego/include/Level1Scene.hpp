#ifndef LEVEL1SCENE_HPP
#define LEVEL1SCENE_HPP

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QKeyEvent>
#include <QList>
#include <QRandomGenerator>
#include <QDebug>
#include <cmath>


#include <Player.hpp>
#include <DogAgent.hpp>

class Level1Scene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit Level1Scene(QObject *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateScene();
    void updateTimer();

private:
    Player *player;
    DogAgent *dog;
    QGraphicsPixmapItem *refuge;
    QList<QGraphicsPixmapItem*> fires;
    QGraphicsPixmapItem *smoke;
    QGraphicsTextItem *timerText;
    QTimer gameLoop;
    QTimer countdown;
    int timeLeft;
};


#endif