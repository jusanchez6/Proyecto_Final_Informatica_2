#include <Level3Scene.hpp>


Level3Scene::Level3Scene(QObject *parent)
    : QGraphicsScene(parent), m_selected(nullptr), m_dragLine(nullptr), m_time(0.0f)
{
    setSceneRect(0, 0, 800, 600);
    setBackgroundBrush(Qt::black);

    // hint text
    m_hintText = addText("Nivel 3 - Control Aéreo: click y arrastra para fijar rumbo", QFont("Arial", 12));
    m_hintText->setDefaultTextColor(Qt::white);
    m_hintText->setPos(10, 10);

    // spawn some planes
    spawnPlanes();

    // loop
    connect(&m_gameLoop, &QTimer::timeout, this, &Level3Scene::updateScene);
    m_gameLoop.start(16);
}

// create 4 planes with different velocities
void Level3Scene::spawnPlanes() {
    for (int i = 0; i < 4; ++i) {
        QPixmap pix("../assets/sprites/Level3_plane1.png");
        if (pix.isNull()) pix = QPixmap(32,32); // fallback
        pix = pix.scaled(32,32);
        float x = 150 + i * 140;
        float y = 100 + (i%2)*200;
        // random-ish velocities
        QPointF vel((QRandomGenerator::global()->bounded(30, 80) - 50) / 10.0f,
                    (QRandomGenerator::global()->bounded(0, 60) - 30) / 10.0f);
        Plane* p = new Plane(pix, QPointF(x,y), vel);
        addItem(p);
        m_planes.append(p);
    }
}

// selection helpers
Plane* Level3Scene::planeAtPos(const QPointF &p) {
    for (auto *plane : m_planes) {
        if (plane->contains(plane->mapFromScene(p)))
            return plane;
    }
    return nullptr;
}

void Level3Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPointF p = event->scenePos();
    Plane* hit = planeAtPos(p);
    if (hit) {
        m_selected = hit;
        // create drag line
        if (!m_dragLine) {
            m_dragLine = addLine(QLineF(p, p), QPen(Qt::green));
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void Level3Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (m_selected && m_dragLine) {
        QLineF line(m_selected->pos(), event->scenePos());
        m_dragLine->setLine(line);
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void Level3Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (m_selected && m_dragLine) {
        QPointF dir = event->scenePos() - m_selected->pos();
        if (qFuzzyIsNull(dir.x()) && qFuzzyIsNull(dir.y())) {
            // toggle holding pattern if click without drag
            m_selected->setState( (m_selected->state() == Plane::Holding) ? Plane::Cruising : Plane::Holding );
        } else {
            // set velocity proportional to drag vector
            QPointF newVel = dir / 10.0; // scale down
            m_selected->setVelocity(newVel);
            m_selected->setState(Plane::Cruising);
        }
        removeItem(m_dragLine);
        delete m_dragLine;
        m_dragLine = nullptr;
    }
    m_selected = nullptr;
    QGraphicsScene::mouseReleaseEvent(event);
}

void Level3Scene::keyPressEvent(QKeyEvent *event) {
    // allow nudging selected plane with arrows
    if (m_selected) {
        QPointF v = m_selected->velocity();
        float delta = 1.0f;
        switch (event->key()) {
        case Qt::Key_Up:    v += QPointF(0, -delta); break;
        case Qt::Key_Down:  v += QPointF(0, delta); break;
        case Qt::Key_Left:  v += QPointF(-delta, 0); break;
        case Qt::Key_Right: v += QPointF(delta, 0); break;
        case Qt::Key_H:     m_selected->setState(Plane::Holding); return;
        case Qt::Key_C:     m_selected->setState(Plane::Cruising); return;
        default: break;
        }
        m_selected->setVelocity(v);
    }
    QGraphicsScene::keyPressEvent(event);
}

void Level3Scene::predictConflicts() {
    // simple pairwise linear prediction: check if two planes come within threshold in next T seconds
    const float T = 6.0f; // seconds to predict
    const float dt = 0.5f;
    const float threshold = 30.0f; // px separation considered conflict

    // clear visual flags (reset color)
    for (auto *p : m_planes) {
        p->setOpacity(1.0);
    }

    for (int i = 0; i < m_planes.size(); ++i) {
        for (int j = i + 1; j < m_planes.size(); ++j) {
            Plane* a = m_planes[i];
            Plane* b = m_planes[j];
            for (float t = 0.0f; t <= T; t += dt) {
                QPointF pa = a->predictPos(t);
                QPointF pb = b->predictPos(t);
                if (QLineF(pa, pb).length() < threshold) {
                    // mark both planes (assistant warning)
                    a->setOpacity(0.5);
                    b->setOpacity(0.5);
                    break;
                }
            }
        }
    }
}

void Level3Scene::updateScene() {
    float dt = 0.016f;
    m_time += dt;

    // update plane positions
    for (auto *p : m_planes) {
        p->update(dt);
    }

    // assistant prediction
    predictConflicts();

    // optional: wrap planes around screen for demo
    for (auto *p : m_planes) {
        QPointF pos = p->pos();
        bool changed = false;
        if (pos.x() < -50) { pos.setX(850); changed = true; }
        if (pos.x() > 850)  { pos.setX(-50); changed = true; }
        if (pos.y() < -50)  { pos.setY(650); changed = true; }
        if (pos.y() > 650)  { pos.setY(-50); changed = true; }
        if (changed) p->setPos(pos);
    }
}
