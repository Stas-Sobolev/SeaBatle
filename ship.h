#ifndef SHIP_H
#define SHIP_H
#include "partoftheship.h"
#include <QVector>
class Field;

class Ship
{
public:
    enum orientation
    {
       HORIZONTAL,VERTICAL
    };
    Ship(Field* field,unsigned int number_part,const QVector<PartOfTheShip*>& parts={},orientation orient = HORIZONTAL);
    Ship(Field* field = nullptr);
    ~Ship();


    //setters
    void set_number_of_part(unsigned int num);
    void set_change_put(bool);
    void set_parts(const QVector<PartOfTheShip*>& parts);
    void add_part(PartOfTheShip* part);
    void dead_ship();
    void set_field(Field* field);
    //getters

    Field *get_field()const;
    const QPoint &get_coordinate_head()const;
    const QVector<PartOfTheShip *> &get_parts() const;
    int get_num_part()const;
    orientation get_orientation()const;
    bool get_state_put()const;
    //Рисование корабля
    void draw_ship(QPainter* painter);

    //Проверка на возможность постановки корабля
    bool ship_dont_put();

    void change_orient(orientation _orient);

    void turnt_ship();

    bool is_alive()const;
private:
    //количесвто палуб у корабля
    int number_of_part;
    //Можно ли поставить корабль
    bool state_put;
    //Палубы корабля отдельно
    QVector<PartOfTheShip*> parts;
    //жив ли корабль
    bool alive;
    //Поле,которому принадлежит корабль
    Field* field;
    //ориентация корабля
    orientation orient;



};

#endif // SHIP_H
