# Intro-2-CS2-Project1
This is a C++ OOP project with using Qt to build a Mario game.

# Lesson
Introduction to Computer Science 2 lectured by Prof. Yean-Ru Chen, in 2024 NCKUEE.

# Group 16
- 蔡承希 E24126270
- 蔡辰鑫 
- 黃士洵

# 0416 Log (jtsai)

### 此次新增：
- 把 Game_bg, Floor_brick 等等都建立成 Class。
- 小更改 KeyPressEvent()
- 加入 all_move_detection()，用來檢查是馬力歐要動，還是其他所有物件要動
- 加入 all_move()
- 因為 game_init() (遊戲場景布置、初始化) 內容太多太大，因此新增一個 mainwindow_game_init.h 來寫。
- 修正 floor_brick 物件寫法，讓 Floor_brick(Class) 一次只生成一個 floor_brick(Object)，再把布置許多 floor_bricks 的工作交給 Mainwindow::game_init()
- 實現：mario 改變方向的同時，改圖片方向(換成反方向的圖片)

### 注意事項：
>  view_x 可以視為馬力歐的 x 座標，但並非馬力歐的真實座標，

### 預計下次要完成：
1. mario jump () (要先實現物件觸碰)
2. 新增更多 scene、物件
3. 敵人物件
4. 抵達終點->結束畫面
5. mario 跑步動畫 (setPixmap: run1_L -> run2_L -> run1_L -> ...)

### 思考如何實現：
1. 物件觸碰事件 --> 如何實現?

# 0407 Log (jtsai)

這次把 mario 加入進去了，但在寫 mario.move() 時發現應該不是 mario 要動，而是所有物件要動。

### 所以下次的任務：
1. 把所有物件(start_bg, game_bg, start_button, floor) 都寫成個別的 Class，且都要個別加上 x, y 屬性
2. 再把 mario 的 move() 移植到 mainwindow() 的 move()，讓 mainwindow 來呼叫所有物件 move

### 思考要怎麼實現的部分：
1. mario jump
2. mario 改變方向時也改圖片方向(換成反方向的圖片)
 

