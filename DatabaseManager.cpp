#include <DatabaseManager.h>

DatabaseManager::DatabaseManager(): QSqlDatabase()
{ }

//Function to create database when first opening the application and connect to it otherwise
void DatabaseManager::initializeDatabaseManager()
{
    //create database
    databaseGame = QSqlDatabase::addDatabase("QSQLITE");
    databaseGame.setDatabaseName("database.db");

    //connect to database
    if(!databaseGame.open()){
        qWarning() << "ERROR 1: " << databaseGame.lastError();
    }
    else{
        qDebug() << "Database connection ok";
    }

    //create table "user"  to store informations(id, username, highscore, money, level, maximumSpeed, acceleration, controllerLevel, playedGames, maximumSavedMoney) about users
    QSqlQuery query("CREATE TABLE IF NOT EXISTS user(id INTEGER PRIMARY KEY, "
                    "username TEXT, "
                    "highscore DOUBLE, "
                    "money INTEGER, "
                    "level INTEGER, "
                    "maximumSpeed DOUBLE, "
                    "maximumAcceleration DOUBLE, "
                    "control DOUBLE,"
                    "playedGames INTEGER,"
                    "maximumSavedMoney INTEGER,"
                    "highscoreAchievementNumber INTEGER,"
                    "moneyAchievementNumber INTEGER,"
                    "playedGamesAchievementNumber INTEGER)");
    if(!query.isActive()){
        qWarning() << "ERROR 2: " << query.lastError().text();
    }
}

//Function to add new user to database
void DatabaseManager::addUser(QString username)
{
    QSqlQuery queryTest;
    queryTest.prepare("INSERT INTO user (username, highscore, money, level, maximumSpeed, maximumAcceleration, control, playedGames,"
                      " maximumSavedMoney, highscoreAchievementNumber, moneyAchievementNumber, playedGamesAchievementNumber)"
                      "VALUES (:username, 0.0, 0, 0, 0.25, 0.0005, 0.1, 0, 0, 0, 0, 0)");
    queryTest.bindValue(":username", username);

    if(!queryTest.exec())
    {
        qWarning() << "ERROR 3: " << queryTest.lastError().text();
    }

    std::vector<std::string> testArray = this->returnAllUsernames();
    qDebug() << "user added to database ";
}

//Function that tests if user with username already exists
bool DatabaseManager::checkIfUserExists(QString username)
{
    bool userExists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT username FROM user WHERE username = (:username)");
    checkQuery.bindValue(":username", username);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            userExists = true;
        }
    }
    else
    {
        qDebug() << "person exists failed: " << checkQuery.lastError();
    }

    return userExists;
}

// selectUser should return a UserProfile oject with all data prefilled from the database
UserProfile * DatabaseManager::selectUser(QString username)
{
   if(checkIfUserExists(username))
   {
       QSqlQuery query;
       query.prepare("SELECT * FROM user WHERE username = (:username)");
       query.bindValue(":username" , username);

       if(!query.exec())
       {
           qDebug() << "select person failed: " << query.lastError();
       }

       while(query.next()) {
           QString usernameInDatabase = query.value(query.record().indexOf("username")).toString();
           double highscoreInDatabase = query.value(query.record().indexOf("highscore")).toDouble();
           int moneyInDatabase = query.value(query.record().indexOf("money")).toInt();
           int levelInDatabase = query.value(query.record().indexOf("level")).toInt();
           double maximumSpeedInDatabase = query.value(query.record().indexOf("maxmimumSpeed")).toDouble();
           double maximumAccelerationInDatabase = query.value(query.record().indexOf("maxmimumAcceleration")).toDouble();
           double controlInDatabase = query.value(query.record().indexOf("control")).toDouble();
           int playedGamesInDatabase = query.value(query.record().indexOf("playedGames")).toInt();
           int maximumSavedMoney = query.value(query.record().indexOf("maximumSavedMoney")).toInt();
           int highscoreAchievementNumber = query.value(query.record().indexOf("highscoreAchievementNumber")).toInt();
           int moneyAchievementNumber = query.value(query.record().indexOf("moneyAchievementNumber")).toInt();
           int playedGamesAchievementNumber = query.value(query.record().indexOf("playedGamesAchievementNumber")).toInt();

           UserProfile * userProfile = new UserProfile(usernameInDatabase, highscoreInDatabase, moneyInDatabase, levelInDatabase,
                                                       maximumSpeedInDatabase, maximumAccelerationInDatabase, controlInDatabase, playedGamesInDatabase, maximumSavedMoney,
                                                       highscoreAchievementNumber, moneyAchievementNumber, playedGamesAchievementNumber);
           return userProfile;
       }
   }
   return 0;
}

