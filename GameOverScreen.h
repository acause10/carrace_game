#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <QGridLayout>
#include <QWidget>
#include <QPushButton>
#include <QLabel>

///
/// \brief The GameOverScreen class
///
/// creates a new Widget that can be added/showed in mainLayout (QGridLayout) of mainwindow, when game is over
class GameOverScreen: public QWidget
{
    Q_OBJECT

public:

    ///
    /// \brief GameOverScreen constructor
    /// \param parent
    /// \param currentUsername the current active users name
    ///
    explicit GameOverScreen(QWidget *parent = nullptr, QString currentUsername = "");
    ~GameOverScreen();

    ///
    /// \brief publicCurrentUsername the variable to use the currentUsername in every function of the class (it is equal to currentUsername)
    ///
    QString publicCurrentUsername;

    ///
    /// \brief neededTimeForRaceText shows the time user needed to finish the race
    ///
    /// should not be removed before GameOverScreen gets closed
    QLabel * neededTimeForRaceText;

    ///
    /// \brief collectedCoinsText shows the sum of coins the user collected during the race
    ///
    /// should not be removed before the GameOverScreen gets closed
    QLabel * collectedCoinsText;

    ///
    /// \brief setTextLabelNeededTimeForRace gives the option to change the text of QLabel neededTimeForRaceText
    /// \param neededTimeForRace the time user needed for the race
    ///
    void setTextLabelNeededTimeForRace(double neededTimeForRace);

    ///
    /// \brief setTextLabelCollectedCoins gives the option to change the text of QLabel collectedCoinsText
    /// \param collectedCoins the sum of coins the user collected during the race
    ///
    void setTextLabelCollectedCoins(int collectedCoins);

signals:
    ///
    /// \brief restartGameButtonClicked
    ///
    /// is connected with signal that restartGameButton is clicked \n
    /// and with slot restartGame() in mainwindow \n
    /// leads to exit Game (and also set invisible gameOverScreen) first and opens (set visible playingGameScene) it then
    void restartGameButtonClicked();

    ///
    /// \brief goBackToRouteSelectionScreenButtonClicked
    ///
    /// is connected with signal that goBackToRouteSelectionScreenButton is clicked \n
    /// and with slot exitGame() in mainwindow \n
    /// leads to close (set invisible) the GameOverScreen and sets visible the routeSelectionScreen
    void goBackToRouteSelectionScreenButtonClicked();

private:
    ///
    /// \brief gameOverScreenGridLayout the Layout of the GameOverScreen
    ///
    /// should not be removed before GameOverScreen gets closed
    QGridLayout * gameOverScreenGridLayout;

    ///
    /// \brief goBackToRouteSelectionScreenButton
    ///
    /// should not be removed before GameOverScreen gets closed
    QPushButton * goBackToRouteSelectionScreenButton;

    ///
    /// \brief restartGameButton
    ///
    /// should not be removed before GameOverScreen gets closed
    QPushButton * restartGameButton;
};

#endif // GAMEOVERSCREEN_H
