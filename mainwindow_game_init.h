#ifndef MAINWINDOW_GAME_INIT_H
#define MAINWINDOW_GAME_INIT_H

#include "mainwindow.h"
#include "mario.h"
#include "game_bg.h"
#include "floor_brick.h"
#include <QDebug>

void MainWindow::game_init() {
    qDebug() << "game_init() Called";
    game_status = 1;
    cur_scene = &game_scene;
    view_x = Mario::init_x; // Equals to mario's x coordinates between the scenes;

    // Scene 1
        // add game_bg
        cur_scene->addItem(game_bg.game_bg_item);

        // add floor_bricks_item(s)
        const int floor_num_in_a_scene = 1400 / Floor_brick::floor_brick_width;
        for (int i = 0 ; i < floor_num_in_a_scene ; i++) {
            floor_bricks.push_back(new Floor_brick);
            floor_bricks[i]->set_x(i * Floor_brick::floor_brick_width);
            cur_scene->addItem(floor_bricks[i]->floor_brick_item);
        }

        // add mario
        cur_scene->addItem(mario.mario);

}


#endif // MAINWINDOW_GAME_INIT_H
