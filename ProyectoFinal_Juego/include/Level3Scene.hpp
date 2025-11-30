/**
 * @file Level3Scene.hpp
 * @brief Escena del tercer nivel del juego
 * @authors John Tristancho
 *          Julian Sanchez
 * 
 * @date 29/11/2025
 * @version 1.0
 */

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

/**
 * @brief Escena del tercer nivel del juego
 */
class Level3Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @brief Constructor de la escena del nivel 3
     * @param parent Objeto padre
     */
    explicit Level3Scene(QObject *parent = nullptr);

    /**
     * @brief Maneja eventos de clic del mouse
     * @param event Evento del mouse
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief Maneja eventos de movimiento del mouse
     * @param event Evento del mouse
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief Maneja eventos de liberación del mouse
     * @param event Evento del mouse
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief Maneja eventos de teclas presionadas
     * @param event Evento de tecla
     */
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief Detiene la música del nivel
     */
    static void stopMusic();

signals:
    /**
     * @brief Señal emitida cuando se completa el nivel
     */
    void levelCompleted();

    /**
     * @brief Señal emitida cuando falla el nivel
     * @param reason Razón del fallo
     */
    void levelFailed(const QString &reason);

private slots:
    /**
     * @brief Actualiza el estado de la escena
     */
    void updateScene();

private:
    /**
     * @brief Genera aviones en la escena
     */
    void spawnPlanes();

    /**
     * @brief Predice conflictos entre aviones
     */
    void predictConflicts();

    /**
     * @brief Obtiene el avión en una posición dada
     * @param p Posición a verificar
     * @return Avión en la posición o nullptr
     */
    Plane *planeAtPos(const QPointF &p);

    QList<Plane *> m_planes;                    ///< Lista de aviones
    Plane *m_selected;                          ///< Avión seleccionado
    QGraphicsLineItem *m_dragLine;              ///< Línea de arrastre
    QTimer m_gameLoop;                          ///< Timer del bucle principal
    QGraphicsTextItem *m_hintText;              ///< Texto de ayuda

    QList<QGraphicsEllipseItem *> m_dangerZones;    ///< Zonas de peligro
    QList<QGraphicsEllipseItem *> m_safeZones;      ///< Zonas seguras
    QTimer m_dangerTimer;                       ///< Timer de zonas de peligro
    QTimer safeZoneTimer;                       ///< Timer de zonas seguras

    /**
     * @brief Genera zonas de peligro
     */
    void spawnDangerZones();

    /**
     * @brief Genera zonas seguras
     */
    void spawnSafeZones();

    /**
     * @brief Finaliza el nivel
     * @param reason Razón del fin
     * @param success Si fue exitoso
     */
    void endLevel(const QString &reason, bool success);

    static QMediaPlayer *musicPlayer;           ///< Reproductor de música
    static QMediaPlaylist * playlist;           ///< Lista de reproducción

    float m_time;                               ///< Tiempo transcurrido
};

#endif