#ifndef SUPER_MUSHROOM_H
#define SUPER_MUSHROOM_H
#include <QGraphicsPixmapItem>
#include <QPixmap>

class Super_mushroom{
public:
    Super_mushroom();
    QGraphicsPixmapItem *super_mushroom_item;

    void set_xy(int new_x, int new_y);
    void move(int dx);


    static const int super_mushroom_height = 50;
    static const int super_mushroom_width = 50;
private:
    QPixmap super_mushroom_pic;

    int x, y;
    bool opened;

};


#endif // SUPER_MUSHROOM_H
