#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QImage>
#include<QPainter>
#include <QPaintEvent>
#include <QGraphicsView>
#include <field.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QGraphicsView
{
    Q_OBJECT

public:
    MainWindow(QGraphicsScene* scene);
    ~MainWindow() override ;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
private:
    QImage background;
    Field* field_1;
    Field* field_2;
};
#endif // MAINWINDOW_H
