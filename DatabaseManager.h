#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <UserProfile.h>
#include <QSqlRecord>

///
/// \brief The DatabaseManager class
///
/// gives functions to create, connect and interact between a sqlite database and the UserProfile class
class DatabaseManager : public QSqlDatabase
{
public:
    ///
    /// \brief DatabaseManager constructor
    ///
    DatabaseManager();

    ///
    /// \brief getHighscoreUserFromDatabase selects suitable field highscore to given username from sqlite database
    /// \param username the currently active users name
    /// \return the highscore of user with corresponding <username> from sqlite database
    ///
    /// function executes a sql command that selects the highscore field to corresponding given username from slite database
    double getHighscoreUserFromDatabase(QString username);

    ///
    /// \brief increaseHighscoreUserInDatabase updates the field highscore of corresponding field username in database with new highscore value
    /// \param username the currently active users name
    /// \param newHighscore the new double value that should be stored in database
    ///
    /// function executes a sql command that updates highscore of corresponding given username from slite database
    void increaseHighscoreUserInDatabase(QString username, double newHighscore);

    ///
    /// \brief getMoneyUserFromDatabase selects suitable field money to given username from sqlite database
    /// \param username the currently active users name
    /// \return a double with the value of money field of <user(name)> in database
    ///
    /// function executes a sql command that selects the money field to corresponding given username
    int getMoneyUserFromDatabase(QString username);

    ///
    /// \brief updateMoneyUserInDatabase  updates the field money of corresponding field username in database with new money value
    /// \param username the currently active users name
    /// \param collectedCoins the integer value of coins that should be added to the current value of money from corresponding <user> in database
    ///
    /// function selects the current money of user from database
    /// then adds the value of collected coins to current money and stores value in int newMoneyUser
    /// at least it executes a sql command that updates/overrites the field money of corresponding given username with value of newMoneyUser
    void updateMoneyUserInDatabase(QString username, int collectedCoins);

    ///
    /// \brief getLevelUserFromDatabase selects suitable field level to given username from sqlite database
    /// \param username the currently active users name
    /// \return an integer with the value of level field of <user(name)> in database
    ///
    /// function executes a sql command that selects the level field to corresponding given username from sqlite database
    int getLevelUserFromDatabase(QString username);

    ///
    /// \brief increaseLevelUserInDatabase updates the field level of corresponding field username in database with new level value
    /// \param username the currently active users name
    ///
    /// function selects the current level of user from database
    /// then adds +1 to it and stores new value in integer newLevelUser
    /// at least it executes a sql command that updates/overrites the field level of corresponding given username with value of newLevelUser
    void increaseLevelUserInDatabase(QString username);

    ///
    /// \brief upgradeMaximumSpeedInDatabase  updates the field maximumSpeed of corresponding field username in database with new maximum speed value
    /// \param username the currently active users name
    /// \param newMaximumSpeed the new value of maximum speed that should replace the current value of maximum speed in database
    ///
    /// function executes a sql command that select the field maximumSpeed to corresponding given username
    /// and updates/overrites its value with the value of newMaximumSpeed
    void upgradeMaximumSpeedInDatabase(QString username, double newMaximumSpeed);

    ///
    /// \brief getMaximumSpeedFromDatabase selects suitable field maximumSpeed to given username from sqlite database
    /// \param username the currently active users name
    /// \return a double with the value of maximumSpeed field of <user(name)> in database
    ///
    /// function executes a sql command that selects the maximumSpeed field to corresponding given username from sqlite database
    double getMaximumSpeedFromDatabase(QString username);

    ///
    /// \brief upgradeMaximumAccelerationInDatabase updates the field maximumAcceleration of corresponding field username in database with new acceleration value
    /// \param username the currently active users name
    /// \param newMaximumAcceleration the new value of maximum acceleration that should replace the current value of maximum acceleration in database
    ///
    /// function executes a sql command that select the field maximumAcceleration to corresponding given username
    /// and updates/overrites its value with the value of newMaximumAcceleration
    void upgradeMaximumAccelerationInDatabase(QString username, double newMaximumAcceleration);

