#include <HighscoreDialog.h>
#include <QDebug>

HighscoreDialog::HighscoreDialog(QWidget *parent)
    : QWidget(parent)
{
    //set Layout for ExitGameDialog
    highscoreLayout = new QGridLayout;

    //create and add QLabel Text to ExitGameDialog
    QLabel * highscoreText = new QLabel(tr("The best player is..."));
    highscoreLayout->addWidget(highscoreText, 0, 0);

    this->addUsersHighscoresToScreen();

    //alter Dialog
    setWindowTitle(tr("Highscores"));
    setLayout(highscoreLayout);
}

void HighscoreDialog::addUsersHighscoresToScreen()
{
    userprofile = new UserProfile;
    std::vector<std::string> userSortedByHighscoreVector = userprofile->returnAllUsernamesSortedByHighscore();
    int vectorSize = userSortedByHighscoreVector.size();
    QString listOfUserHighscores;

    //add all users with highscore to the screen
    for (int i = 0; i < vectorSize ; i++ ) {
       QString rankingPlace = QString::number(i + 1);
       listOfUserHighscores = listOfUserHighscores + "\n" + rankingPlace + ". " + QString::fromStdString(userSortedByHighscoreVector[i]);
    }
    QLabel * userText = new QLabel(listOfUserHighscores);
    highscoreLayout->addWidget(userText, 1, 1);
}
