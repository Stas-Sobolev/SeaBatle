#include "partoftheship.h"
#include <QDebug>
#include "ship.h"

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
void PartOfTheShip::draw(QPainter *painter, const QVector<PartOfTheShip*>& existing_parts, qreal cell_size)
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


    qDebug()<<existing_parts.size();
    if(is_lonely(existing_parts,this))
    {
        painter->fillRect(A.x()+1,A.y()+1,cell_size-0.5,cell_size-0.5,QBrush(Qt::green));
        get_ship()->set_change_put(true);
    }
    else
    {
        painter->fillRect(A.x()+1,A.y()+1,cell_size-0.5,cell_size-0.5,QBrush(Qt::red));
        get_ship()->set_change_put(false);
    }

    if(this->is_hit())
    {
        painter->drawLine(A,C);
        painter->drawLine(B,D);
    }


}

bool PartOfTheShip::is_lonely(const QVector<PartOfTheShip *> &all_parts, PartOfTheShip* part_to_check)
{
    QVector<QPoint> delta {{0,1},{0,-1},{1,0},{-1,0},{1,1},{-1,-1},{1,-1},{-1,1}};

    for(auto part: all_parts)
    {
        for(auto d:delta)
        {
            if((QPoint(part_to_check->get_coordinate().x()+d.x(),part_to_check->get_coordinate().y()+d.y())==part->get_coordinate()
            && part_to_check->get_ship()!=part->get_ship()))
                return false;

            if(part_to_check->get_coordinate().x()<0 ||part_to_check->get_coordinate().x()>10)
                return false;
        }
    }
    return true;
}
