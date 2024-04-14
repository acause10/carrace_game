#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <RouteSelectionScreen.h>
#include <QPushButton>
#include <GameScene.h>
#include <QLabel>
#include <MainScene.h>
#include <Startscreen.h>
#include <ExitGameDialog.h>
#include <DatabaseManager.h>
#include <UserProfile.h>
#include <HighscoreDialog.h>
#include <AchievementsDialog.h>
#include <GameOverScreen.h>
#include <startline.h>
#include <ReceiveAchievementDialog.h>


namespace Ui {
class MainWindow;
}

///
/// \brief The MainWindow class
///
/// in this class all screens and dialogs get created and gesteuert
class MainWindow: public QMainWindow{
    Q_OBJECT
public:
    ///
    /// \brief MainWindow constructor
    /// \param parent
    ///
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    ///
    /// \brief startScreen the dialog window that comes at first, when opening the application
    ///
    Startscreen * startScreen;

    void setTheCar(Car *value);

public slots:
    ///
    /// \brief exitGame sets invisible or closes the current active screens/dialogs and reurns to the routeSelectionScreen
    ///
    /// slot that is connected with the exitGame Button in exitGame Dialog
    void exitGame();

    ///
    /// \brief restartGame first exits the game and then starts it again
    ///
    void restartGame();

    ///
    /// \brief openGameOverScreen replaces the playingGameScene with a new GameOverScreen
    ///
    /// querys information about highscore, neededTime for the game and collected coins \n
    /// and shows them on the screen
    void openGameOverScreen();

    ///
    /// \brief backToGame closes the exitGame Diaolog and continues the game (and runningtime)
    ///
    void backToGame();

private:
        ///
        /// \brief ui
        ///
        /// should not be removed before the mainwindow gets closed
        Ui::MainWindow *ui;

        ///
        /// \brief mainLayout
        ///
        /// should not be removed before the mainwindow gets closed
        QGridLayout *mainLayout;

        ///
        /// \brief routeSelectionScreen the screen on which you can enter the game and upgrade your car
        ///
        /// should not be removed before the mainwindow gets closed
        RouteSelectionScreen * routeSelectionScreen;

        ///
        /// \brief basicInformations the menubar of the mainwindow
        ///
        /// should not be removed before the mainwindow gets closed
        QMenuBar *basicInformations;

        ///
        /// \brief startGameButton when clicked leads to playingGameScene
        ///
        /// should not be removed before the mainwindow gets closed
        QPushButton * startGameButton;

        ///
        /// \brief exitGameButton when clicked leads to exitGame (-Method)
        ///
        /// should not be removed before the mainwindow gets closed
        QPushButton * exitGameButton;

        ///
        /// \brief exitGameDialog the Dialog that gives options to continue, restart or quit the game (playingGameScene)
        ///
        /// should not be removed before the mainwindow gets closed
        ExitGameDialog *exitGameDialog;

        ///
        /// \brief playingGameScene the Scene on which the Game (race) takes place
        ///
        /// should not be removed before the mainwindow gets closed
        GameScene * playingGameScene;

        ///
        /// \brief qMain the mainScene of the Game on which everything else is placed
        ///
        ///  should not be removed before the mainwindow gets closed
        MainScene *main;

        ///
        /// \brief selectPlayer the part of the menubar on which you can choose an existing player from the database or create an new user
        ///
        ///  should not be removed before the mainwindow gets closed
        QMenu * selectPlayer;

        ///
        /// \brief currentUser a object of UserProfile with the information about current active user
        ///
        /// should not be removed before the mainwindow gets closed
        UserProfile * currentUser;

        ///
        /// \brief highscoreDialog the dialog, that shows all users that already have played at least one gmae in ascending order of thier highscore
        ///
        /// should not be removed before the it gets closed
        HighscoreDialog * highscoreDialog;

        ///
        /// \brief achievementsDialog the dialog that shows the achievement the current active user has already reached
        ///
        /// should not be removed before the mainwindow gets closed
        AchievementsDialog * achievementsDialog;

        ///
        /// \brief gameOverScreen the screen that replaces the playing game scene in the end of the race
        ///
        /// shows the needed time for the race, selected coins during the race and the current highscore of user \n
        /// and gives options to play a new game or go back to menu \n
        /// should not be removed before the mainwindow gets closed \n
        GameOverScreen * gameOverScreen;

        QString currentUsername;
        bool isGameAlreadyEntered = false;

        void startGame();
        void openEscapeDialog();
        void openStartScreen();
        void checkIfUserIsChoosen();
        void addUsersToPlayerSelectionMenu();
        void openHighscoreDialog();
        void openAchievementsDialog(); 
        void checkIfNewAchievementIsReached();

private slots:
        void selectUser(QString username);

protected:
        Car * theCar;
};

#endif // MAINWINDOW_H
