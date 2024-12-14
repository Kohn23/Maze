#include "Maze.h"
#include <conio.h>

bool Render::_need_init = true;

int main() {
	Maze maze;
	maze.SetGenerator(new _DFS_Generator);
	Point start(0, 1);
	Point end(20, 19);
    std::queue<Point> player;
    player.push(Point(1, 1));
	maze.SetMaze({ 21,21 }, start, end);
    Render render;
	while (true)
	{
        maze.GetPlayer(player);
        render(maze);
        // 检查是否到达终点
        if (player.front().x == end.x && player.front().y == end.y)
        {
            break;
        }

        // 进行移动
        Point move = player.front();
        char ch = _getch();  // 获取一个字符输入
        if (ch == 'w' || ch == 'W') // 上
        {
            move += Point(0, -1);
            if (maze.Query(move)) player.push(move);
        }
        else if (ch == 's' || ch == 'S') // 下
        {
            move += Point(0, 1);
            if (maze.Query(move)) player.push(move);
        }
        else if (ch == 'a' || ch == 'A') // 左
        {
            move += Point(-1, 0);
            if (maze.Query(move)) player.push(move);
        }
        else if (ch == 'd' || ch == 'D') // 右
        {
            move += Point(1, 0);
            if (maze.Query(move)) player.push(move);
        }
        // 延时，控制画面刷新
        Sleep(100);
    }

    // 等待用户按键退出
    _getch();
    closegraph();
    return 0;
}
