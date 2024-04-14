/// @file checkpoint.h
/// In this file, we create four polygons which serve
/// the purpose of "checkpoints". After passing all four checkpoints/polygons,
/// the car is able to finish its lap.


#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QGraphicsPolygonItem>
#include <QObject>

/// \brief The Checkpoint class
///
/// Creates checkpoints to track the race progress
class Checkpoint :public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT

public:
/// \brief Constructor call to checkpoints
/// \param parent
    Checkpoint(QGraphicsItem *parent=0);
public:
/// \brief First checkpoint
/// \details Instance of QGraphicsItem that defines the polygon created from previously defined vector of points. Serves the purpose of being the first checkpoint
    QGraphicsPolygonItem * checkpoint;
/// \brief Second checkpoint
/// \details Instance of QGraphicsItem that defines the polygon created from previously defined vector of points. Serves the purpose of being the second checkpoint
    QGraphicsPolygonItem * checkpoint_2;
/// \brief Third checkpoint
/// \details Instance of QGraphicsItem that defines the polygon created from previously defined vector of points. Serves the purpose of being the third checkpoint
    QGraphicsPolygonItem * checkpoint_3;
/// \brief Last checkpoint
/// \details Instance of QGraphicsItem that defines the polygon created from previously defined vector of points. Serves the purpose of being the final checkpoint
    QGraphicsPolygonItem * checkpoint_4;
public:

/// \brief Variable for first checkpoint
/// \details Variable to increment after passing through the first checkpoint
    int counter_checkpoint = 0;
/// \brief Variable for second checkpoint
/// \details Variable to increment after passing through the second checkpoint
    int counter_checkpoint_2 = 0;
/// \brief Variable for third checkpoint
/// \details Variable to increment after passing through the third checkpoint
    int counter_checkpoint_3 = 0;
/// \brief Variable for fourth checkpoint
/// \details Variable to increment after passing through the final checkpoint
    int counter_checkpoint_4 = 0;

public slots:
/// \brief Function to check possible collisions of first checkpoint with the instance of car
    int checkCheckpoint();
/// \brief Function to check possible collisions of second checkpoint with the instance of car
    int checkCheckpoint2();
/// \brief Function to check possible collisions of third checkpoint with the instance of car
    int checkCheckpoint3();
/// \brief Function to check possible collisions of fourth checkpoint with the instance of car
    int checkCheckpoint4();
};

#endif // CHECKPOINT_H
