#include "field.h"
#include <QPainter>
#include <QString>
#include <QRectF>
#include <QtMath>
#include <QDebug>
#include "mainwindow.h"

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
                painter->drawText(QRectF(j*cell_size,i*cell_size,cell_size,cell_size),static_cast<QString>(column_name[j-1]),QTextOption(Qt::AlignCenter));
            else if(i && !j)
                painter->drawText(QRectF(j*cell_size,i*cell_size,cell_size,cell_size),QString::number(i),QTextOption(Qt::AlignCenter));
            else if(i && j)
                painter->drawRect(static_cast<int>(j*cell_size),static_cast<int>(i*cell_size),cell_size,cell_size);
        }
    }
    //рисуем корабли, если состояние подготовки

    for(auto ship: ships)
    {
        ship->draw_ship(painter);
    }

    //рисуем промахи
    for(auto miss:misses)
    {
        painter->setBrush(Qt::blue);
        painter->drawEllipse((miss.x()+1)*cell_size+(cell_size-2*cell_size/3),
                             (miss.y()+1)*cell_size+(cell_size-2*cell_size/3),cell_size/3,cell_size/3);

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
//перевод координат сцены на координаты поля
QPoint Field::toGameFieldSpace(const QPointF &sceneSpacePoint) {
    return {
        qFloor(sceneSpacePoint.x() / cell_size -0.3) - 1,
        qFloor(sceneSpacePoint.y() / cell_size-0.3) - 2
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

bool Field::all_ships_standing() const
{
    for(auto ship: ships)
        if(!ship->get_state_put())
            return false;
    return true;
}

void Field::set_state(Field::state_field _state)
{
    state=_state;
}

Field::state_field Field::get_state() const
{
    return state;
}

bool Field::shot(const QPoint &point)
{
    for(auto part : all_parts)
        if(part->get_coordinate()==point)
        {
            part->set_hit();
            if(!part->get_ship()->is_alive())
                ship_dead(part->get_ship());
            return true;
        }
    add_miss(point);

}
//добавляет промахи
void Field::add_miss(const QPoint &point)
{
    misses.push_back(point);
}
//Обрабатывает смерть корабля(отрисовывет промахи вокруг него
void Field::ship_dead(Ship *ship)
{

    if(ship->get_orientation()==Ship::VERTICAL)
    {
        QVector<QPoint> delta{{1,1},{-1,1},{1,0},{-1,0},{1,-1},{-1,-1}};

        for(auto part : ship->get_parts())
            {
                for(auto d : delta)
                {
                    if((part->get_coordinate()+d).x()>=0 && (part->get_coordinate()+d).x()<=9
                            && (part->get_coordinate()+d).y()>=0 && (part->get_coordinate()+d).y()<=9)
                    add_miss(part->get_coordinate()+d);
                }
            }
        if(ship->get_parts()[0]->get_coordinate().y()>0)
            add_miss(ship->get_parts()[0]->get_coordinate()+QPoint(0,-1));

        if(ship->get_parts()[ship->get_num_part()-1]->get_coordinate().y()<9)
            add_miss(ship->get_parts()[ship->get_num_part()-1]->get_coordinate()+QPoint(0,1));
    }
    else
    {
        QVector<QPoint> delta{{1,1},{-1,1},{1,-1},{-1,-1},{0,1},{0,-1}};

        for(auto part : ship->get_parts())
            {
                for(auto d : delta)
                {
                    if((part->get_coordinate()+d).x()>=0 && (part->get_coordinate()+d).x()<=9
                            && (part->get_coordinate()+d).y()>=0 && (part->get_coordinate()+d).y()<=9)
                    add_miss(part->get_coordinate()+d);
                }
            }

        if(ship->get_parts()[0]->get_coordinate().x()>0)
            add_miss(ship->get_parts()[0]->get_coordinate()+QPoint(-1,0));

        if(ship->get_parts()[ship->get_num_part()-1]->get_coordinate().x()<9)
            add_miss(ship->get_parts()[ship->get_num_part()-1]->get_coordinate()+QPoint(1,0));
    }
}

QRectF Field::boundingRect() const
{

}


