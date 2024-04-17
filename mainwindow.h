#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ButtonItem.h"
#include "mario.h"
#include "game_bg.h"
#include "floor_brick.h"
#include "coin.h"
#include "score.h"
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

    protected:
        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);

    private slots:
        void update_frame(); // 畫面更新

        void on_start_button_clicked();

    private:
        int game_status; // 0:開始畫面, 1:遊戲中, 2:結束畫面

        void start_init();
        void game_init();
        //void end_init();

        void all_move_detection(); // 檢查是馬力歐要左右動、要跳，還是其他所有物件要動(隨view)
        void all_horizontal_move(int moving_unit);

        QGraphicsView *view = new QGraphicsView;
        int view_x; // Equals to mario's x coordinates between the scenes;

        QGraphicsScene *cur_scene;
        QGraphicsScene start_scene, game_scene, end_scene;

        QPixmap start_bg;
        QGraphicsPixmapItem *start_bg_item;

        QPushButton *start_button = new QPushButton;
        QPixmap start_button_pic;
        ButtonItem *start_button_item;

        // game scene
        Score score;
        Game_bg game_bg;
        std::vector<Floor_brick*> floor_bricks;
        Mario mario;
        std::vector<Coin*> coins;

        bool left_key_state, right_key_state, up_key_state;

        QTimer *refreshing_timer;

};
#endif // MAINWINDOW_H
