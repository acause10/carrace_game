#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QApplication>
//#include "Car.h"

class DatabaseManager;

///
/// \brief The UserProfile class creates an object, that can be used as intersection beetween the sqlite database(Manager) and the application
///
///  with a UserProfile object all entries of the database row from given username can be returned and cahnged with getter and setter methods
class UserProfile
{
public:
    ///
    /// \brief UserProfile default constructor
    ///
    UserProfile();
    ///
    /// \brief UserProfile constructor
    /// \param enteredName the users name
    /// \param highscoreUser the users highscore
    /// \param moneyUser the users money
    /// \param levelUser the users level
    /// \param maximimumSpeedUser the users maximum speed
    /// \param maximumAccelerationUser the users maximum accleration
    /// \param controlUser the users control
    ///
    /// in this construtor a database is initialized and a connection to it created
    UserProfile(QString enteredName, double highscoreUser, int moneyUser, int levelUser,
                double maximimumSpeedUser, double maximumAccelerationUser, double controlUser, int playedGames, int maximumSavedMoney,
                int highscoreAchievementNumber, int moneyAchievementNumber, int playedGamesAchievementNumber);//alle daten aus database in den Konstruktor übergeben bei erstellen des Userprofiles

    ///
    /// \brief addNewUser the action to add a new user in database gets commited to the databasemanager
    /// \param username the username to acces the data of corresponding userprofile
    /// \return true if it worked to add the user and false if not
    ///
    /// functions checks if username already exists
    /// if username already exists: return false
    /// else: add user to database action is commited to the databasemanager
    /// and return true
    bool addNewUser(QString username);

    ///
    /// \brief getNameUser returns the username that is currently given to the UserProfile
    /// \return a QString with the username of choosen object from UserProfile
    ///
    QString getNameUser();

    ///
    /// \brief getHighscore returns the highscore of choosen object from UserProfile  based on the username
    /// \param username the username to acces the data of corresponding userprofile
    /// \return a double with the highscore of the object from UserProfile with corresponding username
    ///
    double getHighscore(QString username);

    ///
    /// \brief updateHighscore the action to update the highscore of the userprofile gets commited to the database(Manager)
    /// \param username the username to acces the data of corresponding userprofile
    /// \param potentialNewHighscore the time the user needed to finish the route
    ///
    /// functions checks if the potentialNewHighscore time is higher than the current stored time in database
    /// if it is: action to update highscore in database with potentialNewHighscore is committed to the database(Manager)
    void updateHighscore(QString username, double potentialNewHighscore);

    ///
    /// \brief getMoneyUser retuns the money of choosen object from UserProfile based on the username
    /// \param username the username to acces the data of corresponding userprofile
    /// \return an integer with the money of the object from UserProfile with corresponding username
    ///
    int getMoneyUser(QString username);

    ///
    /// \brief updateMoneyUser the action to update the money of the userprofile gets commited to the database(Manager)
    /// \param username the username to acces the data of corresponding userprofile
    /// \param collectedCoins the number(integer) of coins that has been collected during the race
    ///
    void updateMoneyUser(QString username, int collectedCoins);

    ///
    /// \brief getLevelUser retuns the level of choosen object from UserProfile based on the username
    /// \param username the username to acces the data of corresponding userprofile
    /// \return an integer with level of the object from UserProfile with corresponding username
    ///
    int getLevelUser(QString username);

    ///
    /// \brief updateLevelUser the action to update the level of the userprofile gets commited to the database(Manager)
    /// \param username the username to acces the data of corresponding userprofile
    ///
    void updateLevelUser(QString username);

    ///
    /// \brief getMaximumSpeedUser retuns the maximumSpeed of choosen object from UserProfile based on the username
    /// \param username the username to acces the data of corresponding userprofile
    /// \return a double with maximumSpeed of the object from UserProfile with corresponding username
    ///
    double getMaximumSpeedUser(QString username);

    ///
    /// \brief updateMaximumSpeed the action to update the maximumSpeed of the userprofile gets commited to the database(Manager)
    /// \param username the username to acces the data of corresponding userprofile
    ///
    /// function has stored the different maximumSpeed options in a std::vector
    ///
    /// function calls the getMoney function to check if user has at least a integer of 50 or more stored in money
    /// if user has: function checks if the current maximumSpeed is already the last entry of the std::vector
    /// if it is: the boolean isUpgradePossible is set to false an nothing will be updated
    /// else if it is not: (boolean isUpgradePossible stays true):
    /// action to update maximumSpeed in database with the folllowing value in the std::vector gets commited to the database(Manager)
    /// and action to update money of user in database to currentMoney -50 gets commited to the database(Manager)
    ///
    void updateMaximumSpeed(QString username);

    ///
    /// \brief getMaximumAccelerationUser retuns the maximumAcceleration of choosen object from UserProfile based on the username
    /// \param username the username to acces the data of corresponding userprofile
    /// \return a double with maximumAcceleration of the object from UserProfile with corresponding username
    ///
    double getMaximumAccelerationUser(QString username);

    ///
    /// \brief updateMaximumAcceleration the action to update the maximumAcceleration of the userprofile gets commited to the database(Manager)
    /// \param username the username to acces the data of corresponding userprofile
    ///
    /// function has stored the different maximumAcceleration options in a std::vector
    ///
    /// function calls the getMoney function to check if user has at least a integer of 50 or more stored in money
    /// if user has: function checks if the current maximumAcceleration is already the last entry of the std::vector
    /// if it is: the boolean isUpgradePossible is set to false an nothing will be updated
    /// else if it is not: (boolean isUpgradePossible stays true):
    /// action to update maximumAcceleration in database with the folllowing value in the std::vector gets commited to the database(Manager)
    /// and action to update money of user in database to currentMoney -50 gets commited to the database(Manager)
    ///
    void updateMaximumAcceleration(QString username);

