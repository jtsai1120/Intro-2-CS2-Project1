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
#include "invisible_brick.h"
#include "toxic_mushroom.h"
#include "super_mushroom.h"
#include "fire_flower.h"


#include <QDebug>

void MainWindow::game_init() {
    qDebug() << "game_init() Called";
    game_status = 1;
    cur_scene = &game_scene;
    view_x = Mario::init_x; // Equals to mario's x coordinates between the scenes;


    // Game Scene
        // add game_bg
        for (int i = 0; i < 5; i++) {
            game_bgs.push_back(new Game_bg);
            game_bgs[i]->set(i);
            cur_scene->addItem(game_bgs[i]->game_bg_item);
        }

        // add flag pole & flag
        cur_scene->addItem(flag_pole.flag_pole_item);
        flag.mario = &mario;
        cur_scene->addItem(flag.flag_item);

        // score text
        cur_scene->addItem(score.score_text);

        // hp text
        cur_scene->addItem(hp.hp_text);

        // add invisible_bricks
        invisible_bricks_list = {
            {750 - 10, 620 - Floor_brick::floor_brick_height - 6 * Invisible_brick::invisible_brick_height},
            {950, 620 - 10 - Floor_brick::floor_brick_height - 10 * Invisible_brick::invisible_brick_height},
            {-50, 620 - Floor_brick::floor_brick_height - 1 * Invisible_brick::invisible_brick_height},
            {1800, 620 - 10 - Floor_brick::floor_brick_height - 1 * Invisible_brick::invisible_brick_height},
            {2000, 620 - 10 - Floor_brick::floor_brick_height - 12 * Invisible_brick::invisible_brick_height},
            {2000, 620 - 10 - Floor_brick::floor_brick_height - 13 * Invisible_brick::invisible_brick_height},
            {2600, 620 - 10 - Floor_brick::floor_brick_height - 10 * Invisible_brick::invisible_brick_height},
            {2600, 620 - 10 - Floor_brick::floor_brick_height - 11 * Invisible_brick::invisible_brick_height},
            {2700, 620 - 10 - Floor_brick::floor_brick_height - 0 * Stone_brick::stone_brick_height},
            {3750 + 10, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},
            {4250, 620 - Floor_brick::floor_brick_height - (-1) * Stone_brick::stone_brick_height},
            {4250, 620 - Floor_brick::floor_brick_height - (-2) * Stone_brick::stone_brick_height},
            {4300, 620 - Floor_brick::floor_brick_height - (-2) * Stone_brick::stone_brick_height},
            {4350, 620 - Floor_brick::floor_brick_height - (-2) * Stone_brick::stone_brick_height},
            {4400, 620 - Floor_brick::floor_brick_height - (-2) * Stone_brick::stone_brick_height},
            {4450, 620 - Floor_brick::floor_brick_height - (-2) * Stone_brick::stone_brick_height},
            {4500, 620 - Floor_brick::floor_brick_height - (-2) * Stone_brick::stone_brick_height},
            {4550, 620 - Floor_brick::floor_brick_height - (-2) * Stone_brick::stone_brick_height},
            {4600, 620 - Floor_brick::floor_brick_height - (-2) * Stone_brick::stone_brick_height},
            {4650, 620 - Floor_brick::floor_brick_height - (-2) * Stone_brick::stone_brick_height},
            {4700, 620 - Floor_brick::floor_brick_height - (-2) * Stone_brick::stone_brick_height},
            {4750, 620 - Floor_brick::floor_brick_height - (-2) * Stone_brick::stone_brick_height},
            {4800, 620 - Floor_brick::floor_brick_height - (-2) * Stone_brick::stone_brick_height},
            {4850, 620 - Floor_brick::floor_brick_height - (-2) * Stone_brick::stone_brick_height},
            {4900, 620 - Floor_brick::floor_brick_height - (-2) * Stone_brick::stone_brick_height},
            {4950, 620 - Floor_brick::floor_brick_height - (-2) * Stone_brick::stone_brick_height},
            {5000, 620 - Floor_brick::floor_brick_height - (-2) * Stone_brick::stone_brick_height},
            {5050, 620 - Floor_brick::floor_brick_height - (-2) * Stone_brick::stone_brick_height},
            {5100, 620 - Floor_brick::floor_brick_height - (-2) * Stone_brick::stone_brick_height},

            {6550, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {6550, 620 - Floor_brick::floor_brick_height - 9 * Stone_brick::stone_brick_height},

            {6830, 620 - Floor_brick::floor_brick_height - 11 * Stone_brick::stone_brick_height},
            {6830, 620 - Floor_brick::floor_brick_height - 10 * Stone_brick::stone_brick_height},
            {6830, 620 - Floor_brick::floor_brick_height - 12 * Stone_brick::stone_brick_height},
            {6830, 620 - Floor_brick::floor_brick_height - 13 * Stone_brick::stone_brick_height},


        };
        for (int i = 0; i < static_cast<int>(invisible_bricks_list.size()); i++) {
            invisible_bricks.push_back(new Invisible_brick);
            invisible_bricks[i]->set_xy(invisible_bricks_list[i][0], invisible_bricks_list[i][1]);
            cur_scene->addItem(invisible_bricks[i]->invisible_brick_item);
        }

        // add floor_bricks_items
        const int max_floor_brick_num_in_a_scene = 1400 / Floor_brick::floor_brick_width;
        for (int i = 0 ; i < 5 * max_floor_brick_num_in_a_scene ; i++) {
            floor_bricks.push_back(new Floor_brick);
            if ((i+5) % max_floor_brick_num_in_a_scene == 0
                  || (i+6) % max_floor_brick_num_in_a_scene == 0)
                floor_bricks[i]->set_x(-100);
            else if(i > max_floor_brick_num_in_a_scene && i < 1.5 * max_floor_brick_num_in_a_scene)
                floor_bricks[i]->set_x(-100);
            else if(i > 2.65 * max_floor_brick_num_in_a_scene && i < 4 * max_floor_brick_num_in_a_scene)
                floor_bricks[i]->set_x(-100);
            else if(i > 4.6 * max_floor_brick_num_in_a_scene && i < 4.8 * max_floor_brick_num_in_a_scene)
                floor_bricks[i]->set_x(-100);

            else
                floor_bricks[i]->set_x(i * Floor_brick::floor_brick_width);
            cur_scene->addItem(floor_bricks[i]->floor_brick_item);
        }


        // add stone_bricks
        stone_bricks_list = {
            {200, 620 - Floor_brick::floor_brick_height - 1 * Stone_brick::stone_brick_height},
            {300, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {800, 620 - Floor_brick::floor_brick_height - 1 * Stone_brick::stone_brick_height},
            {1100, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {800, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},
            {750, 620 - Floor_brick::floor_brick_height - 6 * Stone_brick::stone_brick_height},
            {300, 620 - Floor_brick::floor_brick_height - 6 * Stone_brick::stone_brick_height},
            {150, 620 - Floor_brick::floor_brick_height - 6 * Stone_brick::stone_brick_height},
            {150, 620 - Floor_brick::floor_brick_height - 6 * Stone_brick::stone_brick_height},
            {400, 620 - Floor_brick::floor_brick_height - 10 * Stone_brick::stone_brick_height},
            {450, 620 - Floor_brick::floor_brick_height - 10 * Stone_brick::stone_brick_height},
            //{500, 620 - Floor_brick::floor_brick_height - 10 * Stone_brick::stone_brick_height},
            {550, 620 - Floor_brick::floor_brick_height - 11 * Stone_brick::stone_brick_height},
            {600, 620 - Floor_brick::floor_brick_height - 11 * Stone_brick::stone_brick_height},
            {650, 620 - Floor_brick::floor_brick_height - 11 * Stone_brick::stone_brick_height},
            {700, 620 - Floor_brick::floor_brick_height - 11 * Stone_brick::stone_brick_height},
            {750, 620 - Floor_brick::floor_brick_height - 11 * Stone_brick::stone_brick_height},
            //{800, 620 - Floor_brick::floor_brick_height - 10 * Stone_brick::stone_brick_height},
            {850, 620 - Floor_brick::floor_brick_height - 10 * Stone_brick::stone_brick_height},
            {900, 620 - Floor_brick::floor_brick_height - 10 * Stone_brick::stone_brick_height},
            {950, 620 - Floor_brick::floor_brick_height - 10 * Stone_brick::stone_brick_height},
            {1150, 620 - Floor_brick::floor_brick_height - 7 * Stone_brick::stone_brick_height},
            //{1200, 620 - Floor_brick::floor_brick_height - 7 * Stone_brick::stone_brick_height},
            //{1200, 620 - Floor_brick::floor_brick_height - 6 * Stone_brick::stone_brick_height},
            {1250, 620 - Floor_brick::floor_brick_height - 7 * Stone_brick::stone_brick_height},
            {1550, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {1600, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {1750, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {2150, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {2350, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {2400, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {2450, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {1600, 620 - Floor_brick::floor_brick_height - 1 * Stone_brick::stone_brick_height},
            {1650, 620 - Floor_brick::floor_brick_height - 1 * Stone_brick::stone_brick_height},
            {1700, 620 - Floor_brick::floor_brick_height - 1 * Stone_brick::stone_brick_height},
            {1750, 620 - Floor_brick::floor_brick_height - 1 * Stone_brick::stone_brick_height},
            {1800, 620 - Floor_brick::floor_brick_height - 1 * Stone_brick::stone_brick_height},
            {1550, 620 - Floor_brick::floor_brick_height - 2 * Stone_brick::stone_brick_height},
            {1600, 620 - Floor_brick::floor_brick_height - 4 * Stone_brick::stone_brick_height},
            {1650, 620 - Floor_brick::floor_brick_height - 4 * Stone_brick::stone_brick_height},
            {1700, 620 - Floor_brick::floor_brick_height - 4 * Stone_brick::stone_brick_height},
            {1750, 620 - Floor_brick::floor_brick_height - 4 * Stone_brick::stone_brick_height},
            {2450, 620 - Floor_brick::floor_brick_height - 1 * Stone_brick::stone_brick_height},
            {2450, 620 - Floor_brick::floor_brick_height - 2 * Stone_brick::stone_brick_height},
            {2450, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {2450, 620 - Floor_brick::floor_brick_height - 4 * Stone_brick::stone_brick_height},
            {2100, 620 - Floor_brick::floor_brick_height - 1 * Stone_brick::stone_brick_height},
            {2150, 620 - Floor_brick::floor_brick_height - 4 * Stone_brick::stone_brick_height},
            {2050, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {2750, 620 - Floor_brick::floor_brick_height - 4 * Stone_brick::stone_brick_height},
            {2800, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {2850, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {2925, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {2900, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {3025, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {3150, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {3050, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {3100, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {2950, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},
            {3050, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},
            {3200, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {3250, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {3350, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {3400, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {3450, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {3550, 620 - Floor_brick::floor_brick_height - 1 * Stone_brick::stone_brick_height},
            {3600, 620 - Floor_brick::floor_brick_height - 1 * Stone_brick::stone_brick_height},
            {3600, 620 - Floor_brick::floor_brick_height - 2 * Stone_brick::stone_brick_height},
            {3600, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {3600, 620 - Floor_brick::floor_brick_height - 4 * Stone_brick::stone_brick_height},
            {3900, 620 - Floor_brick::floor_brick_height - 10 * Stone_brick::stone_brick_height},
            {3900, 620 - Floor_brick::floor_brick_height - 9 * Stone_brick::stone_brick_height},
            {3900, 620 - Floor_brick::floor_brick_height - 11 * Stone_brick::stone_brick_height},
            {3900, 620 - Floor_brick::floor_brick_height - 12 * Stone_brick::stone_brick_height},


            {3500, 620 - Floor_brick::floor_brick_height - 9 * Stone_brick::stone_brick_height},
            {3450, 620 - Floor_brick::floor_brick_height - 6 * Stone_brick::stone_brick_height},
            {3400, 620 - Floor_brick::floor_brick_height - 6 * Stone_brick::stone_brick_height},
            {3350, 620 - Floor_brick::floor_brick_height - 6 * Stone_brick::stone_brick_height},
            {3600, 620 - Floor_brick::floor_brick_height - 6 * Stone_brick::stone_brick_height},
            {3250, 620 - Floor_brick::floor_brick_height - 6 * Stone_brick::stone_brick_height},
            {3200, 620 - Floor_brick::floor_brick_height - 6 * Stone_brick::stone_brick_height},
            {3150, 620 - Floor_brick::floor_brick_height - 6 * Stone_brick::stone_brick_height},
            {2950, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {3000, 620 - Floor_brick::floor_brick_height - 7 * Stone_brick::stone_brick_height},
            {3000, 620 - Floor_brick::floor_brick_height - 6 * Stone_brick::stone_brick_height},
            {2950, 620 - Floor_brick::floor_brick_height - 10 * Stone_brick::stone_brick_height},
            {3000, 620 - Floor_brick::floor_brick_height - 10 * Stone_brick::stone_brick_height},
            {3100, 620 - Floor_brick::floor_brick_height - 10 * Stone_brick::stone_brick_height},
            {3150, 620 - Floor_brick::floor_brick_height - 10 * Stone_brick::stone_brick_height},
            {2900, 620 - Floor_brick::floor_brick_height - 10 * Stone_brick::stone_brick_height},
            {3550, 620 - Floor_brick::floor_brick_height - 9 * Stone_brick::stone_brick_height},
            {3850, 620 - Floor_brick::floor_brick_height - 1 * Stone_brick::stone_brick_height},
            {3900, 620 - Floor_brick::floor_brick_height - 2 * Stone_brick::stone_brick_height},
            {3750, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},
            {3650, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {4000, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},
            {4200, 620 - Floor_brick::floor_brick_height - 0 * Stone_brick::stone_brick_height},
            {4150, 620 - Floor_brick::floor_brick_height - 1 * Stone_brick::stone_brick_height},
            {4100, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {4100, 620 - Floor_brick::floor_brick_height - 2 * Stone_brick::stone_brick_height},
            {4250, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {4300, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {4400, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {4500, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {4600, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {4700, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {4800, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {4900, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {5000, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {5100, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {5200, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {4300, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},
            {4400, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},
            {4500, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},
            {4600, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},
            {4700, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},
            {4800, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},
            {4900, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},
            {5000, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},
            {5100, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},
            {5200, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},
            {4300, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {4400, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {4500, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {4600, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {4700, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {4800, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {4900, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {5000, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {5100, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {5200, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {5300, 620 - Floor_brick::floor_brick_height - 1 * Stone_brick::stone_brick_height},
            {5400, 620 - Floor_brick::floor_brick_height - 1 * Stone_brick::stone_brick_height},
            {5450, 620 - Floor_brick::floor_brick_height - 1 * Stone_brick::stone_brick_height},
            {5500, 620 - Floor_brick::floor_brick_height - 1 * Stone_brick::stone_brick_height},
            {5550, 620 - Floor_brick::floor_brick_height - 1 * Stone_brick::stone_brick_height},
            {5600, 620 - Floor_brick::floor_brick_height - 7 * Stone_brick::stone_brick_height},
            {5650, 620 - Floor_brick::floor_brick_height - 7 * Stone_brick::stone_brick_height},
            {5650, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {5750, 620 - Floor_brick::floor_brick_height - 4 * Stone_brick::stone_brick_height},
            {5800, 620 - Floor_brick::floor_brick_height - 4 * Stone_brick::stone_brick_height},
            {5800, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},
            {5900, 620 - Floor_brick::floor_brick_height - 4 * Stone_brick::stone_brick_height},
            {5950, 620 - Floor_brick::floor_brick_height - 4 * Stone_brick::stone_brick_height},
            {5950, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},

            {6050, 620 - Floor_brick::floor_brick_height - 7 * Stone_brick::stone_brick_height},
            {6100, 620 - Floor_brick::floor_brick_height - 7 * Stone_brick::stone_brick_height},
            {6100, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},

            {6250, 620 - Floor_brick::floor_brick_height - 4 * Stone_brick::stone_brick_height},
            {6300, 620 - Floor_brick::floor_brick_height - 4 * Stone_brick::stone_brick_height},
            {6400, 620 - Floor_brick::floor_brick_height - 5 * Stone_brick::stone_brick_height},


            {6200, 620 - Floor_brick::floor_brick_height - 3 * Stone_brick::stone_brick_height},
            {6150, 620 - Floor_brick::floor_brick_height - 2 * Stone_brick::stone_brick_height},

            {6650, 620 - Floor_brick::floor_brick_height - 6 * Stone_brick::stone_brick_height},
            {6450, 620 - Floor_brick::floor_brick_height - 6 * Stone_brick::stone_brick_height},

            {6300, 620 - Floor_brick::floor_brick_height - 7 * Stone_brick::stone_brick_height},




            //
            //{1450, 620 - Floor_brick::floor_brick_height - 4 * Stone_brick::stone_brick_height},


            //{650, 620 - Floor_brick::floor_brick_height - Stone_brick::stone_brick_height},
            //{500, 620 - Floor_brick::floor_brick_height - 2 * Stone_brick::stone_brick_height},
        };
        for (int i = 0; i < static_cast<int>(stone_bricks_list.size()); i++) {
            stone_bricks.push_back(new Stone_brick);
            stone_bricks[i]->set_xy(stone_bricks_list[i][0], stone_bricks_list[i][1]);
            cur_scene->addItem(stone_bricks[i]->stone_brick_item);
        }

        // add normal_bricks
        normal_bricks_list = {
            {400, 620 - Floor_brick::floor_brick_height - 3 * Normal_brick::normal_brick_height},
            //{450, 620 - Floor_brick::floor_brick_height - 4 * Normal_brick::normal_brick_height},
            {800, 620 - Floor_brick::floor_brick_height - 10 * Normal_brick::normal_brick_height},

            {1000, 620 - Floor_brick::floor_brick_height - 4 * Normal_brick::normal_brick_height},
            {350, 620 - Floor_brick::floor_brick_height - 6 * Normal_brick::normal_brick_height},
            {300, 620 - Floor_brick::floor_brick_height - 9 * Normal_brick::normal_brick_height},
            {1500, 620 - Floor_brick::floor_brick_height - 5 * Normal_brick::normal_brick_height},
            {3000, 620 - Floor_brick::floor_brick_height - 6 * Normal_brick::normal_brick_height},

            {3300, 620 - Floor_brick::floor_brick_height - 3 * Normal_brick::normal_brick_height},
            {3800, 620 - Floor_brick::floor_brick_height - 11 * Normal_brick::normal_brick_height},


        };
        for (int i = 0; i < static_cast<int>(normal_bricks_list.size()); i++) {
            normal_bricks.push_back(new Normal_brick);
            normal_bricks[i]->set_xy(normal_bricks_list[i][0], normal_bricks_list[i][1]);
            normal_bricks[i]->init_y = normal_bricks_list[i][1];
            cur_scene->addItem(normal_bricks[i]->normal_brick_item);
        }

        //add super mushroom
        super_mushroom_list = {
            //{1100, 620 - Floor_brick::floor_brick_height - 2 * Box_brick::box_brick_height},
            //{350, 620 - Floor_brick::floor_brick_height - 3 * Box_brick::box_brick_height},
            //{350, 620 - Floor_brick::floor_brick_height - 9 * Box_brick::box_brick_height},
            {2300, 620 - Floor_brick::floor_brick_height - 3 * Box_brick::box_brick_height},
            {2950, 620 - Floor_brick::floor_brick_height - 4 * Box_brick::box_brick_height},
        };

        for (int i = 0; i < static_cast<int>(super_mushroom_list.size()); i++) {
            super_mushrooms.push_back(new Super_mushroom);
            super_mushrooms[i]->set_xy(super_mushroom_list[i][0],super_mushroom_list[i][1]);
            cur_scene->addItem(super_mushrooms[i]->super_mushroom_item);

        }

        //add fire flowers
        fire_flowers_list = {
            //{1100, 620 - Floor_brick::floor_brick_height - 2 * Box_brick::box_brick_height},
            {350, 620 - Floor_brick::floor_brick_height - 3 * Box_brick::box_brick_height},
            {350, 620 - Floor_brick::floor_brick_height - 9 * Box_brick::box_brick_height},
            //{2300, 620 - Floor_brick::floor_brick_height - 3 * Box_brick::box_brick_height},
            //{2950, 620 - Floor_brick::floor_brick_height - 4 * Box_brick::box_brick_height},
        };

        for (int i = 0; i < static_cast<int>(fire_flowers_list.size()); i++) {
            fire_flowers.push_back(new Fire_flower);
            fire_flowers[i]->set_xy(fire_flowers_list[i][0],fire_flowers_list[i][1]);
            cur_scene->addItem(fire_flowers[i]->fire_flower_item);

        }

        // add box_bricks
        box_bricks_list = {
            //{1100, 620 - Floor_brick::floor_brick_height - 2 * Box_brick::box_brick_height},
            {350, 620 - Floor_brick::floor_brick_height - 3 * Box_brick::box_brick_height},
            {350, 620 - Floor_brick::floor_brick_height - 9 * Box_brick::box_brick_height},
            {2300, 620 - Floor_brick::floor_brick_height - 3 * Box_brick::box_brick_height},
            {2950, 620 - Floor_brick::floor_brick_height - 4 * Box_brick::box_brick_height},
            {3750, 620 - Floor_brick::floor_brick_height - 8 * Box_brick::box_brick_height},


        };
        for (int i = 0; i < static_cast<int>(box_bricks_list.size()); i++) {
            box_bricks.push_back(new Box_brick);
            box_bricks[i]->set_xy(box_bricks_list[i][0], box_bricks_list[i][1]);
            cur_scene->addItem(box_bricks[i]->box_brick_item);

        }


        // add broken_bricks
        broken_bricks_list = {
            {1250, 620 - Floor_brick::floor_brick_height - 2 * Broken_brick::broken_brick_height},
            {0, 620 - Floor_brick::floor_brick_height - 8 * Broken_brick::broken_brick_height},
            {750, 620 - Floor_brick::floor_brick_height - 8 * Broken_brick::broken_brick_height},
            {650, 620 - Floor_brick::floor_brick_height - 9 * Broken_brick::broken_brick_height},
            {1200, 620 - Floor_brick::floor_brick_height - 6 * Broken_brick::broken_brick_height},
            {0, 620 - Floor_brick::floor_brick_height - 10 * Broken_brick::broken_brick_height},
            {2400, 620 - Floor_brick::floor_brick_height - 3 * Broken_brick::broken_brick_height},
            {2350, 620 - Floor_brick::floor_brick_height - 3 * Broken_brick::broken_brick_height},
            {2250, 620 - Floor_brick::floor_brick_height - 3 * Broken_brick::broken_brick_height},
            {2200, 620 - Floor_brick::floor_brick_height - 3 * Broken_brick::broken_brick_height},
            {3000, 620 - Floor_brick::floor_brick_height - 4 * Broken_brick::broken_brick_height},
            {3050, 620 - Floor_brick::floor_brick_height - 9 * Broken_brick::broken_brick_height},
            {3550, 620 - Floor_brick::floor_brick_height - 5 * Broken_brick::broken_brick_height},
            {3500, 620 - Floor_brick::floor_brick_height - 5 * Broken_brick::broken_brick_height},
            {3800, 620 - Floor_brick::floor_brick_height - 8 * Broken_brick::broken_brick_height},
            {3800, 620 - Floor_brick::floor_brick_height - 9 * Broken_brick::broken_brick_height},
            {3800, 620 - Floor_brick::floor_brick_height - 12 * Broken_brick::broken_brick_height},
            {3850, 620 - Floor_brick::floor_brick_height - 11 * Broken_brick::broken_brick_height},

            {3950, 620 - Floor_brick::floor_brick_height - 6 * Broken_brick::broken_brick_height},
            {3850, 620 - Floor_brick::floor_brick_height - 8 * Stone_brick::stone_brick_height},
            {5100, 620 - Floor_brick::floor_brick_height - (-1) * Stone_brick::stone_brick_height},

        };
        for (int i = 0; i < static_cast<int>(broken_bricks_list.size()); i++) {
            broken_bricks.push_back(new Broken_brick);
            broken_bricks[i]->set_xy(broken_bricks_list[i][0], broken_bricks_list[i][1]);
            broken_bricks[i]->init_y = broken_bricks_list[i][1];
            cur_scene->addItem(broken_bricks[i]->broken_brick_item);
        }

        // add water_pipes
        water_pipes_list = {
            {1350, 620 - Floor_brick::floor_brick_height - 2 * Normal_brick::normal_brick_height},
            //{2600, 620 - Floor_brick::floor_brick_height - 2 * Normal_brick::normal_brick_height},
        };
        for (int i = 0; i < static_cast<int>(water_pipes_list.size()); i++) {
            water_pipes.push_back(new Water_pipe);
            water_pipes[i]->set_xy(water_pipes_list[i][0], water_pipes_list[i][1]);
            cur_scene->addItem(water_pipes[i]->water_pipe_item);
        }

        //add bullets
        for (int i = 0; i < 3; i++) {
            bullets.push_back(new Bullet);
            bullets[i]->set_xy(0,1000);
            cur_scene->addItem(bullets[i]->bullet_item);
        }


        //add super mushroom's map
        for (int i = 0; i < static_cast<int>(super_mushroom_list.size()); i++) {
            //add super mushroom's map
            super_mushrooms[i]->floor_bricks = floor_bricks;
            super_mushrooms[i]->stone_bricks = stone_bricks;
            super_mushrooms[i]->normal_bricks = normal_bricks;
            super_mushrooms[i]->box_bricks = box_bricks;
            super_mushrooms[i]->broken_bricks = broken_bricks;
            super_mushrooms[i]->water_pipes = water_pipes;
            super_mushrooms[i]->invisible_bricks = invisible_bricks;
            super_mushrooms[i]->cur_scene = cur_scene;
        }


        // add toxic mushrooms
        toxic_mushrooms_list = {
            {150, 620 - Floor_brick::floor_brick_height - 4 * Toxic_mushroom::toxic_mushroom_height},
            ///*
            {750, 620 - Floor_brick::floor_brick_height - 13 * Toxic_mushroom::toxic_mushroom_height},
            {250, 620 - Floor_brick::floor_brick_height - 10 * Toxic_mushroom::toxic_mushroom_height},
            {1200, 620 - Floor_brick::floor_brick_height - 7 * Toxic_mushroom::toxic_mushroom_height},
            {850, 620 - Floor_brick::floor_brick_height - 13 * Toxic_mushroom::toxic_mushroom_height},
            {1650, 620 + 10 - Floor_brick::floor_brick_height - 3 * Toxic_mushroom::toxic_mushroom_height},
            {2200, 620 - Floor_brick::floor_brick_height - 4 * Toxic_mushroom::toxic_mushroom_height},
            {3000, 620 - Floor_brick::floor_brick_height - 5 * Toxic_mushroom::toxic_mushroom_height},
            {2900, 620 + 10 - Floor_brick::floor_brick_height - 4 * Toxic_mushroom::toxic_mushroom_height},
            {3050, 620 - Floor_brick::floor_brick_height - 10 * Toxic_mushroom::toxic_mushroom_height},
            {3550, 620 - Floor_brick::floor_brick_height - 6 * Toxic_mushroom::toxic_mushroom_height},
            {3850, 620 - Floor_brick::floor_brick_height - 12 * Toxic_mushroom::toxic_mushroom_height},


        };

        for (int i = 0; i < static_cast<int>(toxic_mushrooms_list.size()); i++) {
            toxic_mushrooms.push_back(new Toxic_mushroom);
            toxic_mushrooms[i]->set_xy(toxic_mushrooms_list[i][0], toxic_mushrooms_list[i][1]);
            toxic_mushrooms[i]->init_y = toxic_mushrooms_list[i][1];

            // 設定toxic mushroom 的磚塊位置
            toxic_mushrooms[i]->floor_bricks = floor_bricks;
            toxic_mushrooms[i]->stone_bricks = stone_bricks;
            toxic_mushrooms[i]->normal_bricks = normal_bricks;
            toxic_mushrooms[i]->box_bricks = box_bricks;
            toxic_mushrooms[i]->broken_bricks = broken_bricks;
            toxic_mushrooms[i]->water_pipes = water_pipes;
            toxic_mushrooms[i]->invisible_bricks = invisible_bricks;
            toxic_mushrooms[i]->cur_scene = cur_scene;


            cur_scene->addItem(toxic_mushrooms[i]->toxic_mushroom_item);
        }

        //add bullet's map
        for (int i = 0; i < 3; i++) {
            bullets[i]->floor_bricks = floor_bricks;
            bullets[i]->stone_bricks = stone_bricks;
            bullets[i]->normal_bricks = normal_bricks;
            bullets[i]->box_bricks = box_bricks;
            bullets[i]->broken_bricks = broken_bricks;
            bullets[i]->water_pipes = water_pipes;
            bullets[i]->invisible_bricks = invisible_bricks;
            bullets[i]->toxic_mushrooms = toxic_mushrooms;
            bullets[i]->cur_scene = cur_scene;
        }


        // add coins
        coins_list = {
            {0, 620 - Floor_brick::floor_brick_height - 9 * Coin::coin_height},
            {0, 620 - Floor_brick::floor_brick_height - 11 * Coin::coin_height},
            {550, 620 - Floor_brick::floor_brick_height - 10 * Coin::coin_height},
            {600, 620 - Floor_brick::floor_brick_height - 14 * Coin::coin_height},
            {650, 620 - Floor_brick::floor_brick_height - 14 * Coin::coin_height},

            {1000, 620 - Floor_brick::floor_brick_height - Coin::coin_height},
            {1500, 620 - Floor_brick::floor_brick_height - 3 * Coin::coin_height},

            {1700, 620 - Floor_brick::floor_brick_height - 2 * Coin::coin_height},
            {1750, 620 - Floor_brick::floor_brick_height - 2 * Coin::coin_height},
            {2350, 620 - Floor_brick::floor_brick_height - 9 * Coin::coin_height},
            {2450, 620 - Floor_brick::floor_brick_height - 9 * Coin::coin_height},
            {2400, 620 - Floor_brick::floor_brick_height - 9 * Coin::coin_height},
            {2650, 620 - Floor_brick::floor_brick_height - 10 * Coin::coin_height},
            {2750, 620 - Floor_brick::floor_brick_height - 9 * Coin::coin_height},
            {2950, 620 - Floor_brick::floor_brick_height - 6 * Coin::coin_height},
            {2900, 620 - Floor_brick::floor_brick_height - 11 * Coin::coin_height},
            {2950, 620 - Floor_brick::floor_brick_height - 9 * Coin::coin_height},
            {3650, 620 - Floor_brick::floor_brick_height - 2 * Coin::coin_height},
            {3850, 620 - Floor_brick::floor_brick_height - 10 * Coin::coin_height},
            {3850, 620 - Floor_brick::floor_brick_height - 9 * Coin::coin_height},

            {800, stone_bricks_list[2][1] - Coin::coin_height}

        };
        for (int i = 0; i < static_cast<int>(coins_list.size()); i++) {
            coins.push_back(new Coin);
            coins[i]->set_xy(coins_list[i][0], coins_list[i][1]);
            cur_scene->addItem(coins[i]->coin_item);
        }

        // add mario
        mario.cur_scene = cur_scene;

        // 設定mario 的磚塊位置
        mario.floor_bricks = floor_bricks;
        mario.stone_bricks = stone_bricks;
        mario.normal_bricks = normal_bricks;
        mario.box_bricks = box_bricks;
        mario.broken_bricks = broken_bricks;
        mario.water_pipes = water_pipes;
        mario.invisible_bricks = invisible_bricks;
        mario.toxic_mushrooms = toxic_mushrooms;
        mario.super_mushrooms = super_mushrooms;
        mario.fire_flowers = fire_flowers;
        mario.bullets = bullets;

        mario.set_x(700);

        // 設定mario 初始hp
        mario.hp = &hp;


        cur_scene->addItem(mario.mario);

}

void MainWindow::game_restart() {
    qDebug() << "game_restart() Called";
    game_status = 1;
    view_x = Mario::init_x; // Equals to mario's x coordinates between the scenes;


    // Game Scene
        // add game_bg
        for (int i = 0; i < 5; i++) {
            game_bgs[i]->set(i);
        }

        // reset flag
        flag.reset();
        flag_pole.reset();

        // reset score text
        score.reset_score();

        // reset hp
        while(hp.get_hp()<3){
            hp.add_hp(1);
        }

        // add invisible_bricks
        for (int i = 0; i < static_cast<int>(invisible_bricks_list.size()); i++) {
            invisible_bricks[i]->set_xy(invisible_bricks_list[i][0], invisible_bricks_list[i][1]);
        }

        // add floor_bricks_items
        const int max_floor_brick_num_in_a_scene = 1400 / Floor_brick::floor_brick_width;
        for (int i = 0 ; i < 5 * max_floor_brick_num_in_a_scene ; i++) {
            if ((i+5) % max_floor_brick_num_in_a_scene == 0
                  || (i+6) % max_floor_brick_num_in_a_scene == 0)
                floor_bricks[i]->set_x(-100);
            else if(i > max_floor_brick_num_in_a_scene && i < 1.5 * max_floor_brick_num_in_a_scene)
                floor_bricks[i]->set_x(-100);
            else if(i > 2.65 * max_floor_brick_num_in_a_scene && i < 4 * max_floor_brick_num_in_a_scene)
                floor_bricks[i]->set_x(-100);
            else if(i > 4.6 * max_floor_brick_num_in_a_scene && i < 4.8 * max_floor_brick_num_in_a_scene)
                floor_bricks[i]->set_x(-100);

            else
                floor_bricks[i]->set_x(i * Floor_brick::floor_brick_width);
        }

        // add stone_bricks
        for (int i = 0; i < static_cast<int>(stone_bricks_list.size()); i++) {
            stone_bricks[i]->set_xy(stone_bricks_list[i][0], stone_bricks_list[i][1]);
        }

        // add normal_bricks
        for (int i = 0; i < static_cast<int>(normal_bricks_list.size()); i++) {
            normal_bricks[i]->set_xy(normal_bricks_list[i][0], normal_bricks_list[i][1]);
            normal_bricks[i]->init_y = normal_bricks_list[i][1];
        }

        // super_mushroom
        for (int i = 0; i < static_cast<int>(super_mushroom_list.size()); i++) {
            super_mushrooms[i]->set_xy(super_mushroom_list[i][0],super_mushroom_list[i][1]);
            super_mushrooms[i]->open = false;
        }

        // add box_bricks //蘑菇等獎勵的重新設置還未完成
        for (int i = 0; i < static_cast<int>(box_bricks.size()); i++) {
            box_bricks[i]->reset();
            box_bricks[i]->set_xy(box_bricks_list[i][0], box_bricks_list[i][1]);
            //box_bricks[i]->super_mushroom.set_xy(0,1000);
        }

        // add broken_bricks
        for (int i = 0; i < static_cast<int>(broken_bricks_list.size()); i++) {
            broken_bricks[i]->init_y = broken_bricks_list[i][1];
            broken_bricks[i]->reset(broken_bricks_list[i][0], broken_bricks_list[i][1]);
        }

        // add water_pipes
        for (int i = 0; i < static_cast<int>(water_pipes_list.size()); i++) {
            water_pipes[i]->set_xy(water_pipes_list[i][0], water_pipes_list[i][1]);
        }

        // add toxic mushrooms
        for (int i = 0; i < static_cast<int>(toxic_mushrooms_list.size()); i++) {
            toxic_mushrooms[i]->set_xy(toxic_mushrooms_list[i][0], toxic_mushrooms_list[i][1]);
            toxic_mushrooms[i]->init_y = toxic_mushrooms_list[i][1];
            toxic_mushrooms[i]->dead = false;
            toxic_mushrooms[i]->still = false;
            toxic_mushrooms[i]->dx = 0;
            toxic_mushrooms[i]->dy = 0;
            toxic_mushrooms[i]->hitted_left = false;
            toxic_mushrooms[i]->locked_in = false;
        }


        // add coins
        for (int i = 0; i < static_cast<int>(coins_list.size()); i++) {
            coins[i]->set_xy(coins_list[i][0], coins_list[i][1]);
        }

        // reset mario
        mario.reset();



        // 設定mario 初始hp
        mario.hp = &hp;
}


#endif // MAINWINDOW_GAME_INIT_H
