#ifndef INVISIBLE_BRICK_H
#define INVISIBLE_BRICK_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Invisible_brick
{
public:
    Invisible_brick();
    QGraphicsPixmapItem *invisible_brick_item;

    void set_xy(int new_x, int new_y);
    void move(int dx);

    static const int invisible_brick_height = 50;
    static const int invisible_brick_width = 50;

private:
    QPixmap invisible_brick_pic;
    int x, y;

};

#endif // INVISIBLE_BRICK_H
