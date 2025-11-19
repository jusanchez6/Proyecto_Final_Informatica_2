#ifndef LEVEL1SCENE_HPP
#define LEVEL1SCENE_HPP

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QKeyEvent>
#include <QElapsedTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "Player.hpp"
#include "DogAgent.hpp"
#include "Physics.hpp"

#define LEVEL_ID 1

class Level1Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Level1Scene(QObject *parent = nullptr);
    void setView(QGraphicsView *view); // nuevo método
    static void stopMusic();
signals:
    void levelCompleted();

private slots:
    void updateScene();
    void updateTimer();

private:
    Player *player;
    DogAgent *dog;
    QList<QGraphicsPixmapItem *> fires;
    QGraphicsPixmapItem *smoke;
    QGraphicsItem *refuge;

    QTimer gameLoop;
    QTimer countdown;

    int timeLeft;
    int playerLives;

    bool invulnerable;
    QElapsedTimer damageTimer;

    QGraphicsTextItem *timerText;
    QGraphicsTextItem *livesText;
    QGraphicsRectItem *damageFlash;

    QList<QGraphicsItem *> colliders;

    static QMediaPlayer *musicPlayer;
    static QMediaPlaylist * playlist;
};

#endif
