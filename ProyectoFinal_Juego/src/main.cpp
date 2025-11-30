/**
 * @file main.cpp
 * @brief Punto de entrada principal del juego
 * @authors John Tristancho
 *          Julian Sanchez
 * 
 * @date 29/11/2025
 * @version 1.0
 */

#include <QApplication>
#include <QGraphicsView>
#include <GameController.hpp>

/**
 * @brief Función principal del juego
 * @param argc Número de argumentos
 * @param argv Array de argumentos
 * @return Código de salida de la aplicación
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GameController game;
    game.showMenu();

    return app.exec();
}