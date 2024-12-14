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
        // ����Ƿ񵽴��յ�
        if (player.front().x == end.x && player.front().y == end.y)
        {
            break;
        }

        // �����ƶ�
        Point move = player.front();
        char ch = _getch();  // ��ȡһ���ַ�����
        if (ch == 'w' || ch == 'W') // ��
        {
            move += Point(0, -1);
            if (maze.Query(move)) player.push(move);
        }
        else if (ch == 's' || ch == 'S') // ��
        {
            move += Point(0, 1);
            if (maze.Query(move)) player.push(move);
        }
        else if (ch == 'a' || ch == 'A') // ��
        {
            move += Point(-1, 0);
            if (maze.Query(move)) player.push(move);
        }
        else if (ch == 'd' || ch == 'D') // ��
        {
            move += Point(1, 0);
            if (maze.Query(move)) player.push(move);
        }
        // ��ʱ�����ƻ���ˢ��
        Sleep(100);
    }

    // �ȴ��û������˳�
    _getch();
    closegraph();
    return 0;
}
