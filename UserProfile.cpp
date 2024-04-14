#include "UserProfile.h"
#include "DatabaseManager.h"

UserProfile::UserProfile(){ }

UserProfile::UserProfile(QString enteredName, double highscoreUser, int moneyUser, int levelUser, double maximumSpeedUser, double maximumAccelerationUser, double controlUser, int playedGames, int maximumSavedMoney,
                         int highscoreAchievementNumber, int moneyAchievementNumber, int playedGamesAchievementNumber)
    :username(enteredName), highscoreUser(highscoreUser), moneyUser(moneyUser), levelUser(levelUser), maximumSpeedUser(maximumSpeedUser), maximumAccelerationUser(maximumAccelerationUser), controlUser(controlUser),
      playedGames(playedGames), maximumSavedMoney(maximumSavedMoney), highscoreAchievementNumber(highscoreAchievementNumber), moneyAchievementNumber(moneyAchievementNumber), playedGamesAchievementNumber(playedGamesAchievementNumber)
{
    //create databaseManager to acces the database from the game
    databaseManager = new DatabaseManager;
    databaseManager->initializeDatabaseManager();
}

//Function returns the current selected user
UserProfile * UserProfile::getCurrentUser()
{
    UserProfile * currentUser = new UserProfile;
    currentUser = databaseManager->selectUser(currentUsername);
    return currentUser;
}

//Function returns if username already exists and creates new Account if not
bool UserProfile::addNewUser(QString username)
{
    if(databaseManager->checkIfUserExists(username))
    {
        QString error = "Username already exists, please choose another name!";
        return false;
    } else {
        databaseManager->addUser(username);
        return true;
    }
    currentUsername = username;
    return 0;
}

//Function returns the Name of object user
QString UserProfile::getNameUser()
{
    return currentUsername;
}

//Function returns the highscore of user based on the username
double UserProfile::getHighscore(QString username)
{
    highscoreUser = databaseManager->getHighscoreUserFromDatabase(username);
    return highscoreUser;
}

//Function gives acces to update the highscore of user in database
void UserProfile::updateHighscore(QString username, double potentialNewHighscore)
{
    qDebug() << "entered update highscore in userprofile";
    if(potentialNewHighscore < databaseManager->getHighscoreUserFromDatabase(username) || databaseManager->getHighscoreUserFromDatabase(username) == 0.0)
    {
        databaseManager->increaseHighscoreUserInDatabase(username, potentialNewHighscore);
    }
}

//Function returns the money of user based on the username
int UserProfile::getMoneyUser(QString username)
{
    moneyUser = databaseManager->getMoneyUserFromDatabase(username);
    return moneyUser;
}

//Function gives acces to update the money of user in database
void UserProfile::updateMoneyUser(QString username, int collectedCoins)
{
    databaseManager->updateMoneyUserInDatabase(username, collectedCoins);
    this->updateMaximumSavedMoney(username, databaseManager->getMoneyUserFromDatabase(username));
}

//Function returns the level of user based on the username
int UserProfile::getLevelUser(QString username)
{
    levelUser = databaseManager->getLevelUserFromDatabase(username);
    return levelUser;
}

//Function gives acces to update the level of user in database
void UserProfile::updateLevelUser(QString username)
{
    databaseManager->increaseLevelUserInDatabase(username);
}

//Function returns the maxSpeed of user from database
double UserProfile::getMaximumSpeedUser(QString username)
{
   maximumSpeedUser = databaseManager->getMaximumSpeedFromDatabase(username);
   return maximumSpeedUser;
}

//Function allows to update the maxSpeed of user in database if conditions are fulfilled
void UserProfile::updateMaximumSpeed(QString username)
{
    std::vector<double> upgradeMaximumSpeed{0.25, 0.275, 0.3, 0.325, 0.35}; //Array to add values for maxSpeed upgrade
    double newMaximumSpeed;
    bool isUpgradePossible = true;

    if(this->getMoneyUser(username) >= 50)
    {
        for (uint i = 0; upgradeMaximumSpeed[i] <= this->getMaximumSpeedUser(username) ; i++) {
            if (i < upgradeMaximumSpeed.size() -1) {
                newMaximumSpeed = upgradeMaximumSpeed[i + 1];
            } else if (i >= upgradeMaximumSpeed.size()-1) {
                isUpgradePossible = false;
            }
        }
        if(isUpgradePossible == true){
            this->updateMoneyUser(username, - 50);
            databaseManager->upgradeMaximumSpeedInDatabase(username, newMaximumSpeed);
        }
    }
}

//Function returns the maxAcceleration of user from database
double UserProfile::getMaximumAccelerationUser(QString username)
{
    maximumAccelerationUser = databaseManager->getMaxmimumAccelerationFromDatabase(username);
    return maximumAccelerationUser;
}

