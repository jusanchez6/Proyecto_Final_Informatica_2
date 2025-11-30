/**
 * @file AnimatedSprite.hpp
 * @brief Clase para manejar sprites animados a partir de spritesheets
 * @authors John Tristancho
 *          Julian Sanchez
 *
 * @date 29/11/2025
 * @version 1.0
 */

#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>

/**
 * @brief Clase para manejar sprites animados a partir de spritesheets
 *
 * AnimatedSprite permite cargar una imagen que contiene múltiples frames
 * de animación organizados en una cuadrícula y reproducirlos en secuencia.
 * Es útil para animaciones de personajes, efectos visuales, etc.
 *
 * @inherits QObject, QGraphicsPixmapItem
 */
class AnimatedSprite : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
     * @brief Constructor de AnimatedSprite
     *
     * Carga un spritesheet y lo divide en frames según la cuadrícula especificada.
     *
     * @param path Ruta al archivo de imagen del spritesheet
     * @param columns Número de columnas en el spritesheet
     * @param rows Número de filas en el spritesheet
     * @param parent Puntero al objeto padre
     */
    AnimatedSprite(const QString &path, int columns = 3, int rows = 4, QObject *parent = nullptr);

    /**
     * @brief Establece la fila de animación a reproducir
     *
     * Cada fila del spritesheet típicamente representa una dirección
     * o acción diferente.
     *
     * @param row Índice de la fila a mostrar
     */
    void setAnimationRow(int row);

    /**
     * @brief Inicia la animación
     *
     * Comienza a reproducir los frames de la animación actual en un bucle.
     *
     * @param intervalMs Intervalo entre frames en milisegundos
     */
    void start(int intervalMs = 100);

    /**
     * @brief Detiene la animación
     *
     * Para la reproducción de frames pero mantiene el frame actual visible.
     */
    void stop();

    /**
     * @brief Establece el índice del personaje en spritesheets múltiples
     *
     * Útil cuando el spritesheet contiene múltiples personajes o variantes.
     *
     * @param index Índice del personaje
     */
    void setCharacterIndex(int index);

    /**
     * @brief Factor de escala para el sprite
     *
     * Permite escalar visualmente el sprite. Valores mayores que 1.0 agrandan,
     * valores menores que 1.0 reducen el tamaño.
     */
    float scaleFactor;

protected slots:
    /**
     * @brief Actualiza el frame de animación actual
     *
     * Slot llamado por el timer para avanzar al siguiente frame
     * en la animación actual.
     */
    void updateFrame();

protected:
    QPixmap sheet;              ///< Imagen completa del spritesheet
    QPoint characterOffset;     ///< Desplazamiento para múltiples personajes
    int cols;                   ///< Número de columnas en el spritesheet
    int rows;                   ///< Número de filas en el spritesheet
    int currentFrame;           ///< Frame actual siendo mostrado
    int currentRow;             ///< Fila actual de animación
    int frameWidth;             ///< Ancho de cada frame en píxeles
    int frameHeight;            ///< Alto de cada frame en píxeles
    QTimer timer;               ///< Timer para controlar la animación
};

#endif
