#include <mainwindow.h>
#include "ui_Mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //create main Gridlayout
    mainLayout = new QGridLayout;

    //add startGame Button
    startGameButton = new QPushButton ("Start game");
    startGameButton->setStyleSheet("QPushButton{background-image: url(:/resources/images/backgroundMainwindow.png);}"
                                                 "QPushButton:hover {background-image: url(:/resources/images/BackgroundButtons.png);}");
    connect(startGameButton, &QPushButton::clicked, this, &MainWindow::startGame);

    mainLayout->addWidget(startGameButton, 1, 0);

    //add exitGame Button
    exitGameButton = new QPushButton ("Exit game");
    exitGameButton->setStyleSheet("QPushButton{background-image: url(:/resources/images/backgroundMainwindow.png);}"
                                  "QPushButton:hover {background-image: url(:/resources/images/BackgroundButtons.png);}");
    connect(exitGameButton, &QPushButton::clicked, this, &MainWindow::openEscapeDialog);
    mainLayout->addWidget(exitGameButton, 2, 0);
    exitGameButton->setVisible(false);

    // initalize dialogs with nullptr
    exitGameDialog = NULL;
    gameOverScreen = NULL;
    routeSelectionScreen = NULL;

    //create Screens that are needed in the game
    routeSelectionScreen = new RouteSelectionScreen(nullptr, currentUsername);
    mainLayout->addWidget(routeSelectionScreen, 0, 0);

    //Create and add MenuBar to Mainwindow
    basicInformations = new QMenuBar();
    MainWindow::setMenuBar(basicInformations);

    //create Player Selction Menu
    selectPlayer = basicInformations->addMenu(tr("Select Player"));

    //create and open StartScreen
    startScreen = new Startscreen;
    openStartScreen();

    //create default central Widget
    main = new MainScene;
    main->setLayout(mainLayout);
    MainWindow::setCentralWidget(main);

    //add Actions to Player Selection Menu
    QAction * createNewUserAction = new QAction("create new user");
    connect(createNewUserAction, &QAction::triggered, this, &MainWindow::openStartScreen);
    selectPlayer->addAction(createNewUserAction);
    this->addUsersToPlayerSelectionMenu();

    isGameAlreadyEntered = true;

//    //Create Carinformation Menu
//    QMenu * carInformation = basicInformations->addMenu(tr("Car Information"));
//    QAction * gameOverTest = new QAction("test game over screen");
//    connect(gameOverTest, &QAction::triggered, this, &MainWindow::openGameOverScreen);
//    carInformation->addAction(gameOverTest);

    //create Achievements Information Menu
    QMenu * achievementsInformation = basicInformations->addMenu(tr("Achievements"));

    QAction * highscoreUserAction = new QAction(tr("Highscores"));
    connect(highscoreUserAction, &QAction::triggered, this, &MainWindow::openHighscoreDialog);
    achievementsInformation->addAction(highscoreUserAction);


    QAction * achievementsAction = new QAction(tr("Achievements"));
    connect(achievementsAction, &QAction::triggered, this, &MainWindow::openAchievementsDialog);
    achievementsInformation->addAction(achievementsAction);

    // alter window
    setFixedSize(1700,1000);

    //avoid focus on mainscene (background)
    main->setFocusPolicy(Qt::NoFocus);
}

void MainWindow::openStartScreen()
{
    startScreen->setFocus();
    startScreen->exec();

    this->checkIfUserIsChoosen();
}


//Function should create new user or select user from combobox
void MainWindow::checkIfUserIsChoosen()
{
    if(startScreen->createAccountClicked() != "")
    {
        currentUsername = startScreen->getNameUser();
        if (!currentUser->addNewUser(currentUsername))
        {
            startScreen->changeWelcomeText("Username already exists, please choose another name!");
            this->openStartScreen();
        }
        if (isGameAlreadyEntered == true && currentUsername != "") {
            QAction * newPlayerAction;
            newPlayerAction = new QAction(currentUsername);

            connect(newPlayerAction, &QAction::triggered, this,
                    [=] () {this->selectUser(currentUsername);});
            selectPlayer->addAction(newPlayerAction);
        }
    } else if (startScreen->createAccountClicked() == "")
    {
        currentUsername = startScreen->enterGame();
    }
   routeSelectionScreen->setCurrentUsername(currentUsername);
   this->setWindowTitle(currentUsername + " is racing now :)");
}

void MainWindow::startGame()
{
    qDebug() << "entered (start) game";

    playingGameScene = new GameScene(currentUsername);
    connect(playingGameScene->start, SIGNAL(openGameOverScreenFromStartlineSIGNAL()), this, SLOT(openGameOverScreen()));
    mainLayout->addWidget(playingGameScene, 0, 0);

    routeSelectionScreen->setVisible(false);
    playingGameScene->setVisible(true);

    startGameButton->setVisible(false);
    exitGameButton->setVisible(true);

    basicInformations->setEnabled(false);
    playingGameScene->setFocus();
}

void MainWindow::openEscapeDialog()
{
    exitGameDialog = new ExitGameDialog;
    exitGameDialog->show();

    playingGameScene->getTheCar()->setGamestatus(0);

    //connect signals ExitGameDialog with slots in mainwindow
    connect(exitGameDialog, SIGNAL(exitGameButtonInDialogClicked()), this, SLOT(exitGame()));
    connect(exitGameDialog, SIGNAL(restartButtonInDialogClicked()), this, SLOT(restartGame()));
    connect(exitGameDialog, SIGNAL(closeExitGameDialog()), this, SLOT(backToGame()));
}

