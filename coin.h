#ifndef COIN_H
#define COIN_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Coin {
    public:
        Coin();
        ~Coin();
        QGraphicsPixmapItem *coin_item;

        static const int coin_width = 50;
        static const int coin_height = 50;

        void set_xy(int new_x, int new_y);
        void move();
        void fly(int new_x, int new_y);//射出金幣
        double y; int init_y;

        int dx;

        bool flying = false;

    private:
        QPixmap coin_pic;
        int x; double dy;
        const double vy0 = -7;
        const double ay = 0.15;
};

#endif // COIN_H
