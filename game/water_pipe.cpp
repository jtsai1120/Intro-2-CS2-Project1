#include "water_pipe.h"

Water_pipe::Water_pipe() {
    water_pipe_pic.load(":/Dataset/image/brick/water pipe.png");
    water_pipe_item = new QGraphicsPixmapItem(water_pipe_pic);
}

void Water_pipe::set_xy(int new_x, int new_y) {
    x = new_x;
    y = new_y;
    water_pipe_item->setPos(x, y);
}

void Water_pipe::move(int dx) {
    x += dx;
    set_xy(x, y);
}

void Water_pipe::go_in() {
}
