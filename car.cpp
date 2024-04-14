#include <QDebug>
#include <QPixmap>
#include <QList>
#include <stdio.h>
#include <QGraphicsScene>
#include <QDebug>
#include "Car.h"
#include "checkpoint.h"
#include "startline.h"
#include "Innerbounds.h"
#include "Outterbounds.h"
#include "obstacle.h"
#include <time.h>


Car::Car()
{

}

Car::Car(QPointF p,double w, double h, QString currentUsername):begin(p),width(w),height(h)
{
   qDebug() << "username in car: " << currentUsername;
   publicCurrentUsername = currentUsername;
    //add Rect/Pixmap
    color="Red";//color changable
    setPixmap(QPixmap(":resources/images/car"+color+".png").scaled(QSize(width,height),Qt::IgnoreAspectRatio));//scale Pixmap to given (width,height)
    setRotation(90);//starting direction in degrees; clockwise from (0,1)
    setPos(begin);
    setTransformOriginPoint(0.5*width,0.5*height);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    //load the data of car from database
    maxspeed = userprofile->getMaximumSpeedUser(publicCurrentUsername);
    maxacceleration = userprofile->getMaximumAccelerationUser(publicCurrentUsername);
    control = userprofile->getControlUser(publicCurrentUsername);

    cx=x();cy=-y();//coordination system in Qt is with reversed y-Axis
    front_friction=back_friction=QPointF(friction_rolling,friction_sliding);//friction{wheel direction,wheel normal direction}
    QTimer * timer_move = new QTimer(this);
    QTimer * timer_showing = new QTimer(this);
    connect(timer_move,SIGNAL(timeout()),this,SLOT(move()));
    connect(timer_showing,SIGNAL(timeout()),this,SLOT(showing()));
    timer_move->start(1);//calculte the new status of car 1000Hz
    timer_showing->start(10);//then show the newest status of car 100fps
}

void Car::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up){
        keypressed[0]=1;
    }
    if (event->key() == Qt::Key_Down){
        keypressed[1]=1;
    }
    if (event->key() == Qt::Key_Left){
        keypressed[2]=1;
    }
    if (event->key() == Qt::Key_Right){
        keypressed[3]=1;
    }
    if (event->key() == Qt::Key_W){
        keypressed[4]=1;
    }
    if (event->key() == Qt::Key_S){
        keypressed[5]=1;
    }
    if (event->key() == Qt::Key_A){
        keypressed[6]=1;
    }
    if (event->key() == Qt::Key_D){
        keypressed[7]=1;
    }
    if (event->key() == Qt::Key_Space){
        keypressed[8]=1;
    }
    //in game status 1 (press any key to start), update game status to 2 (game running)
    if (gamestatus==1) gamestatus=2;
}

void Car::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up){
        keypressed[0]=0;
    }
    if (event->key() == Qt::Key_Down){
        keypressed[1]=0;
    }
    if (event->key() == Qt::Key_Left){
        keypressed[2]=0;
    }
    if (event->key() == Qt::Key_Right){
        keypressed[3]=0;
    }
    if (event->key() == Qt::Key_W){
        keypressed[4]=0;
    }
    if (event->key() == Qt::Key_S){
        keypressed[5]=0;
    }
    if (event->key() == Qt::Key_A){
        keypressed[6]=0;
    }
    if (event->key() == Qt::Key_D){
        keypressed[7]=0;
    }
    if (event->key() == Qt::Key_Space){
        keypressed[8]=0;
    }
}


// left,right,up,down,brake until now

void Car::focusOutEvent(QFocusEvent *event)
{
    setFocus();
}

