#ifndef LEVEL3SCENE_HPP
#define LEVEL3SCENE_HPP

#include <QCoreApplication>

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QList>

#include <QRandomGenerator>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>


#include "Plane.hpp"

class Level3Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Level3Scene(QObject *parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    static void stopMusic();

signals:
    void levelCompleted();
    void levelFailed(const QString &reason);

private slots:
    void updateScene();

private:
    void spawnPlanes();
    void predictConflicts(); // assistant: mark potential collisions
    Plane *planeAtPos(const QPointF &p);

    QList<Plane *> m_planes;
    Plane *m_selected;
    QGraphicsLineItem *m_dragLine;
    QTimer m_gameLoop;
    QGraphicsTextItem *m_hintText;

    // zonas de peligro y cronometro
    QList<QGraphicsEllipseItem *> m_dangerZones;
    QList<QGraphicsEllipseItem *> m_safeZones;
    QTimer m_dangerTimer;
    QTimer safeZoneTimer;


    void spawnDangerZones();
    void spawnSafeZones();

    void endLevel(const QString &reason, bool success);

    static QMediaPlayer *musicPlayer;
    static QMediaPlaylist * playlist;

    float m_time; // seconds
};

#endif