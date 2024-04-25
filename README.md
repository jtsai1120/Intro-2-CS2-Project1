# Intro-2-CS2-Project1
This is a C++ OOP project with using Qt to build a Mario game.

# Lesson
Introduction to Computer Science 2 lectured by Prof. Yean-Ru Chen, in 2024 NCKUEE.

# Group 16
- 蔡承希 E24126270
- 蔡辰鑫 
- 黃士洵

// test

# 0425 Log (huang)
- 新增彈跳金幣特效及獲得上限

# 0420 Log (huang)
- 新增物件: invisible brick = 顏色和背景相同的stone brick
- 最遠起跳點用invisible brick 延長一些，大幅增加成功率
- 加入毒蘑菇，要下落過程擊中才能擊殺
-  修正毒蘑菇像素大小不一問題
- 毒蘑菇起始方向隨機似乎沒有成功
- 撞擊兩秒內免疫(之後使用無敵星星可以使用相同函式)

# 0419 Log (huang)
- 讓broken brick 順利從畫面消失
- 讓box brick 觸發後更換造型，且不能再重複觸發
- 畫了一張地圖

# 0418 Log (huang)
- 新增完整的5面背景
- normal block 的 bump 機制不完整
-  其他方塊完成填充(只有算進碰撞，沒有功能)

# 0417 Log (jtsai)

### 此次新增
- 新增 Mario.jump()、Mario.is_grounded()、Mario.check_whether_ground_brick()
- 改順 mario movement
- 太多了好懶

### 預計下次完成
1. HP (摔到洞裡、碰到敵人等等會扣血? 看題目報告)
2. 新增更多 scene、物件
3. 敵人物件
4. 抵達終點->結束畫面
5. mario 跑步動畫 (setPixmap: run1_L -> run2_L -> run1_L -> ...)
6. 碰撞偵測好像不能寫在 all_move_detection，因為有可能 mario 不移動但是敵人移動觸碰到 mario
    - 要讓敵人自己內部寫一個碰撞偵測

# 0416 Log (jtsai)

### 此次新增：
- 把 Game_bg, Floor_brick 等等都建立成 Class。
- 小更改 KeyPressEvent()
- 加入 all_move_detection()，用來檢查是馬力歐要動，還是其他所有物件要動
- 加入 all_move()
- 因為 game_init() (遊戲場景布置、初始化) 內容太多太大，因此新增一個 mainwindow_game_init.h 來寫。
- 修正 floor_brick 物件寫法，讓 Floor_brick(Class) 一次只生成一個 floor_brick(Object)，再把布置許多 floor_bricks 的工作交給 Mainwindow::game_init()
- 實現：mario 改變方向的同時，改圖片方向(換成反方向的圖片)
- 新增 Coin(Class)
- 新增碰撞偵測(放在mainwindow::all_move_detection)
- 新增 Score(Class) 
- 實現當 mario 觸碰到 coin 後，coin 會消失且 score += 1

### 注意事項：
-   view_x 可以視為馬力歐的 x 座標，但並非馬力歐的真實座標，
-  當 coin 被撿到時，雖然可以讓它從 cur_scene 消失，但它座標還是在那邊，所以仍會觸發碰撞式。因此我讓 coin 被碰到後 y 座標直接移到 1000，也就是完全消失在畫面中。


### 預計下次要完成：
1. mario jump & fall 
    - 想法：偵測 mario 左下角的點 ***(x, y+mario.height())*** 和右下角的點 ***(x+mario.width(), y+mario.height())*** 是否有碰撞磚塊類(幫所有磚塊進行標籤) 
    - 設立一個 bool is_grounded，若起跳或落下時為 0
    - 記得要實現重力加速度
2. 新增更多 scene、物件
3. 敵人物件
4. 抵達終點->結束畫面
5. mario 跑步動畫 (setPixmap: run1_L -> run2_L -> run1_L -> ...)
6. 碰撞偵測好像不能寫在 all_move_detection，因為有可能 mario 不移動但是敵人移動觸碰到 mario
    - 要讓敵人自己內部寫一個碰撞偵測嗎 ?

# 0407 Log (jtsai)

這次把 mario 加入進去了，但在寫 mario.move() 時發現應該不是 mario 要動，而是所有物件要動。

### 所以下次的任務：
1. 把所有物件(start_bg, game_bg, start_button, floor) 都寫成個別的 Class，且都要個別加上 x, y 屬性
2. 再把 mario 的 move() 移植到 mainwindow() 的 move()，讓 mainwindow 來呼叫所有物件 move

### 思考要怎麼實現的部分：
1. mario jump
2. mario 改變方向時也改圖片方向(換成反方向的圖片)
 

