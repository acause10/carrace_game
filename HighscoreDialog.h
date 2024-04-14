#ifndef HIGHSCOREDIALOG_H
#define HIGHSCOREDIALOG_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <UserProfile.h>

///
/// \brief The HighscoreDialog class
///
/// creates a QDialog that list all users ordered by ascending highscore
class HighscoreDialog:  public QWidget
{
     Q_OBJECT

public:
    ///
    /// \brief HighscoreDialog constructor
    /// \param parent
    ///
    /// if an object of the class is created all users from database get selected in ascending highscore order from database
    HighscoreDialog(QWidget * parent = 0);

private:
    ///
    /// \brief highscoreLayout
    ///
    /// should not be removed until the HighscoreDialog window gets closed
    QGridLayout * highscoreLayout;
    ///
    /// \brief userprofile gives intersection from the application to the database
    ///
    /// should not be removed until the HighscoreDialog window gets closed
    UserProfile * userprofile;

    void addUsersHighscoresToScreen();
};

#endif // HIGHSCOREDIALOG_H
