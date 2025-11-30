/**
 * @file GameController.cpp
 * @brief Implementación controlador principal del juego
 * @authors John Tristancho
 *          Julian Sanchez
 * 
 * @date 29/11/2025
 * @version 1.0
 */

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

    MenuScene::stopMusic();    
    QString title, text;

    if (level == 1) {
        title = "Nivel 1 - Bomba de Nagasaki.";
        text = "El 9 de agosto de 1945, la ciudad de Nagasaki fue sacudida por la explosión de una bomba atómica que transformó el mundo para siempre. La devastación fue inmediata: edificios reducidos a ruinas, un cielo cubierto de ceniza y un silencio roto solo por el eco de la destrucción. Miles de vidas cambiaron en un instante y muchas familias quedaron separadas en medio del caos.\n\n"
       "En esta historia tú eres un niño que logró sobrevivir al impacto inicial. Confundido, asustado y rodeado por un bosque en las afueras de la ciudad, sabes que tus padres te están esperando en un refugio improvisado, construido para resistir lo peor. Aunque el aire es pesado y la tierra aún tiembla, tu única misión es encontrarlos para esto cuentas con tu fiel amigo perruno, que con su olfato refinado te indicara si estas o no cerca del refugio.\n\n"
       "Tu objetivo: Avanza a través del bosque y llega al refugio lo más pronto posible. Evita los peligros y sigue tu instinto — tu familia te está esperando.";

    }
    else if (level == 2) {
        Level1Scene::stopMusic();
        title = "Nivel 2- Asesinato de Gaitan";
        text = "El 9 de abril de 1948, Colombia quedó marcada para siempre. Ese día, en pleno centro de Bogotá, fue asesinado Jorge Eliécer Gaitán, una de las figuras políticas más queridas y esperanzadoras del país. La noticia corrió como fuego por las calles y, en cuestión de minutos, la ciudad estalló en caos. Edificios incendiados, comercios saqueados y multitudes fuera de control transformaron la capital en un escenario de confusión y violencia.\n\n"
       "En esta historia tú eres un joven atrapado en medio de los disturbios. No tienes armas, pero cuentas con un símbolo poderoso: el símbolo de la paz. Con él podrás repeler a los revoltosos y abrirte paso entre la multitud. Tu misión no es combatir, sino sobrevivir sin contribuir a la destrucción que consume la ciudad.\n\n"
       "Tu objetivo: Usa el símbolo de la paz para dispersar a los alborotadores esquivando las rocas que caen. Evita que te rodeen o que la violencia te alcance. Mantén la calma, evita las rocas y sobrevive el mayor tiempo posible.";

    }
    else if (level == 3) {
        Level2Scene::stopMusic();
        title = "Nivel 3";
        text = "El 11 de septiembre de 2001, el mundo presenció uno de los eventos más impactantes de la historia moderna. Aviones comerciales desviados de sus rutas fueron utilizados como armas, y el cielo, que solía ser símbolo de seguridad y libertad, se convirtió en un espacio de incertidumbre y peligro. En cuestión de horas, millones de vidas fueron alteradas para siempre.\n\n"
       "En esta historia tú eres un controlador aéreo que, en medio del caos, debe desviar aeronaves potencialmente comprometidas lejos de zonas de riesgo. Tus decisiones son inmediatas, tensas y cruciales. Un error puede tener consecuencias inimaginables.\n\n"
       "Tu objetivo: No permitas que ningún avión entre en áreas de peligro. Guía cada aeronave hacia zonas seguras y mantén el control del espacio aéreo. Pierdes si fallas en redirigir un avión o si alguno escapa fuera de la pantalla. Mantén la concentración — muchas vidas dependen de ti.";

    }

    auto *inst = new InstructionScene(title, text, [this, level]() {
        this->startLevel(level);
    });

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

        QObject::connect(lvl, &Level1Scene::levelFailed,
                         [this, lvl](const QString &reason) {
                             lvl->deleteLater();
                             this->showGameOver(reason);
                         });
    }
    else if (level == 2) {
        auto *lvl = new Level2Scene();
        lvl->setView(m_view);
        m_view->setScene(lvl);

        QObject::connect(lvl, &Level2Scene::levelCompleted, [this, lvl]() {
            lvl->deleteLater();
            this->showInstructions(3);
        });

        QObject::connect(lvl, &Level2Scene::levelFailed,
                         [this, lvl](const QString &reason) {
                             lvl->deleteLater();
                             this->showGameOver(reason);
                         });
    }
    else if (level == 3) {
        auto *lvl = new Level3Scene();
        m_view->setScene(lvl);

        QObject::connect(lvl, &Level3Scene::levelCompleted, [this, lvl]() {
            lvl->deleteLater();
            this->showEnding();
        });

        QObject::connect(lvl, &Level3Scene::levelFailed,
                         [this, lvl](const QString &reason) {
                             lvl->deleteLater();
                             this->showGameOver(reason);
                         });
    }
}

void GameController::showEnding()
{
    Level3Scene::stopMusic();
    auto *end = new InstructionScene(
        "¡Felicidades!",
        "Has completado todos los niveles.\nHaz clic para volver al menú.",
        [this]() {
            this->showMenu();
        });

    m_view->setScene(end);
}

void GameController::showGameOver(const QString &reason)
{
    auto *inst = new InstructionScene(
        "Has perdido",
        reason + "\n\nHaz clic para volver al menú.",
        [this]() {
            this->showMenu();
        });

    m_view->setScene(inst);
}
