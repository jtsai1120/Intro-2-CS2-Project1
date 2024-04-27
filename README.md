# Project Mario
    This is a C++ OOP project using Qt to build a Mario game.

### Course
    Introduction to Computer Science 2 lectured by Prof. Yean-Ru Chen, in 2024 NCKUEE.

### Group 16
- 蔡承希 E24126270
- 蔡辰鑫 
- 黃士洵

# Basic Intro.

### Final Goal
    The game's final goal is to control Mario to capture the flag at the end of right side.
- If the following happens, the game is over and will reset the game : 
    1. Mario fall to the bottom of the hole, you **Lose**.
    2. Mario lose all HP, you **Lose**.
    3. Mario reach the flag with less than 21 coins ( score ), you **Lose**.
    4. Mario reach the flag wiht more than 20 coins ( score ), you **Win**.

### About Mario
#### HP
    Mario has 3 HP at most
- If Mario touch a super mushroom, HP increases 1 and turn bigger size.
- If Mario touch a toxic mushroom, HP decreases 1 and turn smaller size if he was in bigger size before.   

#### Movement
    You can control Mario by pressing the following keys on the keyboard.
- **'w'** : Jump 
    - Note : Double jump ( jump again while not grounded ) is not permitted.
- **'a'** : Move Left
- **'d'** : Move Right 

#### Shooting
    Mario can fire 3 bullets with mouse, only after he gets a fire flower.
    If a toxic mushroom is shot by the bullet, it will die immediately.

### About Bricks
    There are several bricks with different characteristics.
1. **Floor brick** : only appear on the ground, without speicific funtion.
2. **Stone brick** : a brick without specific function.
3. **Broken brick** : when being touched from below, the brick will break and disappear.
4. **Normal brick** : when being touched from below, either nothing happen or Mario gets a coin. However, it will turn to a Stone brick after Mario get 5 coins from it.
5. **Box brick** : when being touched from below, the brick will randomly generate a coin or a super mushroom or a fire flower and then transform into a Stone brick.
6. **Water pipe** : a huge brick without specifix function.

### About Items
    There are several items with different characteristics. Item will disappear after begin touch by Mario.
1. **Super mushroom** : will moving around or fall to ground. When Mario touch it, Mario Increase 1 HP and turn into bigger size if he was in smaller size before.   
2. **Fire flower** : // 打到第１７頁

### About Enemy
    There is only 1 kind of enemy.
- **Toxic Mushroom** : 

# How to Compile & Run


# Project Attainment
    What requirements and bonus we had done and implement in this project.
1. 
