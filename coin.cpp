#include "coin.h"
#include <QDebug>

Coin::Coin() {
    coin_pic.load(":/Dataset/image/item/coin.png");
    coin_item = new QGraphicsPixmapItem(coin_pic);
}

void Coin::set_xy(int new_x, int new_y) {
    x = new_x;
    y = new_y;
    coin_item->setPos(x, y);
}

void Coin::move(int dx, int dy) {
    set_xy(x + dx, y + dy);
}
