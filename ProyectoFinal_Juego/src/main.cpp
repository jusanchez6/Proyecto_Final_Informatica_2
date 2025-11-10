#include <QApplication>
#include <QGraphicsView>
#include "Level1Scene.hpp"
#include "Level2Scene.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QGraphicsView view;
    view.setWindowTitle("Proyecto Final - Qt Game");
    view.setFixedSize(800, 600);
    view.show();

    Level1Scene *level1 = new Level1Scene();
    Level2Scene *level2 = new Level2Scene();

    QObject::connect(level1, &Level1Scene::levelCompleted, [&]() {
        view.setScene(level2);
    });

    view.setScene(level1);

    return app.exec();
}

// #include <QApplication>
// #include <QLabel>
// #include <QPixmap>
// #include <QDebug>

// int main(int argc, char *argv[]) {
//     QApplication a(argc, argv);
//     QPixmap pix("../assets/sprites/Level1_player.png");
//     qDebug() << (pix.isNull() ? "❌ No cargó" : "✅ Cargó OK");
//     QLabel label;
//     label.setPixmap(pix);
//     label.show();
//     return a.exec();
// }