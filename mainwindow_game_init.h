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
        std::vector<std::vector<int>> stone_bricks_list = {
            {800, 620 - Floor_brick::floor_brick_height - Stone_brick::stone_brick_height},
            {800, 620 - Floor_brick::floor_brick_height - 2 * Stone_brick::stone_brick_height},
            {800, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {650, 620 - Floor_brick::floor_brick_height - Stone_brick::stone_brick_height},
        };
        for (int i = 0; i < static_cast<int>(stone_bricks_list.size()); i++) {
            stone_bricks.push_back(new Stone_brick);
            stone_bricks[i]->set_xy(stone_bricks_list[i][0], stone_bricks_list[i][1]);
            cur_scene->addItem(stone_bricks[i]->stone_brick_item);
        }


        // add coins
        std::vector<std::vector<int>> coins_list = {
            {1000, 620 - Floor_brick::floor_brick_height - Coin::coin_height},
            {800, stone_bricks_list[2][1] - Coin::coin_height}
        };
        for (int i = 0; i < static_cast<int>(coins_list.size()); i++) {
            coins.push_back(new Coin);
            coins[i]->set_xy(coins_list[i][0], coins_list[i][1]);
            cur_scene->addItem(coins[i]->coin_item);
        }


        // add mario
        mario.cur_scene = cur_scene;
        mario.game_bg_item = game_bg.game_bg_item;
        mario.floor_bricks = floor_bricks;
        mario.stone_bricks = stone_bricks;
        cur_scene->addItem(mario.mario);
}


#endif // MAINWINDOW_GAME_INIT_H