//Functions adds all Usernames from Database to the PlayerSelection Menu
void MainWindow::addUsersToPlayerSelectionMenu()
{
    std::vector<std::string> allUsernames = currentUser->returnAllUsernames();
    int sizeOfAllUsersArray = allUsernames.size();

    for (int i = 0 ; i < sizeOfAllUsersArray ;i++ ) {
      std::string name = allUsernames[i];
      QString usernameForPlayerSelectionMenu = QString::fromStdString(name);
      QAction * selectUSernameAction = new QAction(usernameForPlayerSelectionMenu);
      connect(selectUSernameAction, &QAction::triggered, this,
              [=] () {this->selectUser(usernameForPlayerSelectionMenu);});
      selectPlayer->addAction(selectUSernameAction);
    }
}

//Functions changes the current User in Mainwindow, routeSelectionScreen an ShopDialog
void MainWindow::selectUser(QString username)
{
    currentUsername = username;
    this->setWindowTitle(currentUsername + " is racing now :)");
    routeSelectionScreen->setCurrentUsername(currentUsername);
}

void MainWindow::setTheCar(Car *value)
{
    theCar = value;
}

void MainWindow::openHighscoreDialog()
{
    highscoreDialog = new HighscoreDialog();
    highscoreDialog->setFocus();
    highscoreDialog->show();
}

void MainWindow::openAchievementsDialog()
{
    achievementsDialog = new AchievementsDialog(nullptr, currentUsername);
    achievementsDialog->setFocus();
    achievementsDialog->show();
}

void MainWindow::exitGame()
{
    qDebug() << "exit Game entered";

    routeSelectionScreen->setVisible(true);
    startGameButton->setVisible(true);
    basicInformations->setEnabled(true);

    if (gameOverScreen != NULL) {
        gameOverScreen->setVisible(false);
    }

    if (exitGameDialog != NULL) {
        qDebug() << "test";
        exitGameDialog->close();
        playingGameScene->setVisible(false);
        exitGameButton->setVisible(false);
    }
    qDebug() << "test 2";
}

void MainWindow::restartGame()
{
    qDebug() << "entered restart Game";
    this->exitGame();
    this->startGame();
}

void MainWindow::openGameOverScreen()
{
    qDebug()<< "entered GameOverScreen";
    gameOverScreen = new GameOverScreen(nullptr, currentUsername);
    mainLayout->addWidget(gameOverScreen, 0, 0);

    routeSelectionScreen->setVisible(false);

    playingGameScene->setVisible(false);
    exitGameButton->setVisible(false);

    double neededTimeForRound = playingGameScene->start->getNeededTimeForRace();
    gameOverScreen->setTextLabelNeededTimeForRace(neededTimeForRound);

    int collectedCoins = playingGameScene->start->getCollectedCoins();
    gameOverScreen->setTextLabelCollectedCoins(collectedCoins);

    connect(gameOverScreen, SIGNAL(restartGameButtonClicked()), this, SLOT(restartGame()));
    connect(gameOverScreen, SIGNAL(goBackToRouteSelectionScreenButtonClicked()), this, SLOT(exitGame()));

    this->checkIfNewAchievementIsReached();
}

void MainWindow::checkIfNewAchievementIsReached()
{
    UserProfile * userprofile = new UserProfile;
    std::vector<double> highscoreAchievementsValues{70.0, 50.0, 30.0, 20.0}; // tbd add values to get achievement that are realistic
    std::vector<std::string> highscoreAchievements{"Fast racer"  , "Speedful mind", "Supermario", "The very best"};
    std::vector<double> moneyAchievementsValues{500, 1000, 1500, 2000};
    std::vector<std::string> moneyAchievements{"Piggybank" , "Bankbook" , "Investor", "Millionaire"};
    std::vector<double> playedGamesAcievementsValues{10, 50, 200, 500};
    std::vector<std::string> playedGamesAchievements{"Skilled Racer" , "Advanced Racer" , "Expert Racer", "Master Racer"};

    for (int i = 0; i<3 ; i++) {
        if (userprofile->getHighscore(currentUsername) >= highscoreAchievementsValues[i] && userprofile->getHighscoreAchievementNumber(currentUsername) < i+1) {
            ReceiveAchievementDialog * highscoreAchievementDialog = new ReceiveAchievementDialog(nullptr, currentUsername, "You gained the trophy " + QString::fromStdString(highscoreAchievements[i]));
            highscoreAchievementDialog->show();
            userprofile->updateHighscoreAchievementNumber(currentUsername);
        }
        if (userprofile->getMoneyUser(currentUsername) >= moneyAchievementsValues[i] && userprofile->getMoneyAchievementNumber(currentUsername) < i+1) {
            ReceiveAchievementDialog * moneyAchievementsDialog = new ReceiveAchievementDialog(nullptr, currentUsername, "You gained the trophy " + QString::fromStdString(moneyAchievements[i]));
            moneyAchievementsDialog->show();
            userprofile->updateMoneyAchievementNumber(currentUsername);
        }
        if (userprofile->getPlayedGames(currentUsername) >= playedGamesAcievementsValues[i] && userprofile->getPlayedGamesAchievementNumber(currentUsername) < i+1) {
            ReceiveAchievementDialog * playedGamesAchievementDialog = new ReceiveAchievementDialog(nullptr, currentUsername, "You gained the trophy: " + QString::fromStdString(playedGamesAchievements[i]));
            playedGamesAchievementDialog->show();
            userprofile->updatePlayedGamesAchievementNumber(currentUsername);
        }
    }
}

void MainWindow::backToGame()
{
    playingGameScene->getTheCar()->setGamestatus(1);
    exitGameDialog->close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
