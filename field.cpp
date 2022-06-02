#include "field.h"
#include <QPainter>
#include <QString>
#include <QRectF>
#include <QtMath>
#include <QDebug>

Field::Field(qreal cell_size, const QPoint &field_size, Field::state_field state, MainWindow *parent):QGraphicsItem(),
    cell_size(cell_size),field_size(field_size),state(state),parent(parent)
{
    captured_ship = nullptr;
    //this->setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
}

Field::~Field()
{

}

void Field::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::black);
    QString column_name="АБВГДЕЖЗИК";

    //рисуем поле
    for(int i=0;i<field_size.x()+1;i++)
    {
        for(int j=0;j<field_size.y()+1;j++)
        {
            if(!i && j)
                painter->drawText(QRectF(i*cell_size,j*cell_size,cell_size,cell_size),static_cast<QString>(column_name[j-1]),QTextOption(Qt::AlignCenter));
            else if(i && !j)
                painter->drawText(QRectF(i*cell_size,j*cell_size,cell_size,cell_size),QString::number(i),QTextOption(Qt::AlignCenter));
            else if(i && j)
                painter->drawRect(static_cast<int>(i*cell_size),static_cast<int>(j*cell_size),cell_size,cell_size);
        }
    }

    //рисуем корабли
    for(auto ship: ships)
    {
        ship->draw_ship(painter);
    }

}

void Field::add_ship(const QPoint& pos, int num_parts, Ship::orientation orient)
{
    Ship* _ship = new Ship();
    _ship->set_field(this);
    _ship->set_number_of_part(num_parts);
    _ship->change_orient(orient);
    for(int i=0;i<num_parts;i++)
    {
        PartOfTheShip* part = new PartOfTheShip();
        QPoint part_point = (_ship->get_orientation() == Ship::HORIZONTAL)?pos+QPoint(i,0):pos+QPoint(0,i);
        part->set_point(part_point);
        part->set_ship(_ship);
        if(!i)
            part->set_head();
        _ship->add_part(part);
        add_part(part);
    }
    ships.push_back(_ship);

}

void Field::initial_ships()
{
    add_ship({0,11},4);
    add_ship({0,13},3);
    add_ship({4,13},3);
    add_ship({0,15},2);
    add_ship({3,15},2);
    add_ship({6,15},2);
    add_ship({0,17},1);
    add_ship({2,17},1);
    add_ship({4,17},1);
    add_ship({6,17},1);
}

QPoint Field::toGameFieldSpace(const QPointF &sceneSpacePoint) {
    return {
        qFloor(sceneSpacePoint.x() / cell_size) - 1,
        qFloor(sceneSpacePoint.y() / cell_size) - 2
    };
}

const QVector<Ship *>& Field::get_ships() const
{
    return ships;
}

void Field::move_ship(Ship *ship, const QPoint &new_position, PartOfTheShip *captured_part)
{
    if(new_position!=captured_part->get_coordinate())
    {
        QPoint delta = new_position - captured_part->get_coordinate();
    for(auto part : ship->get_parts())
        part->set_point(part->get_coordinate()+delta);

    }
}

Ship *Field::get_captured_ship() const
{
    return captured_ship;
}

PartOfTheShip *Field::get_captured_part() const
{
    return captured_part;
}

void Field::set_captured_ship(Ship *ship)
{
    captured_ship=ship;
}

void Field::set_captured_part(PartOfTheShip *part)
{
    captured_part=part;
}

void Field::add_part(PartOfTheShip *part)
{
    all_parts.push_back(part);
}

const QVector<PartOfTheShip*> &Field::get_all_parts() const
{
    return all_parts;
}

QRectF Field::boundingRect() const
{

}