void Car::move()
{
    //detection game status
    //==, begin when key pressed
    if (gamestatus!=2) return;
    runningtime+=1;

    //v1 single point engine
    // //drifting simulation
    // cx+=0.3*lastspeed*sin(lastrotation*M_PI/180);
    // cy+=0.3*lastspeed*cos(lastrotation*M_PI/180);
    // lastspeed=speed;lastrotation=rotation();
    // cx+=0.8*lastspeed*sin(lastrotation*M_PI/180);
    // cy+=0.8*lastspeed*cos(lastrotation*M_PI/180);

    // if (keypressed[0]||keypressed[4]){//up
    //     acceleration=-(maxacceleration/maxspeed*speed)+maxacceleration;
    // }
    // if (keypressed[1]||keypressed[5]){//down
    //     acceleration=(speed>0)?(-(maxacceleration/maxspeed*speed)-maxacceleration):(-(0.8*maxacceleration/maxspeed*speed)-0.8*maxacceleration);
    // }
    // if (keypressed[2]||keypressed[6]){//left
    //     setRotation(rotation()-control*sqrt(std::abs(speed)/maxspeed));
    // }
    // if (keypressed[3]||keypressed[7]){//right
    //     setRotation(rotation()+control*sqrt(std::abs(speed)/maxspeed));
    // }
    // if (keypressed[0]==0&&keypressed[4]==0&&keypressed[1]==0&&keypressed[5]==0){//no key pressed, taxiing
    //     acceleration=0;
    // }

    // //calculate effect of friction
    // if(speed>0)
    //     acceleration-=friction; else
    //     if (speed<0)
    //         acceleration+=friction;

    // speed+=acceleration;
    // if (speed>maxspeed) speed=maxspeed;
    // if (speed<-0.8*maxspeed) speed=-0.8*maxspeed;
    // cx+=speed*sin(rotation()*M_PI/180);
    // cy+=speed*cos(rotation()*M_PI/180);



    //v2 double point engine
    //suppose it's a rear wheel drive car;front wheels are steering wheels;back wheels are driving wheels;
    front=QPointF(cx+sin(rotation()*M_PI/180)*0.25*height,cy+cos(rotation()*M_PI/180)*0.25*height);
    back=QPointF(cx-sin(rotation()*M_PI/180)*0.25*height,cy-cos(rotation()*M_PI/180)*0.25*height);
    if (keypressed[0]||keypressed[4]){//up
        flag=1;
        front_friction=back_friction=QPointF(friction_rolling,friction_sliding);
    }
    if (keypressed[1]||keypressed[5]){//down
        flag=-0.8;
        front_friction=back_friction=QPointF(friction_rolling,friction_sliding);
    }
    if (keypressed[2]||keypressed[6]){//left
        steering-=control;
        if (steering<-maxsteering)
            steering=-maxsteering;
    }
    if (keypressed[3]||keypressed[7]){//right
        steering+=control;
        if (steering>maxsteering)
            steering=maxsteering;
    }
    //no left or right pressded, steer back to middle
    if ((!(keypressed[2]||keypressed[6]))&&(!(keypressed[3]||keypressed[7])))
//        if (steering!=0) steering=(steering>0)?(steering-2*control):(steering+2*control);
        steering=0;
    //no up/down pressed, taxiing
    if (keypressed[0]==0&&keypressed[4]==0&&keypressed[1]==0&&keypressed[5]==0){
        flag=0;
    }

    //steering and rotation vectors
    vector_steering = QPointF(sin((steering+rotation())*M_PI/180),cos((steering+rotation())*M_PI/180));
    vector_steering_normal = QPointF(cos((steering+rotation())*M_PI/180),-sin((steering+rotation())*M_PI/180));
    vector_rotation = QPointF(sin(rotation()*M_PI/180),cos(rotation()*M_PI/180));
    vector_rotation_normal = QPointF(cos(rotation()*M_PI/180),-sin(rotation()*M_PI/180));
    //back driving force
    //p=fv;suppose the motor always runs at max power, a~f~1/v;here simpliefied as a~f~-v;
    acceleration=flag*(-maxacceleration/sqrt(maxspeed)*sqrt(QPointF::dotProduct(back_speed,back_speed)) + maxacceleration);
    back_acceleration=acceleration*vector_rotation;

    //front friction
        //rolling friction
        cachef=QPointF::dotProduct(front_speed,vector_steering);
        //if speed and steer have "same" direction, frition to the opposite (*-1) of speed direction
        if (cachef>0.000000001) cachel=-1; else
            if (cachef<-0.000000001) cachel=1; else cachel=0;
        front_acceleration=cachel*front_friction.x()*vector_steering;//resolve in directions of steering (rolling) and its normal (sliding)
        //sliding friction
        cachef=QPointF::dotProduct(front_speed,vector_steering_normal);
        if (cachef>0.0001) cachel=-1; else
            if (cachef<-0.0001) cachel=1; else cachel=0;
        front_acceleration+=cachel*front_friction.y()*vector_steering_normal;

    //back friciton
        //rolling friction
        cachef=QPointF::dotProduct(back_speed,vector_rotation);
        //if speed and rotation have "same" direction, frition to the opposite (*-1) of speed direction
        if ((cachef>0.000000001)) cachel=-1; else
            if ((cachef<-0.000000001)) cachel=1; else cachel=0;
        back_acceleration+=cachel*back_friction.x()*vector_rotation;//resolve in directions of rotation (rolling) and its normal (sliding)
        //sliding friction
        cachef=QPointF::dotProduct(back_speed,vector_rotation_normal);
        if (cachef>0.000000001) cachel=-1; else
            if (cachef<-0.000000001) cachel=1; else cachel=0;
        back_acceleration+=0.5*cachel*back_friction.y()*vector_rotation_normal;

    //calculate reactive force
    reactiveforce=QPointF::dotProduct(front_acceleration,vector_rotation)*vector_rotation + QPointF::dotProduct(back_acceleration,vector_rotation)*vector_rotation;
    front_acceleration-=QPointF::dotProduct(front_acceleration,vector_rotation)*vector_rotation-reactiveforce;
    back_acceleration-=QPointF::dotProduct(back_acceleration,vector_rotation)*vector_rotation-reactiveforce;

    //calculate speed
    front_speed+=front_acceleration;
    back_speed+=back_acceleration;
    //reverse gear with half maxspeed, foward and taxing with maxspeed
    cachef=QPointF::dotProduct(front_speed,vector_steering);
    if (((cachef>0)&&(cachef>maxspeed))||((cachef<0)&&(cachef<-0.8*maxspeed))){
        cachef=(flag!=0)?(flag):(1);
        front_speed=front_speed/(QPointF::dotProduct(front_speed,vector_steering))*maxspeed*cachef;}
    cachef=QPointF::dotProduct(back_speed,vector_rotation);
    if (((cachef>0)&&(cachef>maxspeed))||((cachef<0)&&(cachef<-0.8*maxspeed))){
        cachef=(flag!=0)?(flag):(1);
        back_speed=back_speed/(QPointF::dotProduct(back_speed,vector_rotation))*maxspeed*cachef;}
    speed=(QPointF::dotProduct(back_speed,vector_rotation)+QPointF::dotProduct(front_speed,vector_steering))/2;

    //calculate position and direction
    front+=front_speed;
    back+=back_speed;
    cx=(front.x()+back.x())/2;
    cy=(front.y()+back.y())/2;
    setRotation(90-atan2(front.y()-back.y(),front.x()-back.x())/M_PI*180);//rotation() is clockwise from (0,1), angle in math is anticlockwise from (1,0)

    QList<QGraphicsItem *> colliding_items_coin = collidingItems();

    for (int i=0, n=colliding_items_coin.size(); i<n; ++i){
        if (typeid(*(colliding_items_coin[i])) == typeid(Obstacle)){

              scene()->removeItem(colliding_items_coin[i]);
              collectedCoins += 10;                         // every coin is worth 10
              delete colliding_items_coin[i];
              qDebug()<<"collected:" << collectedCoins;
              return;

                }
            }


}

