#include <ShopDialog.h>
#include <UserProfile.h>
#include <QDebug>

ShopDialog::ShopDialog(QWidget *parent, QString currentUsername)
    : QWidget(parent)
{
    qDebug() << "current username in shop dialog: " << currentUsername;
    userprofile = new UserProfile();
    currentUsernameInShopDialog = currentUsername;

    //set Layout for Shop
    gridLayoutShop = new QGridLayout;

    //create backButton for Shop
    backToRouteSelectionScreenButton = new QPushButton(tr("Back to routes"));
    connect(backToRouteSelectionScreenButton, &QPushButton::clicked, this, &ShopDialog::closeShopDialog);
    gridLayoutShop->addWidget(backToRouteSelectionScreenButton, 0,0);

    //create Information Labels for shop
    currentMoneyLabel = new QLabel(tr("Your money is: ") + QString::number(userprofile->getMoneyUser(currentUsername)) + tr(" Coins"));
    gridLayoutShop->addWidget(currentMoneyLabel, 0, 2);

    currentMaxSpeedLabel = new QLabel(tr("Your maximum Speed is: ") + QString::number(userprofile->getMaximumSpeedUser(currentUsername)) + tr(" m/s"));
    gridLayoutShop->addWidget(currentMaxSpeedLabel, 1, 0);
    maxSpeedReachedLabel = new QLabel(" ");
    gridLayoutShop->addWidget(maxSpeedReachedLabel, 1, 2);

    currentAccelerationLabel = new QLabel(tr("Your acceleration is: ") + QString::number(userprofile->getMaximumAccelerationUser(currentUsername)) + tr(" m/s^2"));
    gridLayoutShop->addWidget(currentAccelerationLabel, 2, 0);
    maxAccelerationReachedLabel = new QLabel(" ");
    gridLayoutShop->addWidget(maxAccelerationReachedLabel, 2, 2);

    currentControlLabel = new QLabel(tr("Your controller Level is: ") + QString::number(userprofile->getControlUser(currentUsername)) + tr(" of 10"));
    gridLayoutShop->addWidget(currentControlLabel, 3, 0);
    maxControlLabel = new QLabel(" ");
    gridLayoutShop->addWidget(maxControlLabel, 3, 2);

    //create upgrade Buttons for shop
    upgradeMaxSpeedButton = new QPushButton(tr("upgrade maximum Speed with 50 coins"));
    connect(upgradeMaxSpeedButton, &QPushButton::clicked, this, &ShopDialog::upgradeMaxSpeedClicked);
    gridLayoutShop->addWidget(upgradeMaxSpeedButton, 1, 1);

    upgradeAccelerationButton = new QPushButton(tr("upgrade acceleration with 50 coins"));
    connect(upgradeAccelerationButton, &QPushButton::clicked, this, &ShopDialog::upgradeMaxAccelerationClicked);
    gridLayoutShop->addWidget(upgradeAccelerationButton, 2, 1);

    upgradeControlButton = new QPushButton(tr("upgrade controller with 50 coins"));
    connect(upgradeControlButton, &QPushButton::clicked, this, &ShopDialog::upgradeControlClicked);
    gridLayoutShop->addWidget(upgradeControlButton, 3, 1);

    //alter Dialog
    setWindowTitle(tr("Upgrade Shop - ") + currentUsernameInShopDialog);
    setLayout(gridLayoutShop);
}


void ShopDialog::closeShopDialog()
{
    this->close();
}

//Function changes the maximumSpeed of current Userprofile to update it in database
void ShopDialog::upgradeMaxSpeedClicked()
{
    userprofile->updateMaximumSpeed(currentUsernameInShopDialog);
    currentMoneyLabel->setText(tr("Your money is: ") + QString::number(userprofile->getMoneyUser(currentUsernameInShopDialog)) + tr(" Coins"));
    currentMaxSpeedLabel->setText(tr("Your maximum Speed is: ") + QString::number(userprofile->getMaximumSpeedUser(currentUsernameInShopDialog)) + tr(" m/s"));
    if (userprofile->getMaximumSpeedUser(currentUsernameInShopDialog) == 0.35) {
        maxSpeedReachedLabel->setText("You have reached the best speed configuration.");
    }
}

//Function changes the maximumAcceleration of current Userprofile to update it in database
void ShopDialog::upgradeMaxAccelerationClicked()
{
    userprofile->updateMaximumAcceleration(currentUsernameInShopDialog);
    currentMoneyLabel->setText(tr("Your money is: ") + QString::number(userprofile->getMoneyUser(currentUsernameInShopDialog)) + tr(" Coins"));
    currentAccelerationLabel->setText(tr("Your acceleration is: ") + QString::number(userprofile->getMaximumAccelerationUser(currentUsernameInShopDialog)) + tr(" m/s^2"));
    if (userprofile->getMaximumAccelerationUser(currentUsernameInShopDialog) == 0.0009) {
        maxAccelerationReachedLabel->setText("You have reached the best acceleration configuration.");
    }
}

//Function changes the control of current Userprofile to update it in database
void ShopDialog::upgradeControlClicked()
{
    userprofile->updateControl(currentUsernameInShopDialog);
    currentMoneyLabel->setText(tr("Your money is: ") + QString::number(userprofile->getMoneyUser(currentUsernameInShopDialog)) + tr(" Coins"));
    currentControlLabel->setText(tr("Your controller Level is: ") + QString::number(userprofile->getControlUser(currentUsernameInShopDialog)) + tr(" of 10"));
    if (userprofile->getControlUser(currentUsernameInShopDialog) == 0.3) {
        maxControlLabel->setText("You have reached the best controller configuration.");
    }
}
