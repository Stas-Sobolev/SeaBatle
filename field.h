#ifndef FIELD_H
#define FIELD_H

#include<QGraphicsItem>
#include <QImage>
#include <QMouseEvent>
#include <QGraphicsEllipseItem>
#include "ship.h"

class MainWindow;
class Ship;
class Field : public QGraphicsItem
{
public:
    enum state_field
    {
        PLACEMENT,ACTIVE,NOTACTIVE
    };

    Field(qreal cell_size,const QPoint& field_size,state_field state,MainWindow* parent);
    ~Field() override;

    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget* widget) override;

    void add_ship(const QPoint& point, int num_parts, Ship::orientation = Ship::HORIZONTAL );

    void initial_ships();

    QPoint toGameFieldSpace(const QPointF &sceneSpacePoint);

    const QVector<Ship*>& get_ships() const;

    void move_ship(Ship* ship,const QPoint& new_position, PartOfTheShip* captured_part);

    Ship* get_captured_ship() const;

    PartOfTheShip* get_captured_part() const;

    void set_captured_ship(Ship* ship);

    void set_captured_part(PartOfTheShip* part);

    void add_part(PartOfTheShip* part);

    const QVector<PartOfTheShip*>& get_all_parts() const;

    bool all_ships_standing() const;

    void set_state(state_field _state);

    state_field get_state() const;

    bool shot(const QPoint& point);

    void add_miss(const QPoint& point);
private:
    //корабли, принадлежащие этому полю
    QVector<Ship*> ships;
    //состояние поля
    state_field state;
    //"родитель" поля (не наследование!)
    MainWindow* parent;
    //размер ячейки
    qreal cell_size;
    //размер поля
    QPoint field_size;
    //схваченный корабль
    Ship* captured_ship;
    //схваченная часть корабля
    PartOfTheShip* captured_part;
    //все кусочки кораблей
    QVector<PartOfTheShip*> all_parts;
    //промахи по полю
    QVector<QPoint> misses;

    void ship_dead(Ship* ship);
public:
    QRectF boundingRect() const;
};

#endif // FIELD_H
