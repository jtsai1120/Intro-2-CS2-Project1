#include "game_bg1.h"

Game_bg1::Game_bg1() {
    game_bg1.load(":/Dataset/image/background.png");
    game_bg1 = game_bg1.scaled(1400, 618, Qt::IgnoreAspectRatio);
    game_bg1_item = new QGraphicsPixmapItem(game_bg1);
    x = 1400;
    y = 0;
    game_bg1_item->setPos(x, y);
}

void Game_bg1::move(int dx, int dy) {
    x += dx;
    y += dy;
    game_bg1_item->setPos(x, y);
}
