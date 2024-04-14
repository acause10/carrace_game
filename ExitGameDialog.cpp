#include <ExitGameDialog.h>
#include <QLabel>
#include <mainwindow.h>

ExitGameDialog::ExitGameDialog(QWidget *parent)
    : QWidget(parent)
{
    //set Layout for ExitGameDialog
    gridLayoutExitGameDialog = new QGridLayout;

    //create and add QLabel Text to ExitGameDialog
    QLabel * exitGameText = new QLabel(tr("Game paused..."));
    gridLayoutExitGameDialog->addWidget(exitGameText, 0, 0);

    //create and add restartButton to ExitGameDialog
    restartButton = new QPushButton(tr("Restart game"));
    connect(restartButton, SIGNAL(clicked()), this, SIGNAL(restartButtonInDialogClicked()));
    gridLayoutExitGameDialog->addWidget(restartButton, 1, 0);

    //create and add backToGameButton to ExitGameDialog
    backToGameButton = new QPushButton(tr("Back to game"));
    connect(backToGameButton, SIGNAL(clicked()), this, SIGNAL(closeExitGameDialog()));
    gridLayoutExitGameDialog->addWidget(backToGameButton, 1, 1);

    //create and add exitGameButton to ExitGameDialog
    exitButtonInDialog = new QPushButton(tr("Exit game"));
    connect(exitButtonInDialog, SIGNAL(clicked()), this, SIGNAL(exitGameButtonInDialogClicked()));
    gridLayoutExitGameDialog->addWidget(exitButtonInDialog, 1, 2);

    //alter Dialog
    setWindowTitle(tr("Exit Menu"));
    setLayout(gridLayoutExitGameDialog);
}
