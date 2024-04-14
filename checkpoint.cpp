#include "checkpoint.h"
#include <QGraphicsItem>
#include "car.h"
#include <QDebug>
#include <QTimer>
#include "startline.h"

Checkpoint::Checkpoint(QGraphicsItem *parent)
{

    // creating 4 checkpoints as 4 polygons
    // first creating shape, resizing it and then setting
    // position and opacity
    QVector<QPointF> points;

    points << QPointF(0,0) << QPointF(2,0) << QPointF(2,2) << QPointF(0,2);

    int scale = 52;
    for (size_t i=0, n=points.size(); i<n; i++){
        points[i] *= scale;
    }

    QPolygonF poly(points);

    checkpoint = new QGraphicsPolygonItem(poly,this);
    checkpoint->setPos(22,300);
    checkpoint->setOpacity(0);

    checkpoint_2 = new QGraphicsPolygonItem(poly,this);
    checkpoint_2->setPos(340,625);
    checkpoint_2->setOpacity(0);

    checkpoint_3 = new QGraphicsPolygonItem(poly,this);
    checkpoint_3->setPos(673,300);
    checkpoint_3->setOpacity(0);

    checkpoint_4 = new QGraphicsPolygonItem(poly,this);
    checkpoint_4->setPos(340,32);
    checkpoint_4->setOpacity(0);

    QTimer * timer = new QTimer(this);
    QTimer * timer_2 = new QTimer(this);
    QTimer * timer_3 = new QTimer(this);
    QTimer * timer_4 = new QTimer(this);


    // signals to track collision occurence
    connect(timer,SIGNAL(timeout()),this,SLOT(checkCheckpoint()));
    connect(timer,SIGNAL(timeout()),this,SLOT(checkCheckpoint2()));
    connect(timer,SIGNAL(timeout()),this,SLOT(checkCheckpoint3()));
    connect(timer,SIGNAL(timeout()),this,SLOT(checkCheckpoint4()));

    timer->start(60);
    timer_2->start(60);
    timer_3->start(60);
    timer_4->start(60);


}

int Checkpoint::checkCheckpoint()
{

    // checking collisions between car and first checkpoint
    QList<QGraphicsItem *> colliding_items_cp = checkpoint->collidingItems();

    for (int i=0, n=colliding_items_cp.size(); i<n; ++i){
        if (typeid(*(colliding_items_cp[i])) == typeid(Car)){

            counter_checkpoint++;
            qDebug()<<"First counter:"<<counter_checkpoint;
        }
    }

    return counter_checkpoint;
}

int Checkpoint::checkCheckpoint2()
{

    // checking collisions between car and second checkpoint
    QList<QGraphicsItem *> colliding_items_cp = checkpoint_2->collidingItems();

    for (int i=0, n=colliding_items_cp.size(); i<n; ++i){
        if (typeid(*(colliding_items_cp[i])) == typeid(Car)){

            counter_checkpoint_2++;
            qDebug()<<"Second counter:"<<counter_checkpoint_2;
        }
    }

    return counter_checkpoint_2;
}

int Checkpoint::checkCheckpoint3()
{

    // checking collisions between car and third checkpoint
    QList<QGraphicsItem *> colliding_items_cp = checkpoint_3->collidingItems();

    for (int i=0, n=colliding_items_cp.size(); i<n; ++i){
        if (typeid(*(colliding_items_cp[i])) == typeid(Car)){

            counter_checkpoint_3++;
            qDebug()<<"Third counter:"<<counter_checkpoint_3;
        }
    }
    return counter_checkpoint_3;
}

int Checkpoint::checkCheckpoint4()
{

    // checking collisions between car and fourth checkpoint
    QList<QGraphicsItem *> colliding_items_cp = checkpoint_4->collidingItems();

    for (int i=0, n=colliding_items_cp.size(); i<n; ++i){
        if (typeid(*(colliding_items_cp[i])) == typeid(Car)){

            counter_checkpoint_4++;
            qDebug()<<"Fourth counter:"<<counter_checkpoint_4;
        }
    }

    return counter_checkpoint_4;
}


