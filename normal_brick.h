#ifndef NORMAL_BRICK_H
#define NORMAL_BRICK_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <coin.h>

class Normal_brick{
public:
    Normal_brick();
    QGraphicsPixmapItem *normal_brick_item;

    void set_xy(int new_x, int new_y);
    void move();
    void crack();//撞擊反應
    void reset();

    static const int normal_brick_height = 50;
    static const int normal_brick_width = 50;
    int init_y;

    std::vector<Coin*> coins;

    int dx;
    double dy;

    bool cracked = false;
    int no_more_coins = -1;

private:
    QPixmap normal_brick_pic;
    QPixmap stone_brick_pic;

    int x;
    double y;
    const double vy0 = -2;
    const double ay = 0.15;

};

#endif // NORMAL_BRICK_H
