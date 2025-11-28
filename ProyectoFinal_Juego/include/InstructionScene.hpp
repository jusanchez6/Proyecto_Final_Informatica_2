#ifndef INSTRUCTIONSCENE_HPP
#define INSTRUCTIONSCENE_HPP

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <functional>
class InstructionScene : public QGraphicsScene
{
    Q_OBJECT
public:
    InstructionScene(const QString &title,
                     const QString &instructions,
                     std::function<void()> onStart,
                     QObject *parent = nullptr);

private:
    QGraphicsTextItem *titleText;
    QGraphicsTextItem *instructionText;
};

#endif
