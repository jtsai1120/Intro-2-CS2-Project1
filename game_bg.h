#ifndef GAME_BG_H
#define GAME_BG_H

#include "QGraphicsPixmapItem"
#include "QPixmap"

class Game_bg {
    public:
        Game_bg();
        QGraphicsPixmapItem *game_bg_item;
    private:
        QPixmap game_bg;

};

#endif // GAME_BG_H
