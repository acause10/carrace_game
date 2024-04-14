#include <Startscreen.h>
#include <QDebug>

Startscreen::Startscreen(QDialog *parent): QDialog(parent)
{
    //create Gridlayout for Startmenu
    startGridLayout = new QGridLayout();

    //create Text for Startscreen
    welcomeText = new QLabel();
    welcomeText->setText(tr("Welcome in our Racing game :)"));
    startGridLayout->addWidget(welcomeText, 0, 0);

    //create Text - InputField - Button for creating new Userprofile
    QLabel * createUserprofileText = new QLabel(tr("Enter your name to create new Account: "));
    startGridLayout->addWidget(createUserprofileText, 1, 0);

    nameField = new QLineEdit();
    startGridLayout->addWidget(nameField, 1, 1);

    createAccountButton = new QPushButton(tr("create account"));
    connect(createAccountButton, &QPushButton::clicked, this, &Startscreen::createAccountClicked);
    startGridLayout->addWidget(createAccountButton, 1, 2);


    //create Text - ComoboBox to choose existing Account/Userprofile
    QLabel * chooseExistingAccountText = new QLabel(tr("Choose existing Account: "));
    startGridLayout->addWidget(chooseExistingAccountText, 2, 0);

    existingUserprofiles = new QComboBox();
    startGridLayout->addWidget(existingUserprofiles, 2, 1, 1, 2);
    this->addUsersToCombobox();

    existingUserprofiles->setAccessibleDescription("choose existing Account");

    //create Button to enter Game
    enterGameButton = new QPushButton(tr("enter Game"));
    connect(enterGameButton, &QPushButton::clicked, this, &Startscreen::enterGame);
    startGridLayout->addWidget(enterGameButton, 3, 0, 1, 3);

    //disable close Button
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint| Qt::WindowMaximizeButtonHint);

    //alter Window
    setLayout(startGridLayout);
}

//Function closes StartscreenDialog and allows mainwindow to get focused and returns the choosen username from combobox
QString Startscreen::enterGame()
{
    QString currentUser = existingUserprofiles->currentText();
    this->close();
    return currentUser;
}

//Function returns the entered text in inputField
QString Startscreen::getNameUser()
{
    newNameUser = nameField->text();
    return newNameUser;
}

//Function closes StartscreenDialog and allows mainwindow to get focused and returns the entered username from inputField
QString Startscreen::createAccountClicked()
{
    QString username = this->getNameUser();
    this->close();

    return username;
}

//Function allows to change the showed text on startscreen
void Startscreen::changeWelcomeText(QString newText)
{
    welcomeText->setText(newText);
}

//Function adds all usernames from database to combobox on startscreen
void Startscreen::addUsersToCombobox()
{
    DatabaseManager * databaseManager = new DatabaseManager();
    databaseManager->initializeDatabaseManager();
    std::vector<std::string> allUsernames = databaseManager->returnAllUsernames();
    int sizeOfAllUsernamesArray = allUsernames.size();

    for (int i=0;i < sizeOfAllUsernamesArray ;i++ ) {
      std::string name = allUsernames[i];
      QString usernameForCombobox = QString::fromStdString(name);
      existingUserprofiles->addItem(usernameForCombobox);
    }
}
