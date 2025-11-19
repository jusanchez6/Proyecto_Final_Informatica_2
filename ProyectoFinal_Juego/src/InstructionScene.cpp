#include <InstructionScene.hpp>

InstructionScene::InstructionScene(const QString &title, const QString &instructions, std::function<void()> onStart, QObject *parent)
    : QGraphicsScene(parent), startCallback(onStart)
{
    setSceneRect(0, 0, 736, 841);


    QGraphicsTextItem * titleItem = addText(title, QFont("Arial", 32, QFont::Bold));
    titleItem->setDefaultTextColor(Qt::white);
    titleItem->setPos(100, 40);


    // texto de instrucciones
    QGraphicsTextItem *instructionsItem = addText(instructions, QFont("Arial", 32));
    instructionsItem->setDefaultTextColor(Qt::white);
    instructionsItem->setTextWidth(600);
    instructionsItem->setPos(60, 150);

    QGraphicsTextItem * clickText = addText("Haz click para comenzar", QFont("Arial", 18, QFont::Bold));
    clickText->setDefaultTextColor(Qt::yellow);
    clickText->setPos(200, 750);


    addRect(sceneRect(), Qt::NoPen, QBrush(Qt::black));
}

void InstructionScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if (startCallback)
        startCallback();
}