#include <AchievementsDialog.h>
#include <QDebug>
#include <ReceiveAchievementDialog.h>

AchievementsDialog::AchievementsDialog(QWidget * parent, QString currentUsername)
    : QWidget(parent)
{
    publicCurrentUsername = currentUsername;
    userprofile = new UserProfile;

    achievementsLayout = new QGridLayout;

    //create information labels and add them to the gridLayout
    QLabel * achievementsInformationText = new QLabel(tr("Your achievements: "));
    QLabel * highscoreAchievementInformation = new QLabel(tr("Reached highscores"));
    QLabel * moneyAchievementInformation = new QLabel(tr("Saved money"));
    QLabel * playedGamesAchievementInformation = new QLabel(tr("Played Games"));
    achievementsLayout->addWidget(achievementsInformationText, 0, 0);
    achievementsLayout->addWidget(highscoreAchievementInformation, 1, 0);
    achievementsLayout->addWidget(moneyAchievementInformation, 1, 1);
    achievementsLayout->addWidget(playedGamesAchievementInformation, 1, 2);

    this->addUsersHighscoreAchievementsToScreen();
    this->addUsersMoneyAchievementsToScreen();
    this->addUsersPlayedGamesAchievementToScreen();

    //alter dialog
    setWindowTitle(tr("Achievements - ") + currentUsername);
    setLayout(achievementsLayout);
}

void AchievementsDialog::addUsersHighscoreAchievementsToScreen()
{
    std::vector<std::string> highscoreAchievements{"Fast racer"  , "Speedful mind", "Supermario", "The very best"};
    std::vector<double> highscoreAchievementsValues{70.0, 50.0, 30.0, 20.0}; // tbd add values that have to be reached to get the achievement
    int vectorSize = highscoreAchievementsValues.size();
    QString listOfHighscoreAchievements;

    for (int i = 0; i < vectorSize ; i++) {
        if (userprofile->getHighscore(publicCurrentUsername) >= highscoreAchievementsValues[i]) {
            listOfHighscoreAchievements = listOfHighscoreAchievements + "\n" + QString::fromStdString(highscoreAchievements[i]);
        }
    }
    QLabel * achievement = new QLabel(listOfHighscoreAchievements);
    achievementsLayout->addWidget(achievement, 2, 0);
}

void AchievementsDialog::addUsersMoneyAchievementsToScreen()
{
    std::vector<std::string> moneyAchievements{"Piggybank" , "Bankbook" , "Investor", "Millionaire"};
    std::vector<double> moneyAchievementsValues{500, 1000, 1500, 2000};
    int vectorSize = moneyAchievementsValues.size();
    QString listOfMoneyAchievements;

    for (int i = 0; i < vectorSize ; i++) {
        if (userprofile->getMaximumSavedMoney(publicCurrentUsername) >= moneyAchievementsValues[i]) {
            listOfMoneyAchievements = listOfMoneyAchievements + "\n" + QString::fromStdString(moneyAchievements[i]);
        }
    }
    QLabel * achievement = new QLabel(listOfMoneyAchievements);
    achievementsLayout->addWidget(achievement, 2, 1);
}

void AchievementsDialog::addUsersPlayedGamesAchievementToScreen()
{
    std::vector<std::string> playedGamesAchievements{"Skilled Racer" , "Advanced Racer" , "Expert Racer", "Master Racer"};
    std::vector<double> playedGamesAcievementsValues{10, 50, 200, 500};
    int vectorSize = playedGamesAcievementsValues.size();
    QString listOfPlayedGamesAchievements;

    for (int i = 0; i < vectorSize ; i++) {
        if (userprofile->getPlayedGames(publicCurrentUsername) >= playedGamesAcievementsValues[i]) {
            listOfPlayedGamesAchievements = listOfPlayedGamesAchievements + "\n" + QString::fromStdString(playedGamesAchievements[i]);
        }
    }
    QLabel * achievement = new QLabel(listOfPlayedGamesAchievements);
    achievementsLayout->addWidget(achievement, 2, 2);
}
