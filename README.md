# Maze迷宫
## Design设计
Multilayer packaging, from a single block to the entire game, more like a sandbox.从单个方块到整个游戏的多层封装，偏沙盒。
## Supported operating system支持的操作系统
- windows10
- linux
## How to play基本玩法
### Open打开游戏
your folder must at least include:
```
data/
save/
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

Do not step in!不要踏入！
#### Walls墙类
- UnbreakableWall坚墙 "#",LF_yellow

Unbreakable.坚不可摧。
#### Texts文字
- Text文字 /,DF_black,DB_white

Texts could be moved if not blocked.如果不被阻挡，文字可以被推动。
#### Machines机器
- Exit出口 "%",LF_green

Press e and you will win!按e，你就赢了！
#### Comment注释
- LF=light font亮色前景
- DF=dark font暗色前景
- LB=light background亮色背景
- DB=dark background暗色背景
