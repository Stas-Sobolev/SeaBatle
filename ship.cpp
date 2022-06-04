#include "ship.h"
#include <QDebug>
#include <field.h>
//конструкторы

Ship::Ship(Field *field, unsigned int number_part, const QVector<PartOfTheShip *> &parts, Ship::orientation orient):
    field(field),number_of_part(number_part),parts(parts),orient(orient)
{
    alive=true;
    state_put=false;
}

Ship::Ship(Field *field):Ship(field,0,{})
{

}

Ship::~Ship()
{

}
//устанавливает количество палуб
void Ship::set_number_of_part(unsigned int num)
{
    number_of_part=num;
}
//устанавливает палубы
void Ship::set_parts(const QVector<PartOfTheShip *> &parts)
{
    this->parts=parts;
}
//добавляет палубу к кораблю
void Ship::add_part(PartOfTheShip *part)
{
    this->parts.push_back(part);
}

void Ship::dead_ship()
{

}
//устанавливает поле, которому принадлежит корабль
void Ship::set_field(Field *field)
{
    this->field=field;
}
//возвращает поле
Field *Ship::get_field() const
{
    return field;
}

const QPoint &Ship::get_coordinate_head() const
{

}

const QVector<PartOfTheShip *> &Ship::get_parts() const
{
    return parts;
}

int Ship::get_num_part() const
{
    return number_of_part;
}

Ship::orientation Ship::get_orientation() const
{
    return orient;
}

bool Ship::get_state_put() const
{
    return state_put;
}

void Ship::draw_ship(QPainter* painter)
{
    if(field->get_state()==Field::PLACEMENT)
        for(auto part : parts)
            part->draw(painter,field->get_all_parts(),30);
    else
        for(auto part : parts)
            if(part->is_hit())
                part->draw(painter,field->get_all_parts(),30);
}

bool Ship::ship_dont_put()
{

}

void Ship::change_orient(Ship::orientation _orient)
{
    orient=_orient;
}

void Ship::turnt_ship()
{
    int i=0;
    if(orient==HORIZONTAL)
    {
        orient=VERTICAL;

        for(auto part:parts)
        {
            part->set_point(part->get_coordinate() + QPoint(-i,i));
            i++;
        }
    }
    else
    {
        orient=HORIZONTAL;
        for(auto part:parts)
        {
            part->set_point(part->get_coordinate() + QPoint(i,-i));
            i++;
        }
    }
}

bool Ship::is_alive() const
{
    int num_wounded=0;
    for(auto part:parts)
        if(part->is_hit())
            num_wounded++;

    if(num_wounded==number_of_part)
        return false;
    return true;
}

//меняет состояние возможности постановки корабля
void Ship::set_change_put(bool state)
{
    this->state_put=state;
}

