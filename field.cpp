#include "field.h"
#include <QPainter>
Field::Field()
{
    x=0;
    y=0;

}

//setters and getters
int Field::get_y() const
{
    return y;
}

int Field::get_x() const
{
    return x;
}

void Field::set_height(int height)
{
    this->height=height;
}

void Field::set_x(int x)
{
    this->x=x;
}

void Field::set_y(int y)
{
    this->y=y;
}

void Field::set_width(int width)
{
    this->width=width;
}


void Field::draw(QPainter& painter)
{

}
