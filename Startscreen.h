#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QGridLayout>
#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <DatabaseManager.h>

///
/// \brief The Startscreen class
///
/// creates a dialog, when user opens the application \n
/// after closing this dialog th mainwindow gets showed \n
/// in dialog the user is able to choose an existing account from the database or create a new one
class Startscreen: public QDialog
{
    Q_OBJECT

public:
    ///
    /// \brief Startscreen constructor
    /// \param parent
    ///
    Startscreen(QDialog *parent = nullptr);

    ///
    /// \brief getNameUser gets the text entered in inputField "nameField"
    /// \return a QString with the username entered in nameField
    ///
    QString getNameUser();

    ///
    /// \brief createAccountClicked closes the Startscreen
    /// \return a Qstring with the username entered in nameField
    ///
    QString createAccountClicked();

    ///
    /// \brief changeWelcomeText changes the text of QLabel welcomeText
    /// \param newText the new Qstring for QLabel welcomeText
    ///
    void changeWelcomeText(QString newText);

    ///
    /// \brief enterGame closes the Startscreen
    /// \return a QString with the username choosen from combobox existingUserprofiles
    ///
    QString enterGame();

private:
    ///
    /// \brief startGridLayout
    ///
    /// should not be removed before the Startscreen dialog gets closed
    QGridLayout * startGridLayout;

    ///
    /// \brief welcomeText the (explaining) text of the Startscreen
    ///
    /// should not be removed before the Startscreen dialog gets closed
    QLabel * welcomeText;

    ///
    /// \brief nameField the field in which you can type a new text (username)
    ///
    /// should not be removed before the Startscreen dialog gets closed
    QLineEdit * nameField;

    ///
    /// \brief enterGameButton when clicked the startscreen window gets closed and the mainwindow gets opened
    ///
    /// is connected with enterGame()
    /// should not be removed before the Startscreen dialog gets closed
    QPushButton * enterGameButton;

    ///
    /// \brief createAccountButton when clicked closes the startscreen window and opens the mainwindow
    ///
    /// is connected with createAccountClicked()
    /// should not be removed before the Startscreen dialog gets closed
    QPushButton  * createAccountButton;

    ///
    /// \brief existingUserprofiles a QCombobox that lists all the existing Userprofiles from database
    ///
    /// should not be removed before the Startscreen dialog gets closed
    QComboBox * existingUserprofiles;

    void addUsersToCombobox();
    QString newNameUser;
};

#endif // STARTSCREEN_H
