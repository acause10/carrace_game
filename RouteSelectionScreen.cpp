#include <RouteSelectionScreen.h>
#include <QDebug>
#include <mainwindow.h>

RouteSelectionScreen::RouteSelectionScreen(QWidget *parent, QString currentUsername): QWidget(parent)
{
    //set current user for the screen
    this->setCurrentUsername(currentUsername);
    qDebug() << "public current username in route selection: " << publicCurrentUsername;


    //create Gridlayout for the Startmenu/screen
    routeSelectionGridLayout = new QGridLayout();
    routeSelectionGridLayout->setSizeConstraint(QLayout::SetFixedSize);

//    //create Text for Startscreen
//    QLabel * chooseLandscapeText = new QLabel("Choose the Landscape for your race... ");
//    routeSelectionGridLayout->addWidget(chooseLandscapeText, 0, 0, 1, 3);

//    //create Buttons to select Landscape
//    landscapeAsphaltButton = new QPushButton("Asphalt");
//    routeSelectionGridLayout->addWidget(landscapeAsphaltButton, 1, 0);

//    landscapeDesertButton = new QPushButton("Desert");
//    routeSelectionGridLayout->addWidget(landscapeDesertButton, 1, 1);

//    landscapeSpaceButton = new QPushButton("Space");
//    routeSelectionGridLayout->addWidget(landscapeSpaceButton, 1, 2);

//    landscapeOceanButton = new QPushButton("Ocean");
//    routeSelectionGridLayout->addWidget(landscapeOceanButton, 2, 0);

//    landscapeIceButton = new QPushButton("Ice");
//    routeSelectionGridLayout->addWidget(landscapeIceButton, 2, 1);

//    landscapeMudButton = new QPushButton("Mud");
//    routeSelectionGridLayout->addWidget(landscapeMudButton, 2, 2);

    //create Button to open shop
    shopButton = new QPushButton("Shop");
    shopButton->setStyleSheet("QPushButton{background-image: url(:/resources/images/backgroundMainwindow.png);}"
                              "QPushButton:hover {background-image: url(:/resources/images/BackgroundButtons.png);}");
    connect(shopButton, &QPushButton::clicked, this, &RouteSelectionScreen::openShopDialog);
    routeSelectionGridLayout->addWidget(shopButton, 3, 0, 1, 3);

    //alter window
    setFixedSize(1700,1000);
    setLayout(routeSelectionGridLayout);
}

void RouteSelectionScreen::openShopDialog()
{
    shop = new ShopDialog(nullptr, publicCurrentUsername);
    shop->show();
}

//Function sets the current username in routeSelectionScreen
void RouteSelectionScreen::setCurrentUsername(QString username)
{
    publicCurrentUsername = username;
    qDebug() << "currentUsername in RouteSelectionScreen: " <<publicCurrentUsername;
}

RouteSelectionScreen::~RouteSelectionScreen()
{

}
