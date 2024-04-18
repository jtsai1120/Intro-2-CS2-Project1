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
    void move(int dx);
    void crack();//撞擊反應

    static const int broken_brick_height = 50;
    static const int broken_brick_width = 50;
private:
    QPixmap broken_brick_pic;
    int x, y;


};

#endif // BROKEN_BRICK_H
