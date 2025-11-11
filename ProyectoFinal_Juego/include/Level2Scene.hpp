#pragma once
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QList>
#include <QKeyEvent>
#include "Player.hpp"
#include "Physics.hpp"

class Level2Scene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit Level2Scene(QObject *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void levelCompleted();

private slots:
    void updateScene();
    void spawnRock();
    void updateTimer();

private:
    Player *player;
    QList<QGraphicsPixmapItem*> rocks;
    QGraphicsTextItem *timerText;
    QTimer gameLoop;
    QTimer spawnTimer;
    QTimer countdown;
    int timeLeft;
    float t; // tiempo acumulado para la física parabólica
};
