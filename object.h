#ifndef OBJECT_H
#define OBJECT_H
#include <QPair>

class object
{
public:
    object();
    object(int x, int y, int width = 10, int height = 10 );

    virtual ~object() = 0 ;

    void set_x(int x);
    void set_y(int y);
    void set_coordinate(int x, int y);
    void set_width(int width);
    void set_height(int height);

    int get_x() const;
    int get_y() const;
    QPair<int,int> get_coordinate() const;
    int get_width() const;
    int get_height() const;



private:
    int x;
    int y;

    int width;
    int height;

    qreal cell_size;
};

#endif // OBJECT_H
