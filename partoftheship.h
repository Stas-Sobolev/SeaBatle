#ifndef PARTOFTHESHIP_H
#define PARTOFTHESHIP_H

#include "object.h"
#include <QPainter>
#include <QGraphicsItem>
#include <QVector>
#include <QPoint>

class Ship;

class PartOfTheShip
{
public:
    PartOfTheShip(const QPoint& coord, Ship* Ship,bool hit = false, bool head = false);
    PartOfTheShip(int x, int y, Ship* ship, bool hit = false, bool head = false);
    PartOfTheShip();
    ~PartOfTheShip();

    //setters & getters
    const QPoint& get_coordinate()const;
    Ship* get_ship() const;
    bool is_hit() const;
    bool is_head() const;

    void set_point(const QPoint& point);
    void set_ship(Ship* ship);
    void set_hit();
    void set_head();


    //отрисовка ячейки
    void draw(QPainter* painter, const QVector<PartOfTheShip*>& existing_parts, qreal cell_size);

    bool is_lonely(const QVector<PartOfTheShip*>& all_parts, PartOfTheShip* part);
private:

    //координаты
    QPoint coordinate;
    //есть пробитие?
    bool hit;
    //это голова?
    bool head;
    //корабль
    Ship* ship;




};

#endif // PARTOFTHESHIP_H
