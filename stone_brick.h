#ifndef STONE_BRICK_H
#define STONE_BRICK_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Stone_brick {
public:
    Stone_brick();
    QGraphicsPixmapItem *stone_brick_item;

    void set_xy(int new_x, int new_y);
    void move(int dx);

    static const int stone_brick_height = 50;
    static const int stone_brick_width = 50;

private:
    QPixmap stone_brick_pic;
    int x, y;
};

#endif // STONE_BRICK_H