//Function allows to update the maxAcceleration of user in database if conditions are fulfilled
void UserProfile::updateMaximumAcceleration(QString username)
{
    std::vector<double> upgradeMaximumAcceleration{0.0005, 0.0006, 0.0007, 0.0008, 0.0009}; //Array to add values for maxSpeed upgrade
    double newMaximumAcceleration;
    int currentMoney = this->getMoneyUser(username);
    bool isUpgradePossible = true;

    if(currentMoney >= 50)
    {
        for (uint i = 0; upgradeMaximumAcceleration[i] <= this->getMaximumAccelerationUser(username) ; i++) {
            if (i < upgradeMaximumAcceleration.size() -1) {
                newMaximumAcceleration = upgradeMaximumAcceleration[i + 1];
            } else if (i >= upgradeMaximumAcceleration.size() -1){
                isUpgradePossible = false;
            }
        }
        if(isUpgradePossible == true){
            this->updateMoneyUser(username, - 50);
            databaseManager->upgradeMaximumAccelerationInDatabase(username, newMaximumAcceleration);
        }
    }
}

//Function returns the Control of user from database
double UserProfile::getControlUser(QString username)
{
    controlUser = databaseManager->getControlFromDatabase(username);
    return controlUser;
}

//Function allows to update the control of user in database if conditions are fulfilled
void UserProfile::updateControl(QString username)
{
    std::vector<double> upgradeControl{0.1, 0.15, 0.2, 0.25, 0.3}; //Array to add values for Control upgrade
    double newControl;
    int currentMoney = this->getMoneyUser(username);
    bool isUpgradePossible = true;

    if(currentMoney >= 50)
    {
        for (uint i = 0; upgradeControl[i] <= this->getControlUser(username) ; i++) {
            if (i < upgradeControl.size() -1) {
                newControl = upgradeControl[i + 1];
            }
            else if (i >= upgradeControl.size() -1){
                isUpgradePossible = false;
            }
        }
        if (isUpgradePossible == true) {
            this->updateMoneyUser(username, - 50);
            databaseManager->upgradeControlInDatabase(username, newControl);
        }
    }
}

//Function returns a vector af all usernames from database
std::vector<std::string> UserProfile::returnAllUsernames()
{
    std::vector<std::string> allUsernames = databaseManager->returnAllUsernames();

    return allUsernames;
}

std::vector<std::string> UserProfile::returnAllUsernamesSortedByHighscore()
{
    std::vector<std::string> allUsersSortedByHighscore = databaseManager->returnAllUsernamesSortedByHighscore();

    return allUsersSortedByHighscore;
}

//Function gives acces to update the playedGames of user in database
void UserProfile::increasePlayedGames(QString username)
{
    databaseManager->increasePlayedGamesUserInDatabase(username);
}

//Function returns the playedGames of user from database
int UserProfile::getPlayedGames(QString username)
{
    int playedGames = databaseManager->getPlayedGamesUserFromDatabase(username);

    return playedGames;
}


//Function gives acces to update the maximumSavedMoney of user in database
void UserProfile::updateMaximumSavedMoney(QString username, int potentialNewMaximumSavedMoney)
{
    if(potentialNewMaximumSavedMoney > databaseManager->getMaximumSavedMoneyFromDatabase(username))
    {
        databaseManager->updateMaximumSavedMoneyInDatabase(username, potentialNewMaximumSavedMoney);
    }
}

//Function returns the maximumSavedMoney of user from database
int UserProfile::getMaximumSavedMoney(QString username)
{
    maximumSavedMoney = databaseManager->getMaximumSavedMoneyFromDatabase(username);

    return maximumSavedMoney;
}

//Function gives acces to update the highscoreAchievementNumber of user in database
void UserProfile::updateHighscoreAchievementNumber(QString username)
{
    databaseManager->updateHighscoreAchievementNumber(username);
}

//Function returns the highscoreAchievementNumber of user based on the username
int UserProfile::getHighscoreAchievementNumber(QString username)
{
    highscoreAchievementNumber = databaseManager->getHighscoreAchievementNumber(username);
    return highscoreAchievementNumber;
}

//Function gives acces to update the moneyAchievementNumber of user in database
void UserProfile::updateMoneyAchievementNumber(QString username)
{
    databaseManager->updateMoneyAchievementNumber(username);
}

//Function returns the moneyAchievementNumber of user based on the username
int UserProfile::getMoneyAchievementNumber(QString username)
{
    moneyAchievementNumber = databaseManager->getMoneyAchievementNumber(username);
    return moneyAchievementNumber;
}

//Function gives acces to update the playedGamesAchievementNumber of user in database
void UserProfile::updatePlayedGamesAchievementNumber(QString username)
{
    databaseManager->updatePlayedGamesAchievementNumber(username);
}

//Function returns the playedGamesAchievementNumber of user based on the username
int UserProfile::getPlayedGamesAchievementNumber(QString username)
{
    playedGamesAchievementNumber = databaseManager->getPlayedGamesAchievementNumber(username);
    return playedGamesAchievementNumber;
}