//Function returns the highscore of a user from database
double DatabaseManager::getHighscoreUserFromDatabase(QString username)
{
    QSqlQuery query;
    query.prepare("SELECT highscore FROM user WHERE username = (:username)");
    query.bindValue(":username" , username);

    if(!query.exec())
    {
        qDebug() << "get highscore from database failed: " << query.lastError();
    }

    while(query.next()) {
        double highscoreInDatabase = query.value(query.record().indexOf("highscore")).toDouble();
        return highscoreInDatabase;
    }
    return 0.0;
}

//Function allows to update the highscore of user in database
void DatabaseManager::increaseHighscoreUserInDatabase(QString username, double newHighscore)
{
    QSqlQuery query;
    query.prepare("UPDATE user SET highscore = (:newHighscore) WHERE username = (:username)");
    query.bindValue(":newHighscore", newHighscore);
    query.bindValue(":username", username);
    query.exec();
}

//Function returns the money of a user from database
int DatabaseManager::getMoneyUserFromDatabase(QString username)
{
    QSqlQuery query;
    query.prepare("SELECT money FROM user WHERE username = (:username)");
    query.bindValue(":username" , username);

    if(!query.exec())
    {
        qDebug() << "get money from database failed: " << query.lastError();
    }

    while(query.next()) {
        int moneyInDatabase = query.value(query.record().indexOf("money")).toInt();
        return moneyInDatabase;
    }
    return 0;
}

//Function allows to update the money of user in database
void DatabaseManager::updateMoneyUserInDatabase(QString username, int collectedCoins)
{
    int newMoneyUser = this->getMoneyUserFromDatabase(username) + collectedCoins;

    QSqlQuery query;
    query.prepare("UPDATE user SET money = (:newMoneyUser) WHERE username = (:username)");
    query.bindValue(":newMoneyUser", newMoneyUser);
    query.bindValue(":username", username);
    query.exec();
}

//Function returns the level of a user from database
int DatabaseManager::getLevelUserFromDatabase(QString username)
{
    QSqlQuery query;
    query.prepare("SELECT level FROM user WHERE username = (:username)");
    query.bindValue(":username" , username);

    if(!query.exec())
    {
        qDebug() << "get level from database failed: " << query.lastError();
    }

    while(query.next()) {
        int levelInDatabase = query.value(query.record().indexOf("level")).toInt();
        return levelInDatabase;
    }
    return 0;
}

//Function allows to update the level of user in database
void DatabaseManager::increaseLevelUserInDatabase(QString username)
{
    int newLevelUser = this->getLevelUserFromDatabase(username) + 1;

    QSqlQuery query;
    query.prepare("UPDATE user SET level = (:newLevelUser) WHERE username = (:username)");
    query.bindValue(":newLevelUser", newLevelUser);
    query.bindValue(":username", username);
    query.exec();
}

//Function allows to update the maximum speed of user in database
void DatabaseManager::upgradeMaximumSpeedInDatabase(QString username, double newMaximumSpeed)
{
    QSqlQuery query;
    query.prepare("UPDATE user SET maximumSpeed = (:newMaximumSpeed) WHERE username = (:username)");
    query.bindValue(":newMaximumSpeed", newMaximumSpeed);
    query.bindValue(":username", username);
    query.exec();
}

//Function returns maximum speed of user from database
double DatabaseManager::getMaximumSpeedFromDatabase(QString username)
{
    QSqlQuery query;
    query.prepare("SELECT maximumSpeed FROM user WHERE username = (:username)");
    query.bindValue(":username" , username);

    if(!query.exec())
    {
        qDebug() << "get money from database failed: " << query.lastError();
    }

    while(query.next()) {
        double maximumSpeedInDatabase = query.value(query.record().indexOf("maximumSpeed")).toDouble();
        return maximumSpeedInDatabase;
    }
    return 0.3;
}

//Function allows to update the maximum acceleration of user in database
void DatabaseManager::upgradeMaximumAccelerationInDatabase(QString username, double newMaximumAcceleration)
{
    QSqlQuery query;
    query.prepare("UPDATE user SET maximumAcceleration = (:newMaximumAcceleration) WHERE username = (:username)");
    query.bindValue(":newMaximumAcceleration", newMaximumAcceleration);
    query.bindValue(":username", username);
    query.exec();
}

