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
        // ����Ƿ񵽴��յ�
        if (player.x == end.x && player.y == end.y)
        {
            break;
        }

        // ��ȡ�������
        char ch = _getch();  // ��ȡһ���ַ�����
        if (ch == 'w' || ch == 'W') // ��
        {
            if (!maze.Query(Point(player.x,player.y-1))) player.y--;
        }
        else if (ch == 's' || ch == 'S') // ��
        {
            if (!maze.Query(Point(player.x,player.y+1))) player.y++;
        }
        else if (ch == 'a' || ch == 'A') // ��
        {
            if (!maze.Query(Point(player.x-1,player.y))) player.x--;
        }
        else if (ch == 'd' || ch == 'D') // ��
        {
            if (!maze.Query(Point(player.x+1,player.y))) player.x++;
        }

        maze.GetPlayer(player);
        render(maze);

        // ��ʱ�����ƻ���ˢ��
        Sleep(100);
    }

    // �ȴ��û������˳�
    _getch();
    closegraph();
    return 0;
}
