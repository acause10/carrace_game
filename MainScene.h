#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QGraphicsView>
#include <RouteSelectionScreen.h>
#include <QGraphicsTextItem>

///
/// \brief The MainScene class
///
///  this is the Central Widget of the game, on which the mainWidgets are placed \n
///  in mainwindow the GridLayout mainLayout is set as layout for this scene
class MainScene: public QGraphicsView
{
public:
    ///
    /// \brief MainScene constructor
    ///
    MainScene();

    ///
    /// \brief mainScene
    ///
    /// should not be removed before the mainwindow gets closed
    QGraphicsScene *mainScene;
};

#endif // MAINSCENE_H
