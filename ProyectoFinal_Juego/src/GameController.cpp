#include <GameController.hpp>

GameController::GameController()
{
    m_view = new QGraphicsView();
    m_view->setFixedSize(736, 841);
    m_view->setWindowTitle("Juego Proyecto Final");
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->show();
}

void GameController::showMenu()
{

    auto *menu = new MenuScene([this]()
                               { this->showInstructions(1); });

    m_view->setScene(menu);
}

void GameController::showInstructions(int level)
{
    QString title, text;

    switch (level)
    {
    case 1:
        title = "Nivel 1";
        text = "LLega al refugio a tiempo!";
        break;

    case 2:
        title = "Nivel 2";
        text = "Dispara a los revoltosos y no te dejes alcanzar por las rocas.";
        break;

    case 3:
        title = "Nivel 3";
        text = "Trafico Aereo dificil, evita las zonas peligrosas y lleva los aviones a la zona segura";
        break;
    default:
        break;
    }

    auto *inst = new InstructionScene(title, text, [this, level]()
                                      { this->startLevel(level); });
    m_view->setScene(inst);
}

void GameController::startLevel(int level)
{
    if (level == 1) {
        auto *lvl = new Level1Scene();
        lvl->setView(m_view);
        m_view->setScene(lvl);

        QObject::connect(lvl, &Level1Scene::levelCompleted, [this, lvl]() {
            lvl->deleteLater();
            this->showInstructions(2);
        });
    }

    if (level == 2) {
        auto *lvl = new Level2Scene();
        lvl->setView(m_view);
        m_view->setScene(lvl);

        QObject::connect(lvl, &Level2Scene::levelCompleted, [this, lvl]() {
            lvl->deleteLater();
            this->showInstructions(3);
        });
    }

    if (level == 3) {
        auto *lvl = new Level3Scene();
        m_view->setScene(lvl);

        QObject::connect(lvl, &Level3Scene::levelCompleted, [this, lvl]() {
            lvl->deleteLater();
            this->showEnding();
        });
    }
}

void GameController::showEnding()
{
    auto *end = new InstructionScene(
        "¡Felicidades!",
        "Has completado todos los niveles.\nHaz clic para volver al menú.",
        [this]() {
            this->showMenu();
        });

    m_view->setScene(end);
}