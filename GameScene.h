#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsView>
#include <QPushButton>
#include <RouteSelectionScreen.h>
#include <QGraphicsTextItem>
#include <startline.h>


///
/// \brief The GameScene class
///
/// creates a new QGraphicsView Widget that can be added/showed in mainLayout (QGridLayout) of mainwindow
/// on this widget the game takes place
class GameScene: public QGraphicsView
{
public:
    ///
    /// \brief GameScene constructor
    /// \param currentUsername the current active users name
    ///
    GameScene(QString currentUsername);

    ///
    /// \brief gameScene
    ///
    /// should not be removed before GameScene gets closed
    QGraphicsScene *gameScene;

    //QGraphicsRectItem *rectangle;

    StartLine * start;

    Car *getTheCar() const;

protected:
    Car * theCar;
    Car * car1;

};

#endif // GAMESCENE_H
