#include <ReceiveAchievementDialog.h>
#include <QDebug>

ReceiveAchievementDialog::ReceiveAchievementDialog(QWidget *parent,QString currentUsername, QString congratText)
    : QWidget(parent)
{
    publicCurrentUsername = currentUsername;

    //set Layout for ExitGameDialog
    gridLayoutReceiveAchievementDialog = new QGridLayout;

    //create and add QLabel Text to ExitGameDialog
    QLabel * receiveAchievementText = new QLabel(tr("Congratulations!"));
    gridLayoutReceiveAchievementDialog->addWidget(receiveAchievementText, 0, 0);
    QLabel * congratulationsText = new QLabel(congratText);
    gridLayoutReceiveAchievementDialog->addWidget(congratulationsText, 1, 0);

    //alter Dialog
    setWindowTitle(tr("Congratulations ") + currentUsername + tr(" !"));
    setLayout(gridLayoutReceiveAchievementDialog);
}
