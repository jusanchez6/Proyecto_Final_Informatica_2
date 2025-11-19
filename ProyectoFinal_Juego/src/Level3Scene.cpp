#include <Level3Scene.hpp>

Level3Scene::Level3Scene(QObject *parent)
    : QGraphicsScene(parent), m_selected(nullptr), m_dragLine(nullptr), m_time(0.0f)
{
    setSceneRect(0, 0, 736, 841);
    setBackgroundBrush(Qt::black);
    QPixmap bg("../assets/backgrounds/Bg_level3.png");

    if (!bg.isNull())
    {
        QGraphicsPixmapItem *background = addPixmap(bg.scaled(736, 841));
        background->setZValue(-100);
    }
    else
    {
        qWarning() << "No se pudo cargar el fondo.";
    }

    // hint text
    m_hintText = addText("Nivel 3 - Control Aéreo: click y arrastra para fijar rumbo", QFont("Arial", 12));
    m_hintText->setDefaultTextColor(Qt::white);
    m_hintText->setPos(10, 10);

    // spawn some planes
    spawnPlanes();

    // spawn de las zonas de peligro
    connect(&m_dangerTimer, &QTimer::timeout, this, &Level3Scene::spawnDangerZones);
    m_dangerTimer.start(6000); // cada 6 segundos aparece una nueva zona

    connect(&safeZoneTimer, &QTimer::timeout, this, &Level3Scene::spawnSafeZones);
    safeZoneTimer.start(12000);

    // loop
    connect(&m_gameLoop, &QTimer::timeout, this, &Level3Scene::updateScene);
    m_gameLoop.start(16);
}

void Level3Scene::spawnPlanes()
{
    for (int i = 0; i < 6; ++i)
    {
        QPixmap pix("../assets/sprites/Level3_plane2.png");
        if (pix.isNull())
            pix = QPixmap(32, 32);
        pix = pix.scaled(32, 32);

        // posiciones seguras dentro de la escena
        float x = QRandomGenerator::global()->bounded(50, sceneRect().width() - 50);
        float y = QRandomGenerator::global()->bounded(50, sceneRect().height() - 50);

        // velocidades aleatorias pero más rápidas
        QPointF vel((QRandomGenerator::global()->bounded(-80, 80)) / 10.0f,
                    (QRandomGenerator::global()->bounded(-80, 80)) / 10.0f);

        Plane *p = new Plane(pix, QPointF(x, y), vel);
        addItem(p);
        m_planes.append(p);
    }
}
// selection helpers
Plane *Level3Scene::planeAtPos(const QPointF &p)
{
    for (auto *plane : m_planes)
    {
        QPointF local = plane->mapFromScene(p);
        if (plane->boundingRect().contains(local))
            return plane;
    }
    return nullptr;
}

