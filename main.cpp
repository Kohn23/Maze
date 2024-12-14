#include "Maze.h"
#include <conio.h>
#include <queue>

bool Render::_need_init = true;

int main() {
	Maze maze;
	maze.SetGenerator(new _DFS_Generator);
	Point start(0, 1);
	Point end(20, 19);
	Point player(1, 1);
	maze.SetMaze({ 21,21 }, start, end);
    Render render;
	while (true)
	{
        // 检查是否到达终点
        if (player.x == end.x && player.y == end.y)
        {
            break;
        }

        // 获取玩家输入
        char ch = _getch();  // 获取一个字符输入
        if (ch == 'w' || ch == 'W') // 上
        {
            if (!maze.Query(Point(player.x,player.y-1))) player.y--;
        }
        else if (ch == 's' || ch == 'S') // 下
        {
            if (!maze.Query(Point(player.x,player.y+1))) player.y++;
        }
        else if (ch == 'a' || ch == 'A') // 左
        {
            if (!maze.Query(Point(player.x-1,player.y))) player.x--;
        }
        else if (ch == 'd' || ch == 'D') // 右
        {
            if (!maze.Query(Point(player.x+1,player.y))) player.x++;
        }

        maze.GetPlayer(player);
        render(maze);

        // 延时，控制画面刷新
        Sleep(100);
    }

    // 等待用户按键退出
    _getch();
    closegraph();
    return 0;
}