    ///
    /// \brief getControlUserretuns the control of choosen object from UserProfile based on the username
    /// \param username the username to acces the data of corresponding userprofile
    /// \return a double with control of the object from UserProfile with corresponding username
    ///
    double getControlUser(QString username);

    ///
    /// \brief updateControl the action to update the control of the userprofile in database gets commited to the databaseManager
    /// \param username the username to acces the data of corresponding userprofile
    ///
    /// function has stored the different control options in a std::vector
    ///
    /// function calls the getMoney function to check if user has at least a integer of 50 or more stored in money
    /// if user has: function checks if the current control is already the last entry of the std::vector
    /// if it is: the boolean isUpgradePossible is set to false an nothing will be updated
    /// else if it is not: (boolean isUpgradePossible stays true):
    /// action to update control in database with the folllowing value in the std::vector gets commited to the database(Manager)
    /// and action to update money of user in database to currentMoney -50 gets commited to the database(Manager)
    ///
    void updateControl(QString username);

    ///
    /// \brief getCurrentUser the action to select the current user from database gets commited to the databaseManager
    /// \return an object from UserProfile with all the information (username, highscore, money, level, maximumSpeed, maximumAcceleration, control) coming from the database
    ///
    UserProfile * getCurrentUser();

    ///
    /// \brief returnAllUsernames the action to return all usernames that are stored in the database gets commited to the databaseManager
    /// \return a std::vector with all usernames that are stored in the database
    ///
    std::vector<std::string> returnAllUsernames();

    ///
    /// \brief returnAllUsernamesSortedByHighscore the action to return all usernames with corresponding highscore, that are stored in the database gets commited to the databaseManager
    /// \return a std::vector with all usernames and highscores that are stored in the database
    ///
    std::vector<std::string> returnAllUsernamesSortedByHighscore();

    ///
    /// \brief increasePlayedGames the action to update the playedGames value of the userprofile gets commited to the database(Manager)
    /// \param username the username to acces the data of corresponding userprofile
    ///
    void increasePlayedGames(QString username);

    ///
    /// \brief getPlayedGames retuns the playedGames value of choosen object from UserProfile based on the username
    /// \param username the username to acces the data of corresponding userprofile
    /// \return an integer with playedGames value of the object from UserProfile with corresponding username
    ///
    int getPlayedGames(QString username);

    ///
    /// \brief updateMaximumSavedMoney the action to update the maximumSavedMoney value of the userprofile gets commited to the database(Manager)
    /// \param username the username to acces the data of corresponding userprofile
    /// \param potentialNewMaximumSavedMoney the value of money in database after coins have been added
    ///
    ///  functions checks if the potentialNewMaximumSavedMoney value is higher than the current stored value in database
    /// if it is: action to update highscore in database with potentialNewMaximumSavedMoney is committed to the database(Manager)
    void updateMaximumSavedMoney(QString username, int potentialNewMaximumSavedMoney);

    ///
    /// \brief getMaximumSavedMoney retuns the maximumSavedMoney value of choosen object from UserProfile based on the username
    /// \param username the username to acces the data of corresponding userprofile
    /// \return an integer with maximumSavedMoney value of the object from UserProfile with corresponding username
    ///
    int getMaximumSavedMoney(QString username);

    ///
    /// \brief updateHighscoreAchievementNumber the action to update the highscoreAchievementNumber of the userprofile gets commited to the database(Manager)
    /// \param username the username to acces the data of corresponding userprofile
    ///
    void updateHighscoreAchievementNumber(QString username);

    ///
    /// \brief getHighscoreAchievementNumber retuns the highscoreAchievementNumber of choosen object from UserProfile based on the username
    /// \param username the username to acces the data of corresponding userprofile
    /// \return an integer with highscoreAchievementNumber of the object from UserProfile with corresponding username
    ///
    int getHighscoreAchievementNumber(QString username);

    ///
    /// \brief updateMoneyAchievementNumber the action to update the moneyAchievementNumber of the userprofile gets commited to the database(Manager)
    /// \param username the username to acces the data of corresponding userprofile
    ///
    void updateMoneyAchievementNumber(QString username);

    ///
    /// \brief getMoneyAchievementNumber retuns the moneyAchievementNumber of choosen object from UserProfile based on the username
    /// \param username the username to acces the data of corresponding userprofile
    /// \return an integer with moneyAchievementNumber of the object from UserProfile with corresponding username
    ///
    int getMoneyAchievementNumber(QString username);

    ///
    /// \brief updatePlayedGamesAchievementNumber the action to update the playedGamesAchievementNumber of the userprofile gets commited to the database(Manager)
    /// \param username the username to acces the data of corresponding userprofile
    ///
    void updatePlayedGamesAchievementNumber(QString username);

    ///
    /// \brief getPlayedGamesAchievementNumber retuns the playedGamesAchievementNumber of choosen object from UserProfile based on the username
    /// \param username the username to acces the data of corresponding userprofile
    /// \return an integer with playedGamesAchievementNumber of the object from UserProfile with corresponding username
    ///
    int getPlayedGamesAchievementNumber(QString username);
private:
    QString username;
    double highscoreUser = 0.0;
    int moneyUser = 0;
    int levelUser = 1;
    double maximumSpeedUser;
    double maximumAccelerationUser;
    double controlUser;
    int playedGames = 0;
    int maximumSavedMoney;
    int highscoreAchievementNumber = 0;
    int moneyAchievementNumber = 0;
    int playedGamesAchievementNumber = 0;

    ///
    /// \brief databaseManager
    ///
    /// should not be removed until the application gets closed
    DatabaseManager * databaseManager;
    QString currentUsername;
};

#endif // USERPROFILE_H
