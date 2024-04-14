#include <GameOverScreen.h>
#include <QDebug>
#include <mainwindow.h>

GameOverScreen::GameOverScreen(QWidget *parent, QString currentUsername): QWidget(parent)
{
    publicCurrentUsername = currentUsername;
    UserProfile * userprofile = new UserProfile;

    //create Gridlayout for the Startmenu/screen
    gameOverScreenGridLayout = new QGridLayout();
    gameOverScreenGridLayout->setSizeConstraint(QLayout::SetFixedSize);


    //create Text for game over screen
    QLabel * gameOverText = new QLabel("Congratulations " + currentUsername + ", you finished the race ... ");
    gameOverScreenGridLayout->addWidget(gameOverText, 0, 0, 1, 3);

    QLabel * currentHighscoreText = new QLabel("Your highscore: " + QString::number(userprofile->getHighscore(currentUsername)) + " seconds");
    gameOverScreenGridLayout->addWidget(currentHighscoreText, 1, 2);

    neededTimeForRaceText = new QLabel("");
    gameOverScreenGridLayout->addWidget(neededTimeForRaceText, 1, 0);

    collectedCoinsText = new QLabel("");
    gameOverScreenGridLayout->addWidget(collectedCoinsText, 2, 0, 1, 3);

    //create Buttons to select Landscape
    goBackToRouteSelectionScreenButton = new QPushButton("go back to menu");
    connect(goBackToRouteSelectionScreenButton, SIGNAL(clicked()), this, SIGNAL(goBackToRouteSelectionScreenButtonClicked()));
    gameOverScreenGridLayout->addWidget(goBackToRouteSelectionScreenButton, 3, 0, 1, 3);

    //create Button to open shop
    restartGameButton = new QPushButton("restart Game");
    connect(restartGameButton, SIGNAL(clicked()), this,SIGNAL(restartGameButtonClicked()));
    gameOverScreenGridLayout->addWidget(restartGameButton, 4, 0, 1, 3);

    //alter window
    setFixedSize(1700,1000);
    setLayout(gameOverScreenGridLayout);
    this->setStyleSheet("QLabel{background-color: rgba(12, 199, 197, 0.8); }");
}

void GameOverScreen::setTextLabelNeededTimeForRace(double neededTimeForRace)
{
    neededTimeForRaceText->setText("Your time: " + QString::number(neededTimeForRace) + " seconds");
}

void GameOverScreen::setTextLabelCollectedCoins(int collectedCoins)
{
    collectedCoinsText->setText("You collected " + QString::number(collectedCoins)+ " Coins.");
}

GameOverScreen::~GameOverScreen()
{

}
