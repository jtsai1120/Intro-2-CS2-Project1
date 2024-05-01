#include "coin.h"
#include <QDebug>

Coin::Coin() {
    coin_pic.load(":/Dataset/image/item/coin.png");
    coin_item = new QGraphicsPixmapItem(coin_pic);
    dx = 0;
    dy = 0;
}

void Coin::set_xy(int new_x, int new_y) {
    x = new_x;
    y = new_y;
    coin_item->setPos(x, y);
}

void Coin::move() {
    x += dx;
    dx = 0;

    y += dy;
    if (y > init_y && flying) {
        y = 1000;
        flying = false;
        dy = 0;
        score->add_score(1);

        qDebug()<<"start";
    }
    else if (y < init_y){
        dy += ay;
    }
    else {
        dy = 0;
    }

    set_xy(x, y);
}

void Coin::fly(int new_x, int new_y){//獲得金幣的特效
    set_xy(new_x, new_y - 60);
    dy = vy0;
    init_y = new_y - 60;
    flying = true;
}
