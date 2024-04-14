#ifndef ACHIEVEMENTSDIALOG_H
#define ACHIEVEMENTSDIALOG_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <UserProfile.h>

///
/// \brief The AchievementsDialog class
///
/// creates a QDialog that shows all the achievements the current active user has already made
class AchievementsDialog:  public QWidget
{
     Q_OBJECT

public:

    ///
    /// \brief AchievementsDialog constructor
    /// \param parent
    /// \param currentUsername the current active users name
    ///
    AchievementsDialog(QWidget * parent = 0, QString currentUsername = "");

    ///
    /// \brief publicCurrentUsername the variable to use the currentUsername in every function of the class (it is equal to currentUsername)
    ///
    QString publicCurrentUsername;

    ///
    /// \brief maximumSavedMoney the variable stores always the highest reached integer money value, that user had
    ///
    int maximumSavedMoney;

private:
    ///
    /// \brief achievementsLayout
    ///
    /// should not be removed until the AchievementsDialog window gets closed
    QGridLayout * achievementsLayout;

    ///
    /// \brief userprofile gives intersection from the application to the database
    ///
    /// should not be removed until the AchievementsDialog window gets closed
    UserProfile * userprofile;
    void addUsersHighscoreAchievementsToScreen();
    void addUsersMoneyAchievementsToScreen();
    void addUsersPlayedGamesAchievementToScreen();
};
#endif // ACHIEVEMENTSDIALOG_H
