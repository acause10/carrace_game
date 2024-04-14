#ifndef EXITGAMEDIALOG_H
#define EXITGAMEDIALOG_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

///
/// \brief The ExitGameDialog class
///
/// creates a dialog, when user clicks exitGameButton in mainwindow \n
/// dialog gives options to, restart, continue or exit the game
class ExitGameDialog: public QWidget
{
    Q_OBJECT

public:
    ///
    /// \brief ExitGameDialog constructor
    /// \param parent
    ///
    ExitGameDialog(QWidget *parent = 0);

signals:
    ///
    /// \brief exitGameButtonInDialogClicked
    ///
    /// is connected with signal that exitGameButton is clicked \n
    /// and with slot exitGame() in mainwindow \n
    /// leads to close (set invisible) the GameScene and sets visible the routeSelectionScreen
    void exitGameButtonInDialogClicked();

    ///
    /// \brief restartButtonInDialogClicked
    ///
    /// is connected with signal that restartButton is clicked \n
    /// and with slot restartGame() in mainwindow \n
    /// leads to reopen/initalize th GameScene
    void restartButtonInDialogClicked();

    ///
    /// \brief closeExitGameDialog
    ///
    /// is connected with signal that backToGameButton is clicked \n
    /// and with slot backToGame() in mainwindow \n
    /// leads to continue Game and close exitGameDialog
    void closeExitGameDialog();

private:
    ///
    /// \brief gridLayoutExitGameDialog
    ///
    /// should not be removed before exitGameDialog is closed
    QGridLayout *gridLayoutExitGameDialog;

    ///
    /// \brief backToGameButton
    ///
    /// should not be removed before exitGameDialog is closed
    QPushButton *backToGameButton;

    ///
    /// \brief exitButtonInDialog
    ///
    /// should not be removed before exitGameDialog is closed
    QPushButton *exitButtonInDialog;

    ///
    /// \brief restartButton
    ///
    /// should not be removed before exitGameDialog is closed
    QPushButton *restartButton;
};

#endif // EXITGAMEDIALOG_H
