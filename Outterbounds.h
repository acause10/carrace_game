/// @file outterbounds.h
/// In this file, 2 polygons are being defined which serve the purpose
/// of being the "outter" bounds of the racetrack. Any detected collision
/// with the car results in elastic hit, which makes the car go back on the track.


#ifndef OUTTERBOUNDS_H
#define OUTTERBOUNDS_H
#include "car.h"
#include <QGraphicsPolygonItem>
#include <QObject>

/// \brief The Outterbounds class
///

class Outterbounds :public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:
/// \brief Constructor called in game scene to create outter borders
    Outterbounds();
/// \brief Polygon created from vector that holds previously defined points
    QGraphicsPolygonItem * bigger_poly;
/// \brief Polygon created from vector of points, smaller than the one previously defined
    QGraphicsPolygonItem * smaller_poly;
/// \brief Method to set the car- value, in order to obtain the address from a car added in game scene
    void setTheCar(Car *value);
protected:
/// \brief Instance of car in which we copy the value of car added in game scene
    Car *theCar;
/// \brief Boolean flag to avoid extra rebounce
    bool smallcanrebounce=true,bigcanrebounce=true;
public slots:
/// \brief Function to check possible collisions of "bigger_poly" with the instance of car
    void outOfBoundsBig();
/// \brief Function to check possible collisions of "smaller_poly" with the instance of car
    void outOfBoundsSmall();
};

#endif // OUTTERBOUNDS_H
