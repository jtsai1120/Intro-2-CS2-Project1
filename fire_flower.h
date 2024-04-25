#ifndef FIRE_FLOWER_H
#define FIRE_FLOWER_H

#include <QGraphicsPixmapItem>
#include <QPixmap>


class Fire_flower
{
public:
    Fire_flower();
    QGraphicsPixmapItem *fire_flower_item;

    void set_xy(int new_x, int new_y);
    void move(int dx);
    void used();
    void reset();
    void show();

    int posx,posy;
    bool opened = false;

    static const int fire_flower_height = 50;
    static const int fire_flower_width = 50;

private:
    QPixmap fire_flower_pic;
    int x, y;


};

#endif // FRIE_FLOWER_H