    ///
    /// \brief getMaxmimumAccelerationFromDatabase selects suitable field maximumAcceleration to given username from sqlite database
    /// \param username the currently active users name
    /// \return a double with the value of maximumAcceleration field of <user(name)> in database
    ///
    /// function executes a sql command that selects the maximumAcceleration field to corresponding given username from sqlite database
    double getMaxmimumAccelerationFromDatabase(QString username);

    ///
    /// \brief upgradeControlInDatabase updates the field control of corresponding field username in database with new control value
    /// \param username the currently active users name
    /// \param newControl the new value of  control that should replace the current value of control in database
    ///
    /// function executes a sql command that select the field control to corresponding given username
    /// and updates/overrites its value with the value of newControl
    void upgradeControlInDatabase(QString username, double newControl);

    ///
    /// \brief getControlFromDatabase selects suitable field control to given username from sqlite database
    /// \param username the currently active users name
    /// \return a double with the value of control field of <user(name)> in database
    ///
    /// function executes a sql command that selects the control field to corresponding given username from sqlite database
    double getControlFromDatabase(QString username);

    ///
    /// \brief returnAllUsernames
    /// \return a std::vector with all usernames that are stored in database
    ///
    /// function executes a sql command to select all usernames
    /// then it goes trough all rows and stores them in the std::vector registeredUser
    /// that allocates its length depending on the number of users in database
    std::vector<std::string> returnAllUsernames();

    ///
    /// \brief initializeDatabaseManager creates a sqlite database, connects to it and creates a table user in it
    ///
    /// if no database exists: function creates database with new table user
    /// and connects to it
    ///
    /// else if database already exists it only connects to it
    void initializeDatabaseManager();

    ///
    /// \brief addUser adds user with <username> and default values to the database
    /// \param username the currently active users name
    ///
    /// function executes a sql command to insert a new row in database
    /// and stores in it:
    /// given username
    /// default values for:
    /// highscore(0.0), money(0), level(0), maximumSpeed(0.25), maximumAcceleration(0.0005), control(0.1)
    void addUser(QString username);

    ///
    /// \brief checkIfUserExists checks if a given username already exist in sqlite database
    /// \param username the currently active users name
    /// \return a bool value that true if username exist in database and false if not
    ///
    /// function executes a sql command that goes through all usernames stored in database and trys to select the user to given username
    /// if usre is found it reurns true
    /// else if user is not found till the end it returns false
    bool checkIfUserExists(QString username);

    ///
    /// \brief selectUser selcts a user to given <username> from sqlite database
    /// \param username the currently active users name
    /// \return a Object of UserProfile with all values stored in database for this user
    ///
    /// function executes the checkIfUserExists function
    /// if return value of it is true
    /// it executes a sql command and goes through the column username in database to select the user with <username>
    /// and then cretes an object of UserProfile with the values from database to return it
    /// else the function returns 0
    UserProfile * selectUser(QString username);

    ///
    /// \brief returnAllUsernamesSortedByHighscore selects all usernames and highscores ordered by corrseponding highscore from the database
    /// \return a std::vector with all the usernames and corresponding highscores in ascending order
    ///
    /// function executes a sql-command to order and select all users with ascending highscore \n
    /// then it goes trough all rows of the executed query\n
    /// if the value of highscore is not 0 it stores them in the std::vector registeredUsersSortedByHighscore\n
    /// that allocates its length depending on the number of users (that already played a game) in database\n
    std::vector<std::string> returnAllUsernamesSortedByHighscore();

    ///
    /// \brief increasePlayedGamesUserInDatabase updates the field playedGames of corresponding field username in database with new playedGames value
    /// \param username the currently active users name
    ///
    /// function selects the current value of playedGames field from database\n
    /// then adds +1 to it and stores new value int integer updatedNumberPlayedGames\n
    /// at least it executes a sql command that updates/overrites the field playedGames of corresponding given username with value of updatedNumberPlayedGames\n
    void increasePlayedGamesUserInDatabase(QString username);

