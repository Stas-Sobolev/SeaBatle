#ifndef SHIP_H
#define SHIP_H
#include "partoftheship.h"

class ship
{
public:
    ship();
    ~ship();
    enum orientation
    {
       HORIZONTAL,VERTICAL
    } orientation=orientation::HORIZONTAL;

private:



};

#endif // SHIP_H
