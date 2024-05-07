#ifndef BROKEN_BRICK_H
#define BROKEN_BRICK_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Broken_brick
{
public:
    Broken_brick();
    QGraphicsPixmapItem *broken_brick_item;

    void set_xy(int new_x, int new_y);
    void move();
    void crack();//撞擊反應
    void reset(int new_x, int new_y);

    static const int broken_brick_height = 50;
    static const int broken_brick_width = 50;
    int init_y;

    int dx;
    double dy;
    bool broken;

private:
    QPixmap broken_brick_pic;
    int x;
    double y;
    const double vy0 = -2;
    const double ay = 0.15;


};

#endif // BROKEN_BRICK_H
