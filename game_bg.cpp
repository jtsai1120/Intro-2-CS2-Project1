#include "game_bg.h"

Game_bg::Game_bg() {
    game_bg.load(":/Dataset/image/background.png");
    game_bg = game_bg.scaled(1400, 618, Qt::IgnoreAspectRatio);
    game_bg_item = new QGraphicsPixmapItem(game_bg);
    x = 0;
    y = 0;
    game_bg_item->setPos(x, y);
}

void Game_bg::set(int bg_count) {
    x = 0 + bg_count * 1400;
    y = 0;
    game_bg_item->setPos(x, y);
}


void Game_bg::move(int dx, int dy) {
    x += dx;
    y += dy;
    game_bg_item->setPos(x, y);
}
