#include <GameScene.h>
#include <QtCore>
#include <QtGui>
#include <stdlib.h>
#include <obstacle.h>
#include <checkpoint.h>
#include <Innerbounds.h>
#include <startline.h>
#include <QImage>
#include <Outterbounds.h>
#include <car.h>
#include <QDebug>

GameScene::GameScene(QString currentUsername): QGraphicsView(){
    //Create the scene for the game
    gameScene = new QGraphicsScene(this);
    gameScene->setSceneRect(0,0,800,749);   //rescaled gamescene to adapt to the racetrack size
    setBackgroundBrush(QBrush(QImage(":/resources/images/FinalTrack.png")));

    //add car
    car1 = new Car(QPointF(62,240),20,40, currentUsername);//start position
    //car1->setRect(0,0,20,40);
    car1->setRotation(180);
    car1->setRunningtime(0);//reset timer
    car1->setGamestatus(1);//press any key to start
    gameScene->addItem(car1);

    Checkpoint * check = new Checkpoint();
    check->setPos(0,0);
    gameScene->addItem(check);

    // create inner trackbounds and add them to the scene
    Innerbounds * bounds = new Innerbounds();
    bounds->setTheCar(car1);
    gameScene->addItem(bounds);

    // create outter trackbounds and add them to the scene
    Outterbounds * bounds_out = new Outterbounds();
    bounds_out->setTheCar(car1);
    gameScene->addItem(bounds_out);

    // create startline
    start = new StartLine(currentUsername);
    start->setTheCar(car1);
    gameScene->addItem(start);
    //start->setOpacity(0);

    //set the scene
    setScene(gameScene);

    Obstacle * obstacle1 = new Obstacle();
    gameScene->addItem(obstacle1);
    obstacle1->setPos(240,87);

    Obstacle * obstacle2 = new Obstacle();
    gameScene->addItem(obstacle2);
    obstacle2->setPos(170,630);

    Obstacle * obstacle3 = new Obstacle();
    gameScene->addItem(obstacle3);
    obstacle3->setPos(480,67);

    Obstacle * obstacle4 = new Obstacle();
    gameScene->addItem(obstacle4);
    obstacle4->setPos(470,610);

    Obstacle * obstacle5 = new Obstacle();
    gameScene->addItem(obstacle5);
    obstacle5->setPos(690,400);

    Obstacle * obstacle6 = new Obstacle();
    gameScene->addItem(obstacle6);
    obstacle6->setPos(720,525);

    Obstacle * obstacle7 = new Obstacle();
    gameScene->addItem(obstacle7);
    obstacle7->setPos(520,90);

    Obstacle * obstacle8 = new Obstacle();
    gameScene->addItem(obstacle8);
    obstacle8->setPos(700,90);

    Obstacle * obstacle9 = new Obstacle();
    gameScene->addItem(obstacle9);
    obstacle9->setPos(450,700);

    Obstacle * obstacle10 = new Obstacle();
    gameScene->addItem(obstacle10);
    obstacle10->setPos(100,600);

    // alter window
    setFixedSize(800,749); //gamescene adapted to the image size (racetrack)
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}


Car *GameScene::getTheCar() const
{
    return car1;

}
