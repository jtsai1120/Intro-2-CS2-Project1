#ifndef MAINWINDOW_GAME_INIT_H
#define MAINWINDOW_GAME_INIT_H

#include "mainwindow.h"
#include "mario.h"
#include "game_bg.h"
#include "coin.h"
#include "stone_brick.h"
#include "normal_brick.h"
#include "floor_brick.h"
#include "box_brick.h"
#include "broken_brick.h"
#include "water_pipe.h"

#include <QDebug>

void MainWindow::game_init() {
    qDebug() << "game_init() Called";
    game_status = 1;
    cur_scene = &game_scene;
    view_x = Mario::init_x; // Equals to mario's x coordinates between the scenes;


    // Game Scene
        // add game_bg
        cur_scene->addItem(game_bg.game_bg_item);
        cur_scene->addItem(game_bg1.game_bg_item);
        cur_scene->addItem(game_bg2.game_bg_item);
        cur_scene->addItem(game_bg3.game_bg_item);
        cur_scene->addItem(game_bg4.game_bg_item);
        game_bg1.set(1);//向右方平移一個螢幕大小
        game_bg2.set(2);
        game_bg3.set(3);
        game_bg4.set(4);

        // score text
        cur_scene->addItem(score.score_text);

        // hp text
        cur_scene->addItem(hp.hp_text);

        // add floor_bricks_items
        const int floor_num_in_a_scene = 1000 / Floor_brick::floor_brick_width;
        for (int i = 0 ; i < floor_num_in_a_scene ; i++) {
            floor_bricks.push_back(new Floor_brick);
            floor_bricks[i]->set_x(i * Floor_brick::floor_brick_width);
            cur_scene->addItem(floor_bricks[i]->floor_brick_item);
        }
        for (int i = 20 ; i < 2 * floor_num_in_a_scene ; i++) {
            floor_bricks.push_back(new Floor_brick);
            floor_bricks[i]->set_x(500 + i * Floor_brick::floor_brick_width);
            cur_scene->addItem(floor_bricks[i]->floor_brick_item);
        }


        // add stone_bricks
        std::vector<std::vector<int>> stone_bricks_list = {
            {800, 620 - Floor_brick::floor_brick_height - Stone_brick::stone_brick_height},
            {800, 620 - Floor_brick::floor_brick_height - 2 * Stone_brick::stone_brick_height},
            {800, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {650, 620 - Floor_brick::floor_brick_height - Stone_brick::stone_brick_height},
            {500, 620 - Floor_brick::floor_brick_height - 2 * Stone_brick::stone_brick_height},
        };
        for (int i = 0; i < static_cast<int>(stone_bricks_list.size()); i++) {
            stone_bricks.push_back(new Stone_brick);
            stone_bricks[i]->set_xy(stone_bricks_list[i][0], stone_bricks_list[i][1]);
            cur_scene->addItem(stone_bricks[i]->stone_brick_item);
        }

        // add normal_bricks
        std::vector<std::vector<int>> normal_bricks_list = {
            {950, 620 - Floor_brick::floor_brick_height - 3 * Normal_brick::normal_brick_height},
            //{950, 620 - Floor_brick::floor_brick_height - 1 * Normal_brick::normal_brick_height},
        };
        for (int i = 0; i < static_cast<int>(normal_bricks_list.size()); i++) {
            normal_bricks.push_back(new Normal_brick);
            normal_bricks[i]->set_xy(normal_bricks_list[i][0], normal_bricks_list[i][1]);
            normal_bricks[i]->init_y = normal_bricks_list[i][1];
            cur_scene->addItem(normal_bricks[i]->normal_brick_item);
        }

        // add box_bricks
        std::vector<std::vector<int>> box_bricks_list = {
            {1100, 620 - Floor_brick::floor_brick_height - 2 * Box_brick::box_brick_height},
        };
        for (int i = 0; i < static_cast<int>(box_bricks_list.size()); i++) {
            box_bricks.push_back(new Box_brick);
            box_bricks[i]->set_xy(box_bricks_list[i][0], box_bricks_list[i][1]);
            cur_scene->addItem(box_bricks[i]->box_brick_item);
        }

        // add broken_bricks
        std::vector<std::vector<int>> broken_bricks_list = {
            {1250, 620 - Floor_brick::floor_brick_height - 2 * Broken_brick::broken_brick_height},
        };
        for (int i = 0; i < static_cast<int>(broken_bricks_list.size()); i++) {
            broken_bricks.push_back(new Broken_brick);
            broken_bricks[i]->set_xy(broken_bricks_list[i][0], broken_bricks_list[i][1]);
            cur_scene->addItem(broken_bricks[i]->broken_brick_item);
        }

        // add water_pipes
        std::vector<std::vector<int>> water_pipes_list = {
            {1400, 620 - Floor_brick::floor_brick_height - 2 * Normal_brick::normal_brick_height},
        };
        for (int i = 0; i < static_cast<int>(water_pipes_list.size()); i++) {
            water_pipes.push_back(new Water_pipe);
            water_pipes[i]->set_xy(water_pipes_list[i][0], water_pipes_list[i][1]);
            cur_scene->addItem(water_pipes[i]->water_pipe_item);
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

        // 設定mario 的磚塊位置
        mario.floor_bricks = floor_bricks;
        mario.stone_bricks = stone_bricks;
        mario.normal_bricks = normal_bricks;
        mario.box_bricks = box_bricks;
        mario.broken_bricks = broken_bricks;
        mario.water_pipes = water_pipes;

        cur_scene->addItem(mario.mario);
}


#endif // MAINWINDOW_GAME_INIT_H
