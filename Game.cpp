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
        case 'a': // 自动模式
            AutoMode();
            break;
        case 'c': // 自动模式
            CompeteMode();
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
            render.WinGame();
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
    maze.setGenerator(new _DFS_Generator);
    maze.setMaze({ width,height }, start, end);

    Player player(start);
    while (true)
    {
        maze.updateObject(player);
        render(maze,player.getPosition());
        // 检查是否到达终点
        if (player.getPosition() == end)
        {
            render.WinGame();
            Sleep(3000);
            break;
        }

        // 进行移动
        player.move();
    }

    closegraph();
    return;
}

// 自动模式，大迷宫，只有一条主路，使用DFS算法生成迷宫，人机自动寻路
void Game::AutoMode() {
    int width = 49;
    int height = 49;
    Point start(0, 1);
    Point end(width - 1, height - 2);
    maze.setGenerator(new _DFS_Generator);
    maze.setMaze({ width,height }, start, end);

    AutoPilot player(start);
    player.updateKernel(maze.findPath(start, end));
    while (true)
    {
        render(maze, player.getPosition());
        // 检查是否到达终点
        if (player.getPosition() == end)
        {
            render.WinGame();
            Sleep(3000);
            break;
        }

        // 进行移动
        player.move();
        Sleep(50);
    }

    closegraph();
    return;
}

#include <thread>
#include <atomic>
#include <mutex>

// 全局变量
std::atomic<bool> gameRunning(true); // 游戏运行状态标志
std::mutex gameMutex; // 用于同步访问游戏状态的互斥锁

void Game::CompeteMode() {
    int width = 49;
    int height = 49;
    Point start1(0, 1), start2(0, height - 2);
    Point end1(width - 1, height - 2), end2(width - 1, 1);


    maze.setGenerator(new _DFS_Generator);
    maze.setMaze({ width, height }, start1, end1, start2, end2);

    Player player(start1);
    AutoPilot computerPlayer(start2); // 假设你有一个ComputerPlayer类
    computerPlayer.updateKernel(maze.findPath(start2, end2));

    // 玩家线程函数
    std::thread playerThread([&]() {
        while (gameRunning) {
            std::unique_lock<std::mutex> lock(gameMutex);
            maze.updateObject(player);
            render(maze, player.getPosition(), computerPlayer.getPosition());
            if (player.getPosition() == end1) {
                render.WinGame();
                gameRunning = false;
            }
            lock.unlock();
            player.move();
        }
        });

    // 电脑玩家线程函数
    std::thread computerThread([&]() {
        while (gameRunning) {
            std::unique_lock<std::mutex> lock(gameMutex);
            render(maze, player.getPosition(), computerPlayer.getPosition());
            if (computerPlayer.getPosition() == end2) {
                render.LoseGame();
                gameRunning = false;
            }
            lock.unlock();
            computerPlayer.move();
            Sleep(50); // 模拟电脑玩家操作的延迟
        }
        });

    // 等待两个线程结束
    playerThread.join();
    computerThread.join();

    Sleep(3000);
    closegraph();
    return;
}