void Car::showing()
{
    setPos(cx,-cy);
//    qDebug()<<" "<<steering<<" "<<rotation()<<" "<<steering+rotation();
//    qDebug()<<acceleration<<" "<<sqrt(QPointF::dotProduct(cache,cache))<<" "<<pos()<<" "<<front<<" "<<back<<" "<<sqrt(QPointF::dotProduct((front-back,front-back),(front-back,front-back)));
//    qDebug()<<vector_steering<<" "<<vector_steering_normal<<" "<<vector_rotation<<" "<<vector_rotation_normal;
//    qDebug()<<front_acceleration<<" "<<front_friction<<" "<<front_speed<<" "<<sqrt(QPointF::dotProduct(front_speed,front_speed));
//    qDebug()<<back_acceleration<<" "<<back_friction<<" "<<back_speed<<" "<<sqrt(QPointF::dotProduct(back_speed,back_speed));

}

double Car::getRunningtime() const
{
    return runningtime/1000.0;
}

void Car::setRunningtime(double value)
{
    runningtime = value;
}

void Car::rebounce()
{
//    cachef=sqrt(QPointF::dotProduct(front_speed,front_speed));
//    if (std::abs(cachef)<=0.1)front_speed=front_speed/cachef*-0.1;
//    else if (std::abs(cachef)<=0.2)front_speed=front_speed/cachef*-0.2;
//    else if (std::abs(cachef)<=0.3)front_speed=front_speed/cachef*-0.3;
//    else front_speed=front_speed/cachef*-0.4;
//    cachef=sqrt(QPointF::dotProduct(back_speed,back_speed));
//    if (std::abs(cachef)<=0.1)back_speed=back_speed/cachef*-0.1;
//    else if (std::abs(cachef)<=0.2)back_speed=back_speed/cachef*-0.2;
//    else if (std::abs(cachef)<=0.3)back_speed=back_speed/cachef*-0.3;
//    else back_speed=back_speed/cachef*-0.4;
    front_speed=front_speed/sqrt(QPointF::dotProduct(front_speed,front_speed))*-0.2;
    back_speed=back_speed/sqrt(QPointF::dotProduct(back_speed,back_speed))*-0.2;
}

void Car::setGamestatus(int value)
{
    gamestatus = value;
}

double Car::getSpeed() const
{
    return speed*600;
}

void Car::setControl(double value)
{
    control = value;
}

void Car::setMaxacceleration(double value)
{
    maxacceleration = value;
}

void Car::setMaxspeed(double value)
{
    maxspeed = value;
}

void Car::setFriction(double value)
{
    friction_sliding = value;
    friction_rolling = friction_sliding / 10;
}

void Car::setColor(const QString &value)
{
    color = value;
}
