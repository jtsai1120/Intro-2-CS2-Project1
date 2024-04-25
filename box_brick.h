#ifndef BOX_BRICK_H
#define BOX_BRICK_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <coin.h>


class Box_brick
{
public:
    Box_brick();
    QGraphicsPixmapItem *box_brick_item;

    void set_xy(int new_x, int new_y);
    void move(int dx);
    void crack();//撞擊反應
    void reset();
    std::vector<Coin*> coins;

    //Super_mushroom super_mushroom;

    static const int box_brick_height = 50;
    static const int box_brick_width = 50;

    int x_corresonding;
    int y_corresponding;
private:
    QPixmap box_brick_pic;
    QPixmap stone_brick_pic;
    int x, y;
    bool opened;

};

#endif // BOX_BRICK_H
