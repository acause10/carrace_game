#ifndef CAR_H
#define CAR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QFocusEvent>
#include <math.h>
#include <iostream>
#include <QPainter>
#include <QPixmap>
#include <UserProfile.h>

/// \brief The class for car
class Car: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Car();

    /// \brief constructor for car with 3 parameter for starting position, width, height
    /// \param [QPointF] p is the starting position on the QGraphicsscene
    /// \param [double] w is the width of car
    /// \param [double] h is the height of car
    Car(QPointF p,double w, double h, QString currentUsername = "");
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    /// \brief regain focus when losing focus
    void focusOutEvent(QFocusEvent *event);

    /// \brief returns the speed of car in km/h
    double getSpeed() const;
    void setOrigin(QPointF point);

    /// \brief set the color of car
    /// \param [QString] valur is the color from {"Black","Brown","Cyan","DarkGreen","DarkRed","Red"}
    void setColor(const QString &value);

    /// \brief set sliding friction (route relevant)
    /// \param [double] value is the friction to set
    /// \note default 0.001, do not excede 0.0015!
    void setFriction(double value);//set sliding friction (route relevant);

    /// \brief set maxspeed (pixel per millisecond)
    /// \param [double] value is the maxspeed to set
    void setMaxspeed(double value);
    void setMaxacceleration(double value);
    void setControl(double value);

    /// \brief set game status
    /// \param [int] value is the flag of game status to set {0==game not running (not started, paused or finished),1==press any key to start,2==game running}
    /// \note use combined with set Runningtime when needed!
    /// \note game (re)start: setgamestatus(1);setrunningtime(0);\n
    /// game pause: setgamestatus(0);\n
    /// game continue: setgamestatus(2);\n
    /// game finished: setgamestatus(0);getrunningtime();
    void setGamestatus(int value);

    /// \brief return runningtime (in seconds)
    double getRunningtime() const;

    /// \brief initialize runningtime (to 0) (in milliseconds)
    void setRunningtime(double value);

    /// \brief called when the car hit the bounds to rebounce
    void rebounce();

    ///
    /// \brief userprofile gives intersection from the application to the database
    ///
    /// should not be removed until the car gets deleted
    UserProfile * userprofile = new UserProfile;

    ///
    /// \brief publicCurrentUsername
    ///
    QString publicCurrentUsername;

    ///
    /// \brief collectedCoins
    ///
    int collectedCoins;

public slots:

    /// \brief calculte the new status of car 1000 times per second
    /// \note only when gamestatus==2
    void move();

    /// \brief update the newest status of car 100fps and show it on screen
    void showing();
private:
    /// \brief hash table key{up,down,left,right,w,s,a,d,space}
    /// \note keypressed[theKey]==0 when theKey is not pressed, ==1 when theKey is pressed
    bool keypressed[9]={0,0,0,0,0,0,0,0,0};

    /// \brief the flag of driving status {is reverse gear==-0.8,is foward gear==1,is neutral gear==0} default is neutral gear
    double flag=0;
    double maxspeed=0.3,maxacceleration=0.0006,speed=0,acceleration=0,steering=0,maxsteering=30,control=0.3;
    QPointF begin,front,front_speed=QPointF(0,0),front_acceleration,front_friction,back,back_speed=QPointF(0,0),back_acceleration,back_friction,reactiveforce;
    QPointF vector_rotation,vector_rotation_normal,vector_steering,vector_steering_normal;
    double cachef,cx,cy,width,height,friction_rolling=0.0001,friction_sliding=0.001;


    /// \brief the flag of game status to set {0==game not running (not started, paused or finished),1==press any key to start,2==game running}
    int gamestatus;
    int cachel,runningtime=0;
    QString color;
};

#endif // CAR_H
