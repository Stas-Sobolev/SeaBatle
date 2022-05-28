#ifndef SHIP_H
#define SHIP_H
#include "partoftheship.h"
#include <QVector>
class Field;
class ship
{
public:
    ship(Field* field,unsigned int number_part,const QVector<PartOfTheShip*>& parts={});
    ship(Field* field = nullptr);
    ~ship();
    enum orientation
    {
       HORIZONTAL,VERTICAL
    } orientation=orientation::HORIZONTAL;

    //setters
    void set_number_of_part(unsigned int num);
    void set_change_put(bool);
    void set_parts(const QVector<PartOfTheShip*>& parts);
    void add_part(PartOfTheShip* part);
    void dead_ship();
    void set_field(Field* field);
    //getters

    Field *get_field()const;
    const QPoint& get_coordinate_head()const;
    const QVector<PartOfTheShip*>& get_parts() const;
    unsigned int get_num_part()const;

    //Рисование корабля
    void draw_ship();

    //Проверка на возможность постановки корабля
    bool ship_dont_put();


private:
    //количесвто палуб у корабля
    unsigned int number_of_part;
    //Можно ли поставить корабль
    bool dont_put;
    //Палубы корабля отдельно
    QVector<PartOfTheShip*> parts;
    //жив ли корабль
    bool alive;
    //Поле,которому принадлежит корабль
    Field* field;


};

#endif // SHIP_H
