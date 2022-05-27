#ifndef FIELD_H
#define FIELD_H

#include <QImage>
#include <QVector>

class Field
{
public:
    Field();
    ~Field();

    void draw(QPainter& painter);

    void set_width(int width);
    void set_height(int height);
    int get_width() const;
    int get_height() const;

    void set_x(int x);
    void set_y(int y);
    int get_x() const;
    int get_y() const;



private:
    int x;
    int y;
    int width;
    int height;



};

#endif // FIELD_H
