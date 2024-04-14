#include "Innerbounds.h"
#include "car.h"
#include <QGraphicsPolygonItem>
#include <QTimer>
#include <QDebug>
#include "GameScene.h"

Innerbounds::Innerbounds(): QGraphicsPolygonItem()
{
    // creating vector for inner polygon
    QVector<QPointF> points_inn;

    points_inn << QPointF(2.4,0.4) << QPointF(16,0.4) << QPointF(18.4,2.8) << QPointF(18.4,14.7) << QPointF(16,17) << QPointF(2.4,17)
               << QPointF(0,14.7) << QPointF(0,2.8);

    // scaling points
    int scale_inner = 29;
    for (size_t i=0, n = points_inn.size(); i < n; i++){
        points_inn[i] *= scale_inner;
    }

    // create polygons from points
    QPolygonF inn_poly(points_inn);

    // create QGraphicsPolygonItem
    inner_poly = new QGraphicsPolygonItem(inn_poly,this);
    inner_poly->setPos(135,128);
    inner_poly->setOpacity(0);

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(checkCollision()));

    timer->start(1);

}

void Innerbounds::setTheCar(Car *value)
{
    theCar = value;
}

void Innerbounds::checkCollision()
{

    // check collision between car and polygon to cause an elastic hit
    QList<QGraphicsItem *> colliding_with_inner = inner_poly->collidingItems();

    bool flag = false;

        for (int i=0, n=colliding_with_inner.size(); i<n; ++i){
            if (typeid(*(colliding_with_inner[i])) == typeid(Car)){

                flag = true;
            }
        }

        if (!flag) {canrebounce=true;}
        if (flag && canrebounce){theCar->rebounce();canrebounce=false;}

}
