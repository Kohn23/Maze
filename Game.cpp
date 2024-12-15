#include "Game.h"

void Game::initGame() {
    int status; // 使用 int 来接收 getchar() 的返回值
    while (true) {
        status = Menu();
        switch (status) {
        case 'e': // 简单模式
            EasyMode();
            break;
        case 'h': // 困难模式
            std::cout << std::endl << "敬请期待！" << std::endl;
            break;
        case 'q': // 退出游戏
            exit(0); // 退出程序
            break;
        default:
            // 处理无效输入
            std::cout << std::endl << "无效输入，请重新输入！" << std::endl;
            break;
        }
    }
}
char Game::Menu() {
    Sleep(1000);
    system("cls");
	std::cout << std::endl <<
        "********************************************" << std::endl <<
		"***************** 迷宫游戏 *****************" << std::endl <<
		"********************************************" << std::endl <<
		"请选择模式：" << std::endl <<
		"简单模式（e)" << std::endl <<
		"困难模式（h)" << std::endl <<
		"退出游戏（q)" << std::endl <<
		"输入对应小写字母：";
	char status = getchar();
    getchar();
    return status;
}

// 简单模式，小迷宫，只有一条主路，使用DFS算法生成迷宫
void Game::EasyMode() {
    int size = 21;
    Point start(0, 1);
    Point end(size - 1, size - 2);
    player.push(start);

    maze.SetGenerator(new _DFS_Generator);
    maze.SetMaze({ size,size }, start, end);
    while (true)
    {
        maze.GetPlayer(player);
        render(maze);
        // 检查是否到达终点
        if (player.front().x == end.x && player.front().y == end.y)
        {
            render.EndGame();
            Sleep(3000);
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
    }

    closegraph();
    return;
}