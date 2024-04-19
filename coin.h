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
        void move(int dx, int dy);
        void fly();//射出金幣

    private:
        QPixmap coin_pic;
        int x, y;
};

#endif // COIN_H
