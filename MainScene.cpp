#include <MainScene.h>

MainScene::MainScene(): QGraphicsView(){
    //Create the Mainscene of the game: this is the Central Widget of the game, on which the mainWidgets are placed
    mainScene = new QGraphicsScene(this);
    mainScene->setSceneRect(0,0,1700,1000);

    // alter window
    setScene(mainScene);
    setFixedSize(1700,1000);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //this->setStyleSheet("QGraphicsScene {background-image: url(:/resources/images/backgroundMainwindow.png)};"
    //                    "QPushButton:hover {background-image: url(:/resources/images/BackgroundButtons.png);}");
}
