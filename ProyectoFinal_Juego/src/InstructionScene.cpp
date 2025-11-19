#include <InstructionScene.hpp>
#include <QGraphicsProxyWidget>
#include <QFont>

InstructionScene::InstructionScene(const QString &title,
                                   const QString &instructions,
                                   std::function<void()> onStart,
                                   QObject *parent)
    : QGraphicsScene(parent)
{
    // Tamaño de la escena
    setSceneRect(0, 0, 736, 841);

    // Fondo negro
    setBackgroundBrush(Qt::black);

    // Título grande
    titleText = addText(title, QFont("Arial", 28, QFont::Bold));
    titleText->setDefaultTextColor(Qt::white);
    titleText->setPos(80, 50);

    // Texto de instrucciones
    instructionText = addText(instructions, QFont("Arial", 16));
    instructionText->setDefaultTextColor(Qt::white);
    instructionText->setTextWidth(600);
    instructionText->setPos(60, 150);

    // Botón
    QPushButton *btn = new QPushButton("Comenzar");
    btn->setFixedSize(200, 50);

    QGraphicsProxyWidget *proxy = addWidget(btn);
    proxy->setPos(width() / 2 - 100, height() - 150);

    QObject::connect(btn, &QPushButton::clicked, [onStart]()
                     {
        if (onStart) onStart(); });
}
