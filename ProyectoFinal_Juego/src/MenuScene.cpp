#include <MenuScene.hpp>

MenuScene::MenuScene(std::function<void()> startCallback, QObject *parent)
    : QGraphicsScene(parent), m_startCallback(startCallback)
{
    setSceneRect(0, 0, 736, 841);

    QPixmap bg("../assets/backgrounds/menu_bg.png");
    if (!bg.isNull()) {
        QGraphicsPixmapItem *bgItem = addPixmap(bg.scaled(736, 841));
        bgItem->setZValue(-100);
    } else {
        setBackgroundBrush(Qt::darkBlue);
    }

    // titulo
    QGraphicsTextItem *title = addText("Proyecto Final", QFont("Arial", 32, QFont::Bold));
    title->setDefaultTextColor(Qt::white);
    title->setPos(200, 150);

    // boton
    QGraphicsRectItem *button = addRect(0, 0, 260, 70, QPen(Qt::white), QBrush(Qt::black));
    button->setPos(240, 350);
    button->setOpacity(0.7);
    button->setData(0, "start");

    QGraphicsTextItem *btnText = addText("Iniciar Juego", QFont("Arial", 18));
    btnText->setDefaultTextColor(Qt::white);
    btnText->setPos(280, 365);
}

void MenuScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    auto itemsClicked = items(event->scenePos());

    for (auto *item : itemsClicked) {
        if (item->data(0).toString() == "start") {
            if (m_startCallback) {
                m_startCallback();
            }
            return;
        }
    }

    QGraphicsScene::mousePressEvent(event);
}