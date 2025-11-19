#include <MenuScene.hpp>

QMediaPlayer *MenuScene::musicPlayer = nullptr;
QMediaPlaylist *MenuScene::playlist = nullptr;


MenuScene::MenuScene(std::function<void()> startCallback, QObject *parent)
    : QGraphicsScene(parent), m_startCallback(startCallback)
{
    setSceneRect(0, 0, 736, 841);

    QPixmap bg("../assets/backgrounds/menu_bg.png");
    if (!bg.isNull())
    {
        QGraphicsPixmapItem *bgItem = addPixmap(bg.scaled(736, 841));
        bgItem->setZValue(-100);
    }
    else
    {
        setBackgroundBrush(Qt::darkBlue);
    }

    // boton
    QGraphicsRectItem *button = addRect(0, 0, 260, 70, QPen(Qt::white), QBrush(Qt::black));
    button->setPos(240, 550);
    button->setOpacity(0.7);
    button->setData(0, "start");

    QGraphicsTextItem *btnText = addText("Iniciar Juego", QFont("Arial", 18));
    btnText->setDefaultTextColor(Qt::white);
    btnText->setPos(300, 565);

    if (!musicPlayer) {
        playlist = new QMediaPlaylist();
        playlist->addMedia(QUrl::fromLocalFile("/home/julian-sanchez/Univerisdad/Informatica 2/Proyecto_Final_Informatica_2/ProyectoFinal_Juego/assets/sounds/Menu.wav"));
        playlist->setPlaybackMode(QMediaPlaylist::Loop);

        musicPlayer = new QMediaPlayer();
        musicPlayer->setPlaylist(playlist);
        musicPlayer->setVolume(40);
        musicPlayer->play();
    }
}

void MenuScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    auto itemsClicked = items(event->scenePos());

    for (auto *item : itemsClicked)
    {
        if (item->data(0).toString() == "start")
        {
            if (m_startCallback)
            {
                m_startCallback();
            }
            return;
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

void MenuScene::stopMusic()
{
    if (musicPlayer) {
        musicPlayer->stop();
        delete musicPlayer;
        musicPlayer = nullptr;

        delete playlist;
        playlist = nullptr;
    }
}
