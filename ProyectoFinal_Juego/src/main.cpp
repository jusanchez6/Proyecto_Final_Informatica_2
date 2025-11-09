#include <QApplication>
#include <QGraphicsView>
#include <Level1Scene.hpp>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Level1Scene *scene = new Level1Scene();
    QGraphicsView view(scene);
    view.setWindowTitle("Nivel 1 - Evacuación");
    view.setFixedSize(800, 600);
    view.setBackgroundBrush(Qt::black);
    view.show();

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