//Function returns the maximum acceleration of user from database
double DatabaseManager::getMaxmimumAccelerationFromDatabase(QString username)
{
    QSqlQuery query;
    query.prepare("SELECT maximumAcceleration FROM user WHERE username = (:username)");
    query.bindValue(":username" , username);

    if(!query.exec())
    {
        qDebug() << "get money from database failed: " << query.lastError();
    }

    while(query.next()) {
        double maximumAccelerationInDatabase = query.value(query.record().indexOf("maximumAcceleration")).toDouble();
        return maximumAccelerationInDatabase;
    }
    return 0.006;
}

//Function allows to update the control of user in database
void DatabaseManager::upgradeControlInDatabase(QString username, double newControl)
{
    QSqlQuery query;
    query.prepare("UPDATE user SET control = (:newControl) WHERE username = (:username)");
    query.bindValue(":newControl", newControl);
    query.bindValue(":username", username);
    query.exec();
}

//Function returns control of user from database
double DatabaseManager::getControlFromDatabase(QString username)
{
    QSqlQuery query;
    query.prepare("SELECT control FROM user WHERE username = (:username)");
    query.bindValue(":username" , username);

    if(!query.exec())
    {
        qDebug() << "get money from database failed: " << query.lastError();
    }

    while(query.next()) {
        double controlInDatabase = query.value(query.record().indexOf("control")).toDouble();
        return controlInDatabase;
    }
    return 0.1;
}

//Function returns vector with all existing usernames in database
std::vector<std::string> DatabaseManager::returnAllUsernames()
{
    QSqlQuery query("SELECT * FROM user");
    int idName = query.record().indexOf("username");

    std::vector<std::string> registeredUsers{};

    while (query.next())
    {
       QString qStringName = query.value(idName).toString();
       std::string stdName = qStringName.toStdString();
       registeredUsers.push_back(stdName);
    }
    return registeredUsers;
}


//Function returns vector with all existing usernames and highscores order ascending by highscore
std::vector<std::string> DatabaseManager::returnAllUsernamesSortedByHighscore()
{
    QSqlQuery query("SELECT username, highscore FROM user ORDER BY highscore ASC");
    int idName = query.record().indexOf("username");
    int idHighscore = query.record().indexOf("highscore");

    std::vector<std::string> registeredUsersSortedByHighscore{};

    while (query.next()) {
        double highscoreUser = query.value(idHighscore).toDouble();
        if(highscoreUser != 0.0)
        {
            QString qStringName = query.value(idName).toString();
            std::string stdName = qStringName.toStdString();
            std::string result = stdName + ": " + std::to_string(highscoreUser) + " seconds";

            registeredUsersSortedByHighscore.push_back(result);
        }
    }
    return registeredUsersSortedByHighscore;
}

//Function allows to update the playedGames of user in database
void DatabaseManager::increasePlayedGamesUserInDatabase(QString username)
{
    int updatedNumberPlayedGames = this->getPlayedGamesUserFromDatabase(username) + 1;

    QSqlQuery query;
    query.prepare("UPDATE user SET playedGames = (:updatedNumberPlayedGames) WHERE username = (:username)");
    query.bindValue(":updatedNumberPlayedGames", updatedNumberPlayedGames);
    query.bindValue(":username", username);
    query.exec();
}

//Function returns playedGames of user from database
int DatabaseManager::getPlayedGamesUserFromDatabase(QString username)
{
    QSqlQuery query;
    query.prepare("SELECT playedGames FROM user WHERE username = (:username)");
    query.bindValue(":username" , username);

    if(!query.exec())
    {
        qDebug() << "get playedGames from database failed: " << query.lastError();
    }

    while(query.next()) {
        int playedGamesInDatabase = query.value(query.record().indexOf("playedGames")).toInt();
        return playedGamesInDatabase;
    }
    return 0;
}

//Function allows to update the maximumSavedMoney of user in database
void DatabaseManager::updateMaximumSavedMoneyInDatabase(QString username, int potentialNewMaximumSavedMoney)
{
    QSqlQuery query;
    query.prepare("UPDATE user SET maximumSavedMoney = (:potentialNewMaximumSavedMoney) WHERE username = (:username)");
    query.bindValue(":potentialNewMaximumSavedMoney", potentialNewMaximumSavedMoney);
    query.bindValue(":username", username);
    query.exec();
}

