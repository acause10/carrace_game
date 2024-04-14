#ifndef ROUTESELECTIONSCREEN_H
#define ROUTESELECTIONSCREEN_H

#include <QGridLayout>
#include <QWidget>
#include <QPushButton>
#include <ShopDialog.h>
#include <QLabel>

///
/// \brief The RouteSelectionScreen class
///
/// creates a new Widget that can be added/showed in mainLayout (QGridLayout) of mainwindow
/// it is showed ib the beginning after startscreen gets closed
/// or after when "go back to menu" - button in gameOverScreen or "exit game"-Button in exitGameDialog is clicked
class RouteSelectionScreen: public QWidget
{
    Q_OBJECT

public:
    ///
    /// \brief RouteSelectionScreen constructor
    /// \param parent
    /// \param currentUsername the current active users name
    ///
    explicit RouteSelectionScreen(QWidget *parent = nullptr, QString currentUsername = "");
    ~RouteSelectionScreen();

    ///
    /// \brief publicCurrentUsername the variable to use the currentUsername in every function of the class (it is equal to currentUsername)
    ///
    QString publicCurrentUsername;

    ///
    /// \brief setCurrentUsername changes the publicCurrentUsername in RouteSlectionScreen
    /// \param username the new username that should be commited to publicCurrentUsername
    ///
    void setCurrentUsername(QString username);
private:
    ///
    /// \brief routeSelectionGridLayout
    ///
    /// should not be removed before the mainwindow gets closed
    QGridLayout * routeSelectionGridLayout;

//    QPushButton * landscapeAsphaltButton;
//    QPushButton * landscapeDesertButton;
//    QPushButton * landscapeSpaceButton;
//    QPushButton * landscapeOceanButton;
//    QPushButton * landscapeIceButton;
//    QPushButton * landscapeMudButton;

    ///
    /// \brief shopButton when clicked opens the shopDialog
    ///
    /// should not be removed before the mainwindow gets closed
    QPushButton * shopButton;

    ///
    /// \brief startGameButton when clicked: sets invisible the RouteSelectionScreen and opens/sets visible the playingGameScene
    ///
    /// should not be removed before the mainwindow gets closed
    QPushButton * startGameButton;

    ///
    /// \brief shop the dialog that allows users to upgrade their car (maximuma acceleration, maximum speed and control)
    ///
    /// should not be removed before the mainwindow gets closed
    ShopDialog * shop;

    void openShopDialog();
};


#endif // ROUTESELECTIONSCREEN_H
