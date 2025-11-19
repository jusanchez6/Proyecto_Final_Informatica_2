#ifndef MENUSCENE_HPP
#define MENUSCENE_HPP

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsPathItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QFont>
#include <functional>

class MenuScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MenuScene(std::function<void()> startCallback, QObject *parent = nullptr);

private:
    std::function<void()> m_startCallback;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};



#endif