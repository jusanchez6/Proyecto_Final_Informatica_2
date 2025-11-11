#include "AnimatedSprite.hpp"
#include <QDebug>

AnimatedSprite::AnimatedSprite(const QString &path, int columns, int rows, QObject *parent)
    : QObject(parent),
      QGraphicsPixmapItem(),
      sheet(QPixmap(path)),
      cols(columns),
      rows(rows),
      currentFrame(0),
      currentRow(0),
      scaleFactor(1.0) // Ajusta según necesites (2x tamaño original)

{
    if (sheet.isNull())
    {
        qWarning() << "No se pudo cargar el spritesheet:" << path;
        return;
    }

    frameWidth = sheet.width() / cols;
    frameHeight = sheet.height() / rows;

    characterOffset = QPoint(0, 0);

    // Establece el primer frame
    setPixmap(sheet.copy(0, 0, frameWidth, frameHeight));
    setTransformOriginPoint(frameWidth / 2, frameHeight / 2);

    connect(&timer, &QTimer::timeout, this, &AnimatedSprite::updateFrame);
}

void AnimatedSprite::setAnimationRow(int row)
{
    if (row >= 0 && row < rows)
    {
        currentRow = row;
    }
}

void AnimatedSprite::start(int intervalMs)
{
    timer.start(intervalMs);
}

void AnimatedSprite::stop()
{
    timer.stop();
}

void AnimatedSprite::setCharacterIndex(int index)
{
    // Cada personaje ocupa un bloque de 3x4 frames
    int charsPerRow = sheet.width() / (frameWidth * cols); // 2 personajes por fila
    int charX = (index % charsPerRow) * cols * frameWidth;
    int charY = (index / charsPerRow) * rows * frameHeight;

    characterOffset = QPoint(charX, charY);
}

void AnimatedSprite::updateFrame()
{
    if (sheet.isNull())
        return;

    int x = characterOffset.x() + (currentFrame % cols) * frameWidth;
    int y = characterOffset.y() + currentRow * frameHeight;

    QPixmap frame = sheet.copy(x, y, frameWidth, frameHeight);
    frame = frame.scaled(frameWidth * scaleFactor,
                         frameHeight * scaleFactor,
                         Qt::KeepAspectRatio,
                         Qt::SmoothTransformation);

    setPixmap(frame);
    setTransformOriginPoint(boundingRect().width() / 2, boundingRect().height() / 2);

    currentFrame = (currentFrame + 1) % cols;
}
