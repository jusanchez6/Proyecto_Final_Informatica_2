#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <QObject>
#include <QGraphicsView>

#include <Level1Scene.hpp>
#include <Level2Scene.hpp>
#include <Level3Scene.hpp>
#include <MenuScene.hpp>
#include <InstructionScene.hpp>

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController();

    void showMenu();
    void showInstructions(int level);
    void startLevel(int level);
    void showEnding();

private:
    QGraphicsView *m_view;

};



#endif