    ///
    /// \brief getPlayedGamesUserFromDatabase selects suitable field playedGames to given username from sqlite database
    /// \param username the currently active users name
    /// \return an integer with the value of playedGames field of <user(name)> in database
    ///
    /// function executes a sql command that selects the playedGames field to corresponding given username from sqlite database
    int getPlayedGamesUserFromDatabase(QString username);

    ///
    /// \brief updateMaximumSavedMoneyInDatabase updates the field maximumSavedMoney of corresponding field username in database with new maximumSavedMoney value
    /// \param username the currently active users name
    /// \param potentialNewMaximumSavedMoney the new integer value that should be stored in database
    ///
    /// function executes a sql command that updates maximumSavedMoney of corresponding given username from slite database
    void updateMaximumSavedMoneyInDatabase(QString username, int potentialNewMaximumSavedMoney);

    ///
    /// \brief getMaximumSavedMoneyFromDatabase selects suitable field maximumSavedMoney to given username from sqlite database
    /// \param username the currently active users name
    /// \return an integer with the value of maximumSavedMoney field of <user(name)> in database
    ///
    /// function executes a sql command that selects the maximumSavedMoney field to corresponding given username from sqlite database
    int getMaximumSavedMoneyFromDatabase(QString username);

    ///
    /// \brief updateHighscoreAchievementNumber updates the field highscoreAchievementNumber of corresponding field username in database with new highscoreAchievementNumber value
    /// \param username the currently active users name
    ///
    /// function selects the current highscoreAchievementNumber of user from database
    /// then adds +1 to it and stores new value in integer newHighscoreAchievementNumber
    /// at least it executes a sql command that updates/overrites the field highscoreAchievementNumber of corresponding given username with value of newHighscoreAchievementNumber
    void updateHighscoreAchievementNumber(QString username);

    ///
    /// \brief getHighscoreAchievementNumber selects suitable field highscoreAchievementNumber to given username from sqlite database
    /// \param username the currently active users name
    /// \return an integer with the value of highscoreAchievementNumber field of <user(name)> in database
    ///
    /// function executes a sql command that selects the highscoreAchievementNumber field to corresponding given username from sqlite database
    int getHighscoreAchievementNumber(QString username);

    ///
    /// \brief updateMoneyAchievementNumber updates the field moneyAchievementNumber of corresponding field username in database with new moneyAchievementNumber value
    /// \param username the currently active users name
    ///
    /// function selects the current moneyAchievementNumber of user from database
    /// then adds +1 to it and stores new value in integer newMoneyAchievementNumber
    /// at least it executes a sql command that updates/overrites the field moneyAchievementNumber of corresponding given username with value of newMoneyAchievementNumber
    void updateMoneyAchievementNumber(QString username);

    ///
    /// \brief getMoneyAchievementNumber selects suitable field moneyAchievementNumber to given username from sqlite database
    /// \param username the currently active users name
    /// \return an integer with the value of moneyAchievementNumber field of <user(name)> in database
    ///
    /// function executes a sql command that selects the moneyAchievementNumber field to corresponding given username from sqlite database
    int getMoneyAchievementNumber(QString username);

    ///
    /// \brief updatePlayedGamesAchievementNumber updates the field playedGamesAchievementNumber of corresponding field username in database with new playedGamesAchievementNumber value
    /// \param username the currently active users name
    ///
    /// function selects the current playedGamesAchievementNumber of user from database
    /// then adds +1 to it and stores new value in integer newPlayedGamesAchievementNumber
    /// at least it executes a sql command that updates/overrites the field playedGamesAchievementNumber of corresponding given username with value of newPlayedGamesAchievementNumber
    void updatePlayedGamesAchievementNumber(QString username);

    ///
    /// \brief getPlayedGamesAchievementNumber selects suitable field playedGamesAchievementNumber to given username from sqlite database
    /// \param username the currently active users name
    /// \return an integer with the value of playedGamesAchievementNumber field of <user(name)> in database
    ///
    /// function executes a sql command that selects the playedGamesAchievementNumber field to corresponding given username from sqlite database
    int getPlayedGamesAchievementNumber(QString username);
private:
    QSqlDatabase databaseGame;
};

#endif // DATABASE_H