void Level3Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF p = event->scenePos();
    Plane *hit = planeAtPos(p);
    if (hit)
    {
        m_selected = hit;
        // create drag line
        if (!m_dragLine)
        {
            m_dragLine = addLine(QLineF(p, p), QPen(Qt::green));
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void Level3Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_selected && m_dragLine)
    {
        QLineF line(m_selected->pos(), event->scenePos());
        m_dragLine->setLine(line);
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void Level3Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_selected && m_dragLine)
    {
        QPointF dir = event->scenePos() - m_selected->pos();
        if (qFuzzyIsNull(dir.x()) && qFuzzyIsNull(dir.y()))
        {
            // toggle holding pattern if click without drag
            m_selected->setState((m_selected->state() == Plane::Holding) ? Plane::Cruising : Plane::Holding);
        }
        else
        {
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

void Level3Scene::keyPressEvent(QKeyEvent *event)
{
    // allow nudging selected plane with arrows
    if (m_selected)
    {
        QPointF v = m_selected->velocity();
        float delta = 1.0f;
        switch (event->key())
        {
        case Qt::Key_Up:
            v += QPointF(0, -delta);
            break;
        case Qt::Key_Down:
            v += QPointF(0, delta);
            break;
        case Qt::Key_Left:
            v += QPointF(-delta, 0);
            break;
        case Qt::Key_Right:
            v += QPointF(delta, 0);
            break;
        case Qt::Key_H:
            m_selected->setState(Plane::Holding);
            return;
        case Qt::Key_C:
            m_selected->setState(Plane::Cruising);
            return;
        default:
            break;
        }
        m_selected->setVelocity(v);
    }
    QGraphicsScene::keyPressEvent(event);
}

void Level3Scene::predictConflicts()
{
    // simple pairwise linear prediction: check if two planes come within threshold in next T seconds
    const float T = 6.0f; // seconds to predict
    const float dt = 0.5f;
    const float threshold = 30.0f; // px separation considered conflict

    // clear visual flags (reset color)
    for (auto *p : m_planes)
    {
        p->setOpacity(1.0);
    }

    for (int i = 0; i < m_planes.size(); ++i)
    {
        for (int j = i + 1; j < m_planes.size(); ++j)
        {
            Plane *a = m_planes[i];
            Plane *b = m_planes[j];
            for (float t = 0.0f; t <= T; t += dt)
            {
                QPointF pa = a->predictPos(t);
                QPointF pb = b->predictPos(t);
                if (QLineF(pa, pb).length() < threshold)
                {
                    // mark both planes (assistant warning)
                    a->setOpacity(0.5);
                    b->setOpacity(0.5);
                    break;
                }
            }
        }
    }
}

void Level3Scene::spawnDangerZones()
{
    int zoneCount = QRandomGenerator::global()->bounded(2, 5);
    // 🔸 Aparecen entre 1 y 3 zonas a la vez

    const int maxAttempts = 10;

    for (int i = 0; i < zoneCount; ++i)
    {
        int attempts = 0;
        bool created = false;

        while (attempts < maxAttempts && !created)
        {
            float radius = QRandomGenerator::global()->bounded(40, 100);
            float x = QRandomGenerator::global()->bounded(static_cast<int>(radius), static_cast<int>(width() - radius));
            float y = QRandomGenerator::global()->bounded(static_cast<int>(radius), static_cast<int>(height() - radius));

            QRectF newZoneRect(x - radius, y - radius, radius * 2, radius * 2);
            bool overlapsPlane = false;

            // Evitar que la zona aparezca encima o muy cerca de un avión
            for (auto *plane : m_planes)
            {
                QRectF planeRect = plane->sceneBoundingRect();
                QRectF dangerBuffer = newZoneRect.adjusted(-30, -30, 30, 30);
                if (dangerBuffer.intersects(planeRect))
                {
                    overlapsPlane = true;
                    break;
                }
            }

            if (!overlapsPlane)
            {
                // Crear círculo rojo semitransparente
                QGraphicsEllipseItem *zone = addEllipse(newZoneRect, QPen(Qt::red), QBrush(QColor(255, 0, 0, 120)));
                zone->setZValue(-50);
                m_dangerZones.append(zone);

                // Efecto de parpadeo
                QTimer *blinkTimer = new QTimer(this);
                connect(blinkTimer, &QTimer::timeout, this, [zone]()
                        {
                    QColor current = zone->brush().color();
                    int alpha = (current.alpha() == 120) ? 40 : 120;
                    zone->setBrush(QColor(255, 0, 0, alpha)); });
                blinkTimer->start(300);

                // ⏳ Desaparece después de unos segundos
                QTimer::singleShot(6000, this, [this, zone, blinkTimer]()
                                   {
                    blinkTimer->stop();
                    blinkTimer->deleteLater();
                    removeItem(zone);
                    m_dangerZones.removeOne(zone);
                    delete zone; });

                created = true;
            }

            attempts++;
        }
    }
}

void Level3Scene::spawnSafeZones()
{
    int zoneCount = 1; // solo una zona por turno
    const int maxAttempts = 10;

    for (int i = 0; i < zoneCount; ++i)
    {
        int attempts = 0;
        bool created = false;

        while (attempts < maxAttempts && !created)
        {
            float radius = QRandomGenerator::global()->bounded(50, 120);
            float x = QRandomGenerator::global()->bounded(static_cast<int>(radius), static_cast<int>(width() - radius));
            float y = QRandomGenerator::global()->bounded(static_cast<int>(radius), static_cast<int>(height() - radius));

            QRectF newZoneRect(x - radius, y - radius, radius * 2, radius * 2);
            bool overlapsSomething = false;

            for (auto *plane : m_planes)
            {
                QRectF planeRect = plane->sceneBoundingRect();
                QRectF buffer = newZoneRect.adjusted(-30, -30, 30, 30);
                if (buffer.intersects(planeRect))
                {
                    overlapsSomething = true;
                    break;
                }
            }
            for (auto *danger : m_dangerZones)
            {
                if (danger->rect().intersects(newZoneRect))
                {
                    overlapsSomething = true;
                    break;
                }
            }

            if (!overlapsSomething)
            {
                QGraphicsEllipseItem *zone = addEllipse(newZoneRect, QPen(Qt::green), QBrush(QColor(0, 255, 0, 120)));
                zone->setZValue(-40);
                m_safeZones.append(zone);

                QTimer *pulseTimer = new QTimer(this);
                connect(pulseTimer, &QTimer::timeout, this, [zone]()
                        {
                    QColor current = zone->brush().color();
                    int alpha = (current.alpha() == 120) ? 50 : 120;
                    zone->setBrush(QColor(0, 255, 0, alpha)); });
                pulseTimer->start(400);

                QTimer::singleShot(10000, this, [this, zone, pulseTimer]()
                                   {
                    pulseTimer->stop();
                    pulseTimer->deleteLater();
                    removeItem(zone);
                    m_safeZones.removeOne(zone);
                    delete zone; });

                created = true;
            }

            attempts++;
        }
    }
}

void Level3Scene::endLevel(const QString &reason)
{
    m_gameLoop.stop();
    m_dangerTimer.stop();

    QGraphicsTextItem *gameOver = addText(reason, QFont("Arial", 24, QFont::Bold));
    gameOver->setDefaultTextColor(Qt::red);
    gameOver->setPos(width() / 2 - 200, height() / 2 - 50);

    emit levelCompleted(); // si querés enlazar con el siguiente nivel
}

void Level3Scene::updateScene()
{
    float dt = 0.016f;
    m_time += dt;

    // update plane positions
    for (auto *p : m_planes)
    {
        p->update(dt);

        if (static_cast<int>(m_time) % 20 == 0) // cada 20 segundos
        {
            for (auto *plane : m_planes)
            {
                QPointF v = plane->velocity();
                v *= 1.001; // aumenta 1% cada ciclo de 20 segundos
                plane->setVelocity(v);
            }
        }
    }

    // assistant prediction
    predictConflicts();

    for (auto *p : m_planes)
    {
        QPointF pos = p->pos();
        QRectF bounds = sceneRect();

        if (pos.x() < 0 || pos.x() > bounds.width() ||
            pos.y() < 0 || pos.y() > bounds.height())
        {
            qDebug() << "❌ Avión salió del mapa!";
            endLevel("¡Un avión salió del espacio aéreo!");
            return;
        }
    }

    // Detectar colisiones entre aviones
    for (int i = 0; i < m_planes.size(); ++i)
    {
        for (int j = i + 1; j < m_planes.size(); ++j)
        {
            if (m_planes[i]->collidesWithItem(m_planes[j]))
            {
                qDebug() << "Colisión entre aviones!";
                endLevel("¡Dos aviones colisionaron!");
                return;
            }
        }
    }

    // Detectar colisiones con zonas rojas
    for (auto *plane : m_planes)
    {
        for (auto *zone : m_dangerZones)
        {
            if (plane->collidesWithItem(zone))
            {
                qDebug() << "Avión entró a zona peligrosa!";
                endLevel("¡Un avión entró a una zona peligrosa!");
                return;
            }
        }
    }

    QList<Plane *> planesToRemove;

    for (auto *plane : m_planes)
    {
        for (auto *zone : m_safeZones)
        {
            QRectF zoneRect = zone->sceneBoundingRect();
            QPointF planeCenter = plane->sceneBoundingRect().center();
            QPointF zoneCenter = zoneRect.center();

            // Distancia entre el centro del avión y el centro de la zona
            float dist = QLineF(planeCenter, zoneCenter).length();
            float radius = zoneRect.width() / 2.0f;

            // Si está dentro de la zona
            if (dist < radius * 0.8)
            {
                qDebug() << "Avión llegó a zona segura!";
                planesToRemove.append(plane);
                break;
            }
        }
    }

    // Eliminar los aviones que llegaron a una zona segura
    for (auto *plane : planesToRemove)
    {
        removeItem(plane);
        m_planes.removeOne(plane);
        delete plane;
    }

    // Si todos los aviones fueron rescatados, termina el nivel
    if (m_planes.isEmpty())
    {
        endLevel("🎉 ¡Todos los aviones llegaron a zonas seguras!");
        return;
    }
}
