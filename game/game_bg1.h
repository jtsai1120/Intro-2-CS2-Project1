#ifndef GAME_BG1_H
#define GAME_BG1_H

#include "QGraphicsPixmapItem"
#include "QPixmap"

class Game_bg1{
    public:
        Game_bg1();
        QGraphicsPixmapItem *game_bg1_item;
        void move(int dx, int dy);
    private:
        QPixmap game_bg1;
        int x, y;
};

#endif // GAME_BG1_H
