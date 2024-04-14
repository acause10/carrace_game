/// @file innerbounds.h
/// In this file, a polygon item is created serving the purpose of
/// "inner" bounds of the racetrack. We check possible collisions between
/// this polygon and the car, and if there are any, there will also be an elastic hit.


#ifndef INNERBOUNDS_H
#define INNERBOUNDS_H
#include <QGraphicsPolygonItem>
#include <QObject>
#include "car.h"

/// \brief The Innerbounds class
class Innerbounds :public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:

/// \brief Constructor to call in game scene
/// \details  Add the inner bounds of track to the game scene
    Innerbounds();

/// \brief Instance of QGraphicsItem that defines the polygon created from previously defined vector of points
    QGraphicsPolygonItem * inner_poly;

/// \brief Method to set the car- value, in order to obtain the address from a car added in game scene
    void setTheCar(Car *value);

protected:
/// \brief Instance of car in which we copy the value of car added in game scene
    Car *theCar;
/// \brief Boolean flag to avoid extra rebounce
    bool canrebounce=true;
public slots:
/// \brief Function to check possible collisions of "inner_poly" with the instance of car
    void checkCollision();

};

#endif // TRACKBOUNDS_H
