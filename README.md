# Maze迷宫
## Design设计
Multilayer packaging, from a single block to the entire game, more like a sandbox.从单个方块到整个游戏的多层封装，偏沙盒。
## Supported operating system支持的操作系统
- windows10
- linux
## How to play基本玩法
### Open打开游戏

#### If you haven't got an excutable file.如果你还没有可执行文件
run `[complier path] -std=c++11 [code path]/cpp11/main.cpp [code path]/cpp11/maze-game.cpp [code path]/cpp11/maze-chunk.cpp [code path]/cpp11/maze-base.cpp [code path]/cpp11/paint.cpp -o [code path]/maze.exe`

e.g. (using g++,code path=`D:/C++`):`g++ -std=c++11 D:/C++/Maze/cpp11/main.cpp D:/C++/Maze/cpp11/maze-game.cpp D:/C++/Maze/cpp11/maze-chunk.cpp D:/C++/Maze/cpp11/maze-base.cpp D:/C++/Maze/cpp11/paint.cpp -o D:/C++/Maze/maze.exe`

#### And then然后……
your folder must at least include:
```
data/levels.data
maze.exe (or other excutable files)
```
Run maze.exe
### Input输入
Press `Enter` to confirm after you input your choice.输入你的选择后按回车。

Use w,a,s,d to move.使用wasd移动。

Use q to quit.按q退出。

Use e to "use" a machine.按e使用机器。

### Player玩家
- "!"
- Default Health:10默认生命值为10
### Blocks方块
- Void虚空 " ",LB_purple
#### Walls墙类
- UnbreakableWall坚墙 "#",LF_yellow
#### Texts文字
- Text文字 /,DF_black,DB_white
#### Machines机器
- Exit出口 "%",LF_green
#### Comment注释
- LF=light font亮色前景
- DF=dark font暗色前景
- LB
- DB
