#include "partoftheship.h"



PartOfTheShip::PartOfTheShip(const QPoint &coord, Ship *ship, bool hit, bool head):coordinate(coord),ship(ship),hit(hit),head(head)
{

}

PartOfTheShip::PartOfTheShip(int x, int y, Ship *ship, bool hit, bool head):PartOfTheShip(QPoint(x,y),ship,hit,head)
{

}

PartOfTheShip::PartOfTheShip():PartOfTheShip(0,0,nullptr,false,false)
{

}

PartOfTheShip::~PartOfTheShip()
{
    delete ship;
}

//getters
const QPoint &PartOfTheShip::get_coordinate() const
{
    return coordinate;
}

Ship *PartOfTheShip::get_ship() const
{
    return ship;
}

bool PartOfTheShip::is_hit() const
{
    return hit;
}

bool PartOfTheShip::is_head() const
{
    return head;
}
//setters
void PartOfTheShip::set_point(const QPoint &point)
{
    this->coordinate=point;
}

void PartOfTheShip::set_hit()
{
    this->hit=true;
}

void PartOfTheShip::set_head()
{
    this->head=true;
}

void PartOfTheShip::set_ship(Ship *ship)
{
    this->ship = ship;
}

//Рисует ячейку
void PartOfTheShip::draw(QPainter *painter, const QVector<PartOfTheShip *>& existing_parts, qreal cell_size)
{
    /* Координаты вершин ячейки
     * A-лев верхн
     * B-прав верхн
     * C-прав нижн
     * D-лев нижн
    */
    QPoint A(static_cast<int>((coordinate.x()+1)*cell_size),static_cast<int>((coordinate.y()+1)*cell_size));
    QPoint B(static_cast<int>((coordinate.x()+2)*cell_size),static_cast<int>((coordinate.y()+1)*cell_size));
    QPoint C(static_cast<int>((coordinate.x()+2)*cell_size),static_cast<int>((coordinate.y()+2)*cell_size));
    QPoint D(static_cast<int>((coordinate.x()+1)*cell_size),static_cast<int>((coordinate.y()+2)*cell_size));

    //СДЕЛАТЬ ПРОВЕРКУ НА КОРАБЛИ РЯДОМ
    //
    //
    painter->drawLine(A,B);
    painter->drawLine(B,C);
    painter->drawLine(C,D);
    painter->drawLine(D,A);

    painter->fillRect(A.x()+1,A.y()+1,cell_size-0.5,cell_size-0.5,QBrush(Qt::green));
    if(this->is_hit())
    {
        painter->drawLine(A,C);
        painter->drawLine(B,D);
    }

}
