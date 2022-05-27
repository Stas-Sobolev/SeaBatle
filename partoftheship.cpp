#include "partoftheship.h"



PartOfTheShip::PartOfTheShip(const QPoint &coord, Ship *ship, bool hit, bool head):coordinate(coord),ship(ship),hit(hit),head(head)
{

}

PartOfTheShip::PartOfTheShip(qreal x, qreal y, Ship *ship, bool hit, bool head):PartOfTheShip(QPoint(x,y),ship,hit,head)
{

}

PartOfTheShip::~PartOfTheShip()
{
    delete ship;
}
