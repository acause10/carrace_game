#ifndef SHOPDIALOG_H
#define SHOPDIALOG_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <UserProfile.h>

///
/// \brief The ShopDialog class
///
/// creates a dialog with the options to upgrade the car (maximum acceleration, maximum speed and control)
class ShopDialog: public QWidget
{
    Q_OBJECT

public:
    ///
    /// \brief ShopDialog constructor
    /// \param parent
    /// \param currentUsername the current active users name
    ///
    ShopDialog(QWidget *parent = 0, QString currentUsername = "");
private:
    ///
    /// \brief gridLayoutShop
    ///
    /// should not be removed before shopDialog gets closed
    QGridLayout *gridLayoutShop;

    ///
    /// \brief backToRouteSelectionScreenButton when clicked this shopDialog gets closed
    ///
    /// should not be removed before shopDialog gets closed
    QPushButton *backToRouteSelectionScreenButton;

    ///
    /// \brief upgradeMaxSpeedButton when clicekd upgrades the maximum speed of current user in database
    ///
    /// should not be removed before shopDialog gets closed
    QPushButton *upgradeMaxSpeedButton;

    ///
    /// \brief upgradeAccelerationButton when clicekd upgrades the maximum acceleration of current user in database
    ///
    /// should not be removed before shopDialog gets closed
    QPushButton *upgradeAccelerationButton;

    ///
    /// \brief upgradeControlButton when clicekd upgrades the control of current user in database
    ///
    /// should not be removed before shopDialog gets closed
    QPushButton *upgradeControlButton;

    ///
    /// \brief userprofile gives intersection from the application to the database
    ///
    /// should not be removed before shopDialog gets closed
    UserProfile * userprofile;

    ///
    /// \brief currentUsernameInShopDialog the variable to use the currentUsername in every function of the class (it is equal to currentUsername)
    ///
    /// should not be removed before shopDialog gets closed
    QString currentUsernameInShopDialog;

    ///
    /// \brief currentMoneyLabel shows the current sum of coins the current active user has collected
    ///
    /// should not be removed before shopDialog gets closed
    QLabel *currentMoneyLabel;

    ///
    /// \brief currentMaxSpeedLabel shows the current maximum speed the current active user has
    ///
    /// should not be removed before shopDialog gets closed
    QLabel *currentMaxSpeedLabel;

    ///
    /// \brief currentAccelerationLabel shows the current maximum acceleration the current active user has
    ///
    /// should not be removed before shopDialog gets closed
    QLabel *currentAccelerationLabel;

    ///
    /// \brief currentControlLabel shows the current control the current active user has
    ///
    /// should not be removed before shopDialog gets closed
    QLabel *currentControlLabel;

    ///
    /// \brief maxSpeedReachedLabel is showed when user has reached the maximum option of maximumSpeed
    ///
    /// should not be removed before shopDialog gets closed
    QLabel * maxSpeedReachedLabel;

    ///
    /// \brief maxAccelerationReachedLabel is showed when user has reached the maximum option of maximumAcceleration
    ///
    /// should not be removed before shopDialog gets closed
    QLabel * maxAccelerationReachedLabel;

    ///
    /// \brief maxControlLabel is showed when user has reached the maximum option of control
    ///
    /// should not be removed before shopDialog gets closed
    QLabel * maxControlLabel;

    void closeShopDialog();
    void upgradeMaxSpeedClicked();
    void upgradeMaxAccelerationClicked();
    void upgradeControlClicked();
};

#endif // SHOPDIALOG_H
