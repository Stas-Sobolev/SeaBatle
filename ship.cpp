#include "ship.h"



ship::ship(Field *field, unsigned int number_part, const QVector<PartOfTheShip *> &parts): field(field),number_of_part(number_part),parts(parts)
{
    alive=true;
    dont_put=false;
}

ship::ship(Field *field):ship(field,0,{})
{

}

ship::~ship()
{

}

void ship::set_number_of_part(unsigned int num)
{
    number_of_part=num;
}

void ship::set_parts(const QVector<PartOfTheShip *> &parts)
{
    this->parts=parts;
}

void ship::add_part(PartOfTheShip *part)
{
    this->parts.push_back(part);
}

void ship::set_field(Field *field)
{
    this->field=field;
}

Field *ship::get_field() const
{
    return field;
}

void ship::set_change_put(bool state)
{
    this->dont_put=state;
}

