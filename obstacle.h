/// @file obstacle.h
/// In this file, "obstacles" i.e. coins, are being defined using
/// a QPixmap function, which sets their appearance from .png file.


#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

/// \brief The Obstacle class
///
class Obstacle:public QObject, public QGraphicsPixmapItem
{
public:
/// \brief Constructor called in game scene to add "obstacles" i.e. coins to the game scene
    Obstacle();

};

#endif // OBSTACLE_H
