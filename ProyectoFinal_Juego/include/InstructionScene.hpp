/**
 * @file InstructionScene.hpp
 * @brief Escena de instrucciones del juego
 * @authors John Tristancho
 *          Julian Sanchez
 * 
 * @date 29/11/2025
 * @version 1.0
 */

#ifndef INSTRUCTIONSCENE_HPP
#define INSTRUCTIONSCENE_HPP

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <functional>

/**
 * @brief Escena que muestra las instrucciones del juego
 * 
 * Presenta el título y las instrucciones de un nivel específico
 * con opción para comenzar a jugar.
 */
class InstructionScene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @brief Constructor de la escena de instrucciones
     * @param title Título de las instrucciones
     * @param instructions Texto de las instrucciones
     * @param onStart Función a ejecutar al iniciar el nivel
     * @param parent Objeto padre
     */
    InstructionScene(const QString &title,
                     const QString &instructions,
                     std::function<void()> onStart,
                     QObject *parent = nullptr);

private:
    QGraphicsTextItem *titleText;       ///< Elemento de texto para el título
    QGraphicsTextItem *instructionText; ///< Elemento de texto para las instrucciones
};

#endif