/// @file startline.h
/// In this file we define methods and attributes in order to
/// make sure that the race is being held in proper manner.
/// After passing starting- line the first, second and third time
/// it is being signalised that the race is over



#ifndef STARTLINE_H
#define STARTLINE_H
#include <QObject>
#include <QGraphicsPolygonItem>
#include <checkpoint.h>
#include <UserProfile.h>
#include <car.h>


/// \brief The StartLine class
///
///
class StartLine: public Checkpoint

{
    Q_OBJECT
public:

/// \brief Constructor to call in order to add the startline to game scene
    StartLine();
    StartLine(QString currentUsername);

/// \brief Startline is defined through a polygon created from a vector of points
    QGraphicsPolygonItem * start;

    ///
    /// \brief publicCurrentUsername the variable to use the currentUsername in every function of the class (it is equal to currentUsername)
    ///
    QString publicCurrentUsername;

    ///
    /// \brief getNeededTimeForRace gets time the car needed to get 3 times through the startline from class car
    /// \return a double with the time user needed to finish the race
    ///
    double getNeededTimeForRace();

    ///
    /// \brief getCollectedCoins gets the public variable from car with value of collectedCoins
    /// \return an integer with the sum of coins that have been collected from car during the race
    ///
    int getCollectedCoins();

signals:
    ///
    /// \brief openGameOverScreenFromStartlineSIGNAL leads to set invisible the playingGameScene and opens the gameOverScreen when game is finished
    ///
    /// is connected with slot openGameOverScreen() in mainwindow
    void openGameOverScreenFromStartlineSIGNAL();

public slots:
/// \brief In this function, we make sure that the lap is successfuly closed; after third one we end the game
    void checkLap();

public:
/// \brief Variable to increment when the first lap is finished
    int lap = 0;
/// \brief Variable to increment when the third lap is finished
    int third_lap = 0;
/// \brief Variable to increment in order to give signal that the race is finished
    int finished_race = 0;

///
/// \brief userprofile gives intersection from the application to the database
///
/// should not be removed before the startline gets deleted
    UserProfile * userprofile;

    void setTheCar(Car *value);

/// \brief Instance of car in which we copy the value of car added in game scene
protected:
    Car *theCar;
};

#endif // STARTLINE_H
