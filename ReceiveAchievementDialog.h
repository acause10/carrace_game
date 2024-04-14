#ifndef RECEIVEACHIEVEMENTDIALOG_H
#define RECEIVEACHIEVEMENTDIALOG_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

///
/// \brief The ReceiveAchievementDialog class
///
/// creates a QDialog that opens, when user receives a new achievement
class ReceiveAchievementDialog: public QWidget
{
    Q_OBJECT

public:

    ///
    /// \brief ReceiveAchievementDialog constrcutor
    /// \param parent
    /// \param currentUsername the current active users name
    ///
    ReceiveAchievementDialog(QWidget *parent = 0, QString currentUsername = "", QString congratText = "");

    ///
    /// \brief publicCurrentUsername the variable to use the currentUsername in every function of the class (it is equal to currentUsername)
    ///
    QString publicCurrentUsername;

private:
    ///
    /// \brief gridLayoutReceiveAchievementDialog
    ///
    /// should not be removed before the Dialog gets closed
    QGridLayout *gridLayoutReceiveAchievementDialog;
};

#endif // RECEIVEACHIEVEMENTDIALOG_H
