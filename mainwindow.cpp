#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRect>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    background = QImage();
    background.load("D://Projects//seaBatle//images//background.png");
    background = background.scaled(background.width()*2,background.height()*2);
    this->setFixedSize(background.width(),background.height());
    field_1=new Field;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage((this->width()-background.width())/2,(this->height()-background.height())/2,background);
    painter.end();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<event->x()<<event->y();
}


MainWindow::~MainWindow()
{
    delete ui;

}

