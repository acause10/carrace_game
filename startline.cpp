#include "startline.h"
#include "car.h"
#include <QtCore>
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include "checkpoint.h"

StartLine::StartLine(QString currentUsername)
{
    userprofile = new UserProfile;
    publicCurrentUsername = currentUsername;
    // create polygon serving as the startline
    QVector<QPointF> points_vertical;
    points_vertical << QPointF(0,0) << QPointF(4,0) << QPointF(4,0.1) << QPointF(0,0.1);

    // scale it to route proportions
    int scale_vertic = 28;
    for (size_t i=0, n = points_vertical.size(); i < n; i++){
        points_vertical[i] *= scale_vertic;
    }

    // poly
    QPolygonF vertical(points_vertical);

    start = new QGraphicsPolygonItem(vertical,this);
    start->setPos(19,225);
    start->setOpacity(0);

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(checkLap()));
    timer->start(1);

    QTimer * finish_timer = new QTimer();
    connect(finish_timer,SIGNAL(timeout()),this,SLOT(checkFinal()));
    finish_timer->start(300);

}


void StartLine::checkLap()
{
    QList<QGraphicsItem *> colliding_items_ln = start->collidingItems();

    for (int i=0, n=colliding_items_ln.size(); i<n; ++i){
            if ((typeid(*(colliding_items_ln[i])) == typeid(Car))&&(counter_checkpoint_4>0)){

                if ((lap==2)&&(counter_checkpoint_4>0)){

                    qDebug()<<"Third lap finished";
                    scene()->removeItem(start);
                    finished_race += 1;             // in DB abzuspeichern fur achievements wenn man den fahrt beendet
                    theCar->setGamestatus(0);   // and the race ended

                    //update data in database
                    userprofile->increasePlayedGames(publicCurrentUsername);
                    userprofile->updateHighscore(publicCurrentUsername, theCar->getRunningtime());
                    userprofile->updateMoneyUser(publicCurrentUsername, theCar->collectedCoins);

                    emit openGameOverScreenFromStartlineSIGNAL(); // create new screen with the time showed

                }

                else if((lap==1)&&(counter_checkpoint_4>0)){

                    qDebug()<<"Second lap finished";
                }

                     lap++;
                     qDebug() <<"First lap" << lap;

                     counter_checkpoint = 0;
                     counter_checkpoint_2 = 0;
                     counter_checkpoint_3 = 0;
                     counter_checkpoint_4 = 0;
            }

        }

}


void StartLine::setTheCar(Car *value)
{
    theCar = value;
}

double StartLine::getNeededTimeForRace()
{
    double neededTimeForRace = theCar->getRunningtime();


        // end the game
            third_lap++;
            qDebug() << "Third lap"<<third_lap;
            scene()->removeItem(start);
            finished_race += 1;             // in DB abzuspeichern fur achievements wenn man den fahrt beendet

    return neededTimeForRace;
}


int StartLine::getCollectedCoins()
{
    int collectedCoins = theCar->collectedCoins;

    return collectedCoins;
}
