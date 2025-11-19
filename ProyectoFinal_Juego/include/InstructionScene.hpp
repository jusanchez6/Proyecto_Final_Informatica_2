#ifndef INSTRUCTIONSCENE_HPP
#define INSTRUCTIONSCENE_HPP

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QFont>
#include <functional>

class InstructionScene : public QGraphicsScene
{
    Q_OBJECT

public:
    InstructionScene(const QString &title, const QString &instructions, std::function<void()> onStart, QObject *parent = nullptr);

protected: 
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    std::function<void ()> startCallback;

};

#endif