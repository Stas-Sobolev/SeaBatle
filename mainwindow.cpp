#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRect>
#include<QDebug>
#include <QGraphicsItem>
#include <QPushButton>
#include <QGraphicsScene>
MainWindow::MainWindow(QGraphicsScene* scene)
    : QGraphicsView(scene)
{
    /*background = QImage();
    background.load("D://Projects//seaBatle//images//background.png");
    background = background.scaled(background.width()*2,background.height()*2);
    this->setFixedSize(background.width(),background.height());*/
    this->setFixedSize(scene->width()+20,scene->height()+20);
    field_1=new Field(30.0,{10,10},Field::PLACEMENT,this);
    field_1->initial_ships();
    field_1->setPos(0,30);
    this->scene()->addItem(field_1);

    //this->scene()->addText("hello");
    field_2=new Field(30.0,{10,10},Field::PLACEMENT,this);

    field_2->initial_ships();
    //this->scene()->addItem(field_2);


    ready = new QPushButton("Закончить расстановку",this);
    ready->setGeometry(450,100,150,40);

    connect (ready,&QPushButton::clicked,this,&MainWindow::finished_placement);

    player = new QLabel(this);
    player->setGeometry(450,50,150,40);
    player->setText("Player 1");
    player->setFont(QFont("Arial",20));


}


MainWindow::~MainWindow()
{


}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint point;
    //первое поле в режиме расстановки кораблей
    if(field_1->get_state()==Field::PLACEMENT)
    {
        point = field_1->toGameFieldSpace(event->pos());
        //point-={12,0};
        if(event->button()==Qt::LeftButton)
        {
            bool shvatil= false;
            for(auto ship : field_1->get_ships())
            {
                for(auto part : ship->get_parts())
                {

                    if(part->get_coordinate()==point)
                    {
                        shvatil=true;
                        field_1->set_captured_ship(ship);
                        field_1->set_captured_part(part);
                        break;
                    }
                }
                if(shvatil)
                    break;
            }
        }
        else
        {
            if(!(field_1->get_captured_ship()))
            {
                for(auto ship : field_1->get_ships())
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
    }
    //второе поле в процессе расстановки кораблей
    else if(field_2->get_state()==Field::PLACEMENT)
    {
        point = field_2->toGameFieldSpace(event->pos());
        //point-={12,0};
        //нажатие ЛКМ нужно для фиксации кораблся для перетаскивания
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
        //нажатие ПКМ нужно для поворота кораблся
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
    }
    //выстрелы!!!!PIU PIU
    else
    {
        //стреляет первый игрок
        if(field_1->get_state()==Field::ACTIVE)
        {
            point = field_2->toGameFieldSpace(event->pos());
            point-={12,0};
            if(point.x()>=0 && point.x()<=9 && point.y()>=0 && point.y()<=9)
                if(!field_2->shot(point))
                {
                    field_1->set_state(Field::NOTACTIVE);
                    field_2->set_state(Field::ACTIVE);
                    player->setText("Ходит второй игрок");
                }
        }
        else
        {
            //стреляет второй игрок
            point = field_1->toGameFieldSpace(event->pos());
            if(point.x()>=0 && point.x()<=9 && point.y()>=0 && point.y()<=9)
                if(!field_1->shot(point))
                {
                    field_1->set_state(Field::ACTIVE);
                    field_2->set_state(Field::NOTACTIVE);
                    player->setText("Ходит первый игрок");
                }
        }

    }


    //обнова полей и сцены
    field_1->update();
    field_2->update();
    scene()->update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(field_1->get_state()==Field::PLACEMENT)
    {
        if(field_1->get_captured_ship()!=nullptr)
        {
            QPoint new_point = field_1->toGameFieldSpace(event->pos());
            //new_point-={12,0};
            if(field_1->get_captured_part()->get_coordinate()!=new_point)
                field_1->move_ship(field_1->get_captured_ship(),new_point,field_1->get_captured_part());
            field_1->update();
            field_2->update();
            scene()->update();
            update();
        }
    }
    else if(field_2->get_state()==Field::PLACEMENT)
    {
         if(field_2->get_captured_ship()!=nullptr)
         {
             QPoint new_point = field_2->toGameFieldSpace(event->pos());

             //new_point-={12,0};
             if(field_2->get_captured_part()->get_coordinate()!=new_point)
                 field_2->move_ship(field_2->get_captured_ship(),new_point,field_2->get_captured_part());
             field_1->update();
             field_2->update();
             scene()->update();
             update();
         }
     }
    //qDebug()<<new_point;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    field_1->set_captured_ship(nullptr);
    field_1->set_captured_part(nullptr);

}

void MainWindow::finished_placement()
{
    if(field_1->get_state()==Field::PLACEMENT)
    {
        if(!field_1->all_ships_standing())
        {
            field_1->set_state(Field::ACTIVE);
            this->scene()->removeItem(field_1);
            field_2->setPos(0,30);
            this->scene()->addItem(field_2);

            player->setText("Player 2");

        }

    }
    else if(field_2->get_state()==Field::PLACEMENT)
    {
        if(!field_2->all_ships_standing())
        {
            field_2->set_state(Field::NOTACTIVE);
            field_2->setPos(360,30);
            scene()->addItem(field_1);
            field_1->setPos(0,30);
            //player->deleteLater();
            ready->deleteLater();
            player->setText("Ходит первый игрок");
            player->setGeometry(200,10,400,30);
            scene()->update();
            update();

            //delete player;
            delete ready;
        }
    }
    scene()->update();
}


