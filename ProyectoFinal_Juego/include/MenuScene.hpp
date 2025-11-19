#ifndef MENUSCENE_HPP
#define MENUSCENE_HPP

#include <QCoreApplication>

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsPathItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QFont>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <functional>

class MenuScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MenuScene(std::function<void()> startCallback, QObject *parent = nullptr);
    static void stopMusic();

private:
    std::function<void()> m_startCallback;
    static QMediaPlayer *musicPlayer;
    static QMediaPlaylist * playlist;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif