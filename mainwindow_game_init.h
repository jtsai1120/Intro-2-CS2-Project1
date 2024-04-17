#ifndef MAINWINDOW_GAME_INIT_H
#define MAINWINDOW_GAME_INIT_H

#include "mainwindow.h"
#include "mario.h"
#include "game_bg.h"
#include "floor_brick.h"
#include "coin.h"
#include "stone_brick.h"
#include <QDebug>

void MainWindow::game_init() {
    qDebug() << "game_init() Called";
    game_status = 1;
    cur_scene = &game_scene;
    view_x = Mario::init_x; // Equals to mario's x coordinates between the scenes;

    // Scene 1
        // add game_bg
        cur_scene->addItem(game_bg.game_bg_item);

        // score text
        cur_scene->addItem(score.score_text);

        // add floor_bricks_items
        const int floor_num_in_a_scene = 1400 / Floor_brick::floor_brick_width;
        for (int i = 0 ; i < floor_num_in_a_scene ; i++) {
            floor_bricks.push_back(new Floor_brick);
            floor_bricks[i]->set_x(i * Floor_brick::floor_brick_width);
            cur_scene->addItem(floor_bricks[i]->floor_brick_item);
        }

        // add stone_bricks
        stone_bricks.push_back(new Stone_brick);
        stone_bricks.push_back(new Stone_brick);
        stone_bricks[0]->set_xy(600, 410);
        stone_bricks[1]->set_xy(800, 330);
        cur_scene->addItem(stone_bricks[0]->stone_brick_item);
        cur_scene->addItem(stone_bricks[1]->stone_brick_item);

        // add coins
        coins.push_back(new Coin);
        coins[0]->set_xy(800, 620 - Floor_brick::floor_brick_height - Coin::coin_height);
        cur_scene->addItem(coins[0]->coin_item);

        // add mario
        mario.cur_scene = cur_scene;
        mario.game_bg_item = game_bg.game_bg_item;
        mario.floor_bricks = floor_bricks;
        mario.stone_bricks = stone_bricks;
        cur_scene->addItem(mario.mario);
}


#endif // MAINWINDOW_GAME_INIT_H