//Function returns playedGames of user from database
int DatabaseManager::getMaximumSavedMoneyFromDatabase(QString username)
{
    QSqlQuery query;
    query.prepare("SELECT maximumSavedMoney FROM user WHERE username = (:username)");
    query.bindValue(":username" , username);

    if(!query.exec())
    {
        qDebug() << "get maximumSavedMoney from database failed: " << query.lastError();
    }

    while(query.next()) {
        int maximumSavedMoneyInDatabase = query.value(query.record().indexOf("maximumSavedMoney")).toInt();
        return maximumSavedMoneyInDatabase;
    }
    return 0;
}

//Function allows to update the highscoreAchievementNumber of user in database
void DatabaseManager::updateHighscoreAchievementNumber(QString username)
{
    int newHighscoreAchievementNumber = this->getHighscoreAchievementNumber(username) + 1;

    QSqlQuery query;
    query.prepare("UPDATE user SET highscoreAchievementNumber = (:newHighscoreAchievementNumber) WHERE username = (:username)");
    query.bindValue(":newHighscoreAchievementNumber", newHighscoreAchievementNumber);
    query.bindValue(":username", username);
    query.exec();
}

//Function returns the highscoreAchievementNumber of a user from database
int DatabaseManager::getHighscoreAchievementNumber(QString username)
{
    QSqlQuery query;
    query.prepare("SELECT highscoreAchievementNumber FROM user WHERE username = (:username)");
    query.bindValue(":username" , username);

    if(!query.exec())
    {
        qDebug() << "get highscoreAchievementNumber from database failed: " << query.lastError();
    }

    while(query.next()) {
        int highscoreAchievementNumberInDatabase = query.value(query.record().indexOf("highscoreAchievementNumber")).toInt();
        return highscoreAchievementNumberInDatabase;
    }
    return 0;
}

//Function allows to update the moneyAchievementNumber of user in database
void DatabaseManager::updateMoneyAchievementNumber(QString username)
{
    int newMoneyAchievementNumber = this->getMoneyAchievementNumber(username) + 1;

    QSqlQuery query;
    query.prepare("UPDATE user SET moneyAchievementNumber = (:newMoneyAchievementNumber) WHERE username = (:username)");
    query.bindValue(":newMoneyAchievementNumber", newMoneyAchievementNumber);
    query.bindValue(":username", username);
    query.exec();
}

//Function returns the moneyAchievementNumber of a user from database
int DatabaseManager::getMoneyAchievementNumber(QString username)
{
    QSqlQuery query;
    query.prepare("SELECT moneyAchievementNumber FROM user WHERE username = (:username)");
    query.bindValue(":username" , username);

    if(!query.exec())
    {
        qDebug() << "get moneyAchievementNumber from database failed: " << query.lastError();
    }

    while(query.next()) {
        int moneyAchievementNumberInDatabase = query.value(query.record().indexOf("moneyAchievementNumber")).toInt();
        return moneyAchievementNumberInDatabase;
    }
    return 0;
}

//Function allows to update the playedGamesAchievementNumber of user in database
void DatabaseManager::updatePlayedGamesAchievementNumber(QString username)
{
    int newPlayedGamesAchievementNumber = this->getPlayedGamesAchievementNumber(username) + 1;

    QSqlQuery query;
    query.prepare("UPDATE user SET playedGamesAchievementNumber = (:newPlayedGamesAchievementNumber) WHERE username = (:username)");
    query.bindValue(":newPlayedGamesAchievementNumber", newPlayedGamesAchievementNumber);
    query.bindValue(":username", username);
    query.exec();
}

//Function returns the playedGamesAchievementNumber of a user from database
int DatabaseManager::getPlayedGamesAchievementNumber(QString username)
{
    QSqlQuery query;
    query.prepare("SELECT playedGamesAchievementNumber FROM user WHERE username = (:username)");
    query.bindValue(":username" , username);

    if(!query.exec())
    {
        qDebug() << "get playedGamesAchievementNumber from database failed: " << query.lastError();
    }

    while(query.next()) {
        int playedGamesAchievementNumberInDatabase = query.value(query.record().indexOf("playedGamesAchievementNumber")).toInt();
        return playedGamesAchievementNumberInDatabase;
    }
    return 0;
}
