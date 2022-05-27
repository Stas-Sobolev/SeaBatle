#include "object.h"

object::object(int x, int y, int width, int height):x(x),y(y),width(width),height(height)
{
}

object::~object()
{

}

object::object():object(0,0)
{
}
//setters & getters
void object::set_x(int x)
{
    this->x = x;
}

void object::set_y(int y)
{
    this->y = y;
}

void object::set_coordinate(int x, int y)
{
    this->x=x;
    this->y=y;
}

void object::set_width(int width)
{
    this->width=width;
}

void object::set_height(int height)
{
    this->height = height;
}

int object::get_y() const
{
    return y;
}

int object::get_x() const
{
    return x;
}

QPair<int, int> object::get_coordinate() const
{
    return {x,y};
}

int object::get_width() const
{
    return width;
}

int object::get_height() const
{
    return height;
}
