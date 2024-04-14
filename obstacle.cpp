#include "obstacle.h"
#include "car.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>

Obstacle::Obstacle()
{
    setPixmap(QPixmap(":/resources/images/coin1.png"));

}

