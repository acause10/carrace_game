#include "Outterbounds.h"
#include <QTimer>
#include <QDebug>
#include <car.h>

Outterbounds::Outterbounds(): QGraphicsPolygonItem()
{
    // shaping polygons
    QVector<QPointF> points_big_polygon;
    points_big_polygon << QPointF(-0.2,0) << QPointF(19.7,0) << QPointF(19.7,18.5) << QPointF(16.6,18.5) << QPointF(16.6,18.1) << QPointF(19.3,15.5)
                   << QPointF(19.3,3.25) << QPointF(16.6,0.5) << QPointF(2.9,0.5) << QPointF(0.18,3.25) << QPointF(0.18,15.5) << QPointF(2.9,18.1)
                       << QPointF(2.9,18.5) << QPointF(-0.2,18.5);

    QVector<QPointF> points_small_polygon;
    points_small_polygon << QPointF(2.9,18.05) << QPointF(16.6,18.05) << QPointF(16.6,18.5) << QPointF(2.9,18.5);


    // scaling polygon to be in proportion with route
    int scale = 40;
        for (size_t i=0, n = points_big_polygon.size(); i < n; i++){
            points_big_polygon[i] *= scale;
        }
        for (size_t i=0, n = points_small_polygon.size(); i < n; i++){
            points_small_polygon[i] *= scale;
        }

    // creating polygon out of defined points
    QPolygonF big_poly(points_big_polygon);
    QPolygonF small_poly(points_small_polygon);

    // create qgraphpolyitem
    bigger_poly = new QGraphicsPolygonItem(big_poly,this);
    bigger_poly->setPos(10,10);
    bigger_poly->setOpacity(0);

    smaller_poly = new QGraphicsPolygonItem(small_poly,this);
    smaller_poly->setPos(10,10);
    smaller_poly->setOpacity(0);

    // timer to check collisions with small and big polygon
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(outOfBoundsBig()));
    connect(timer,SIGNAL(timeout()),this,SLOT(outOfBoundsSmall()));

    timer->start(1);
}

void Outterbounds::setTheCar(Car *value)
{
    theCar = value;
}

void Outterbounds::outOfBoundsSmall()
{
    // checking collisions, raising flag if the items collide
    QList<QGraphicsItem *> colliding_with_outter = smaller_poly->collidingItems();
    bool flag = false;

        for (int i=0, n=colliding_with_outter.size(); i<n; ++i){
            if (typeid(*(colliding_with_outter[i])) == typeid(Car)){

                flag = true;
            }
        }

        if (!flag) {smallcanrebounce=true;}
        if (flag && smallcanrebounce){theCar->rebounce();smallcanrebounce=false;}


}

void Outterbounds::outOfBoundsBig()
{
    // checking collisions, same idea like for smaller polygon
    QList<QGraphicsItem *> colliding_with_outter = bigger_poly->collidingItems();
    bool flag = false;

        for (int i=0, n=colliding_with_outter.size(); i<n; ++i){
            if (typeid(*(colliding_with_outter[i])) == typeid(Car)){

                flag = true;
            }
        }

        if (!flag) {bigcanrebounce=true;}
        if (flag && bigcanrebounce){theCar->rebounce();bigcanrebounce=false;}

}
