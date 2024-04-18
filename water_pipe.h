#ifndef WATER_PIPE_H
#define WATER_PIPE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Water_pipe
{
public:
    Water_pipe();
    QGraphicsPixmapItem *water_pipe_item;

    void set_xy(int new_x, int new_y);
    void move(int dx);
    void go_in();//互動?

    static const int water_pipe_height = 50;
    static const int water_pipe_width = 50;
private:
    QPixmap water_pipe_pic;
    int x, y;

};

#endif // WATER_PIPE_H
