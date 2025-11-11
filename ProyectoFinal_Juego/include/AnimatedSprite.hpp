#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>

class AnimatedSprite : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    AnimatedSprite(const QString &path, int columns = 3, int rows = 4, QObject *parent = nullptr);

    void setAnimationRow(int row);
    void start(int intervalMs = 100);
    void stop();

    void setCharacterIndex(int index);

    float scaleFactor;  // puedes cambiarlo desde Player (ej: 1.5 o 0.8)

protected slots:
    void updateFrame();

protected:
    QPixmap sheet;
    QPoint characterOffset;
    int cols, rows;
    int currentFrame;
    int currentRow;
    int frameWidth;
    int frameHeight;
    QTimer timer;
};

#endif
