#include <QApplication>
#include <QGraphicsView>
#include <GameController.hpp>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GameController game;
    game.showMenu();

    return app.exec();
}


// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);

//     // Crear vista principal
//     QGraphicsView view;
//     view.setWindowTitle("Proyecto Final - nivel3");
//     view.setFixedSize(736, 841);

//     // Crear escenas
//     //Level1Scene *level1 = new Level1Scene();
//     //Level2Scene *level2 = new Level2Scene();
//     Level3Scene *level3 = new Level3Scene();

//     // // Conectar niveles (avanza al siguiente cuando termina)
//     // QObject::connect(level1, &Level1Scene::levelCompleted, [&]() {
//     //     view.setScene(level2);
//     // });

//     // QObject::connect(level2, &Level2Scene::levelCompleted, [&]() {
//     //     view.setScene(level3);
//     // });

//     // Mostrar primer nivel
//     // level2->setView(&view);   // muy importante: da foco al jugador
//     // view.setScene(level2);
//     // view.show();



//     // Asignar la escena a la vista
//     view.setScene(level3);
//     view.show();

//     return app.exec();
// }


// #include <QApplication>
// #include <QGraphicsView>
// #include <QGraphicsScene>
// #include <QGraphicsRectItem>
// #include <QMouseEvent>
// #include <QDebug>

// class ColliderEditor : public QGraphicsView {
//     QGraphicsScene scene;
//     QPointF start;
//     bool drawing = false;
// public:
//     ColliderEditor() {
//         setScene(&scene);
//         scene.addPixmap(QPixmap("../assets/backgrounds/Bg_level1.jpg").scaled(736, 841));
//         setFixedSize(736, 841);
//     }

// protected:
//     void mousePressEvent(QMouseEvent *e) override {
//         start = mapToScene(e->pos());
//         drawing = true;
//     }
//     void mouseReleaseEvent(QMouseEvent *e) override {
//         if (!drawing) return;
//         QPointF end = mapToScene(e->pos());
//         QRectF r(QPointF(qMin(start.x(), end.x()), qMin(start.y(), end.y())),
//                  QPointF(qMax(start.x(), end.x()), qMax(start.y(), end.y())));
//         auto *rect = scene.addRect(r, QPen(Qt::red), QBrush(QColor(255, 0, 0, 80)));
//         qDebug() << "QRectF(" << r.x() << "," << r.y() << "," << r.width() << "," << r.height() << "),";
//         drawing = false;
//     }
// };

// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);
//     ColliderEditor editor;
//     editor.show();
//     return app.exec();
// }
