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
            HardMode();
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

// 简单模式，小迷宫，只有一条主路，使用Prim算法生成迷宫
void Game::EasyMode() {
    int width = 21;
    int height = 21;
    Point start(0, 1);
    Point end(width - 1, height - 2);

    Player player(start);
    maze.setGenerator(new _Prim_Generator);
    maze.setMaze({ width,height }, start, end);
    while (true)
    {
        maze.updateObject(player);
        render(maze,player.getPosition());
        // 检查是否到达终点
        if (player.getPosition() == end)
        {
            render.EndGame();
            Sleep(3000);
            break;
        }
        // 进行移动
        player.move();
    }

    closegraph();
    return;
}

// 困难模式，大迷宫，只有一条主路，使用DFS算法生成迷宫
void Game::HardMode() {
    int width = 49;
    int height = 49;
    Point start(0, 1);
    Point end(width - 1, height - 2);
    
    Player player(start);
    maze.setGenerator(new _DFS_Generator);
    maze.setMaze({ width,height }, start, end);
    while (true)
    {
        maze.updateObject(player);
        render(maze,player.getPosition());
        // 检查是否到达终点
        if (player.getPosition() == end)
        {
            render.EndGame();
            Sleep(3000);
            break;
        }

        // 进行移动
        player.move();
    }

    closegraph();
    return;
}