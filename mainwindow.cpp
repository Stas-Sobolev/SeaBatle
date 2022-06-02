#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRect>
#include<QDebug>
#include <QGraphicsItem>
MainWindow::MainWindow(QGraphicsScene* scene)
    : QGraphicsView(scene)
{
    /*background = QImage();
    background.load("D://Projects//seaBatle//images//background.png");
    background = background.scaled(background.width()*2,background.height()*2);
    this->setFixedSize(background.width(),background.height());*/

    field_1=new Field(30.0,{10,10},Field::PLACEMENT,this);
    field_1->initial_ships();
    field_1->setPos(0,30);
    this->scene()->addItem(field_1);

    //this->scene()->addText("hello");
    field_2=new Field(30.0,{10,10},Field::PLACEMENT,this);
    field_2->setPos(360,30);
    field_2->initial_ships();
    this->scene()->addItem(field_2);
}


MainWindow::~MainWindow()
{


}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint point = field_2->toGameFieldSpace(event->pos());
    point-={12,0};
    if(event->button()==Qt::LeftButton)
    {
        bool shvatil= false;
        for(auto ship : field_2->get_ships())
        {
            for(auto part : ship->get_parts())
            {

                if(part->get_coordinate()==point)
                {
                    shvatil=true;
                    field_2->set_captured_ship(ship);
                    field_2->set_captured_part(part);
                    break;
                }
            }
            if(shvatil)
                break;
        }
    }
    else
    {
        if(!(field_2->get_captured_ship()))
        {
            for(auto ship : field_2->get_ships())
            {
                for(auto part : ship->get_parts())
                {

                    if(part->get_coordinate()==point)
                    {
                        //field_2->turning_the_ship(ship);
                        ship->turnt_ship();
                        break;
                    }
                }

            }
        }

    }
    field_1->update();
    field_2->update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(field_2->get_captured_ship()!=nullptr)
    {
        QPoint new_point = field_2->toGameFieldSpace(event->pos());
        new_point-={12,0};
        if(field_2->get_captured_part()->get_coordinate()!=new_point)
            field_2->move_ship(field_2->get_captured_ship(),new_point,field_2->get_captured_part());
        field_1->update();
        field_2->update();
    }

    //qDebug()<<new_point;

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    field_2->set_captured_ship(nullptr);
    field_2->set_captured_part(nullptr);
}


