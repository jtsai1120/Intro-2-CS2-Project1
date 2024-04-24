#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ButtonItem.h"
#include "mario.h"
#include "game_bg.h"
#include "coin.h"
#include "score.h"
#include "stone_brick.h"
#include "normal_brick.h"
#include "floor_brick.h"
#include "box_brick.h"
#include "broken_brick.h"
#include "water_pipe.h"
#include "invisible_brick.h"
#include "toxic_mushroom.h"
#include "super_mushroom.h"
#include "hp.h"
#include "flag.h"
#include "flag_pole.h"
#include <vector>
#include <string>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QPushButton>
#include <QKeyEvent>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        void end_init(); // 由 flag 物件呼叫

    protected:
        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);

    private slots:
        void update_frame(); // 畫面更新
        void on_start_button_clicked();
        void game_over_fade_in();
        void on_restart_button_clicked();

    private:
        int game_status; // 0:開始畫面, 1:遊戲中, 2:結束畫面

        void start_init();
        void game_init();
        void game_restart();


        void all_move_detection(); // 檢查是馬力歐要左右動、要跳，還是其他所有物件要動(隨view)
        void all_horizontal_move(int moving_unit);

        QGraphicsView *view = new QGraphicsView;
        int view_x; // Equals to mario's x coordinates between the scenes;

        QGraphicsScene *cur_scene;
        QGraphicsScene start_scene, game_scene;

        QPixmap start_bg;
        QGraphicsPixmapItem *start_bg_item;

        QPushButton *start_button = new QPushButton;
        QPixmap start_button_pic;
        ButtonItem *start_button_item;

        QPixmap game_over_bg;
        QGraphicsPixmapItem *game_over_bg_item;
        int game_over_object_x;
        QTimer *fade_in_timer;
        QGraphicsRectItem *rectItem;
        QGraphicsTextItem *win_or_lose_text;
        QPixmap restart_button_pic;
        QPushButton *restart_button = new QPushButton;
        ButtonItem *restart_button_item;

        // game scene
        Score score;
        Hp hp;
        Mario mario;
        std::vector<Game_bg*> game_bgs;

        Flag_pole flag_pole;
        Flag flag;

        std::vector<Coin*> coins;
        std::vector<Stone_brick*> stone_bricks;
        std::vector<Normal_brick*> normal_bricks;
        std::vector<Floor_brick*> floor_bricks;
        std::vector<Box_brick*> box_bricks;
        std::vector<Broken_brick*> broken_bricks;
        std::vector<Water_pipe*> water_pipes;
        std::vector<Invisible_brick*> invisible_bricks;
        std::vector<Toxic_mushroom*> toxic_mushrooms;
        std::vector<Super_mushroom*> super_mushrooms;

        //設定座標的，為了能重置因次宣告在外面
        std::vector<std::vector<int>> invisible_bricks_list;
        std::vector<std::vector<int>> stone_bricks_list;
        std::vector<std::vector<int>> normal_bricks_list;
        std::vector<std::vector<int>> broken_bricks_list;
        std::vector<std::vector<int>> super_mushroom_list;
        std::vector<std::vector<int>> box_bricks_list;
        std::vector<std::vector<int>> water_pipes_list;
        std::vector<std::vector<int>> toxic_mushrooms_list;
        std::vector<std::vector<int>> coins_list;


        // KeyEvents (Pressed=1, Released=0)
        bool left_key_state, right_key_state, up_key_state;

        QTimer *refreshing_timer;

};
#endif // MAINWINDOW_H
