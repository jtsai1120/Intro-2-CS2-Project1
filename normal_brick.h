#ifndef NORMAL_BRICK_H
#define NORMAL_BRICK_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Normal_brick{
public:
    Normal_brick();
    QGraphicsPixmapItem *normal_brick_item;

    void set_xy(int new_x, int new_y);
    void move(int dx);
    void crack(double dy);//撞擊反應

    static const int normal_brick_height = 50;
    static const int normal_brick_width = 50;
private:
    QPixmap normal_brick_pic;
    int x, y;

};

#endif // NORMAL_BRICK_H
