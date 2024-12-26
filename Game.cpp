#include "Game.h"

void Game::initGame() {
    int status; // ʹ�� int ������ getchar() �ķ���ֵ
    while (true) {
        status = Menu();
        switch (status) {
        case 'e': // ��ģʽ
            EasyMode();
            break;
        case 'h': // ����ģʽ
            HardMode();
            break;
        case 'a': // �Զ�ģʽ
            AutoMode();
            break;
        case 'c': // �Զ�ģʽ
            CompeteMode();
            break;
        case 'q': // �˳���Ϸ
            exit(0); // �˳�����
            break;
        default:
            // ������Ч����
            std::cout << std::endl << "��Ч���룬���������룡" << std::endl;
            break;
        }
    }
}

char Game::Menu() {
    Sleep(1000);
    system("cls");
	std::cout << std::endl <<
        "********************************************" << std::endl <<
		"***************** �Թ���Ϸ *****************" << std::endl <<
		"********************************************" << std::endl <<
		"��ѡ��ģʽ��" << std::endl <<
		"��ģʽ��e)" << std::endl <<
		"����ģʽ��h)" << std::endl <<
		"�˳���Ϸ��q)" << std::endl <<
		"�����ӦСд��ĸ��";
	char status = getchar();
    getchar();
    return status;
}

// ��ģʽ��С�Թ���ֻ��һ����·��ʹ��Prim�㷨�����Թ�
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
        // ����Ƿ񵽴��յ�
        if (player.getPosition() == end)
        {
            render.WinGame();
            Sleep(3000);
            break;
        }
        // �����ƶ�
        player.move();
    }

    closegraph();
    return;
}

// ����ģʽ�����Թ���ֻ��һ����·��ʹ��DFS�㷨�����Թ�
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
        // ����Ƿ񵽴��յ�
        if (player.getPosition() == end)
        {
            render.WinGame();
            Sleep(3000);
            break;
        }

        // �����ƶ�
        player.move();
    }

    closegraph();
    return;
}

// �Զ�ģʽ�����Թ���ֻ��һ����·��ʹ��DFS�㷨�����Թ����˻��Զ�Ѱ·
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
        // ����Ƿ񵽴��յ�
        if (player.getPosition() == end)
        {
            render.WinGame();
            Sleep(3000);
            break;
        }

        // �����ƶ�
        player.move();
        Sleep(50);
    }

    closegraph();
    return;
}

#include <thread>
#include <atomic>
#include <mutex>

// ȫ�ֱ���
std::atomic<bool> gameRunning(true); // ��Ϸ����״̬��־
std::mutex gameMutex; // ����ͬ��������Ϸ״̬�Ļ�����

void Game::CompeteMode() {
    int width = 49;
    int height = 49;
    Point start1(0, 1), start2(0, height - 2);
    Point end1(width - 1, height - 2), end2(width - 1, 1);


    maze.setGenerator(new _DFS_Generator);
    maze.setMaze({ width, height }, start1, end1, start2, end2);

    Player player(start1);
    AutoPilot computerPlayer(start2); // ��������һ��ComputerPlayer��
    computerPlayer.updateKernel(maze.findPath(start2, end2));

    // ����̺߳���
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

    // ��������̺߳���
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
            Sleep(50); // ģ�������Ҳ������ӳ�
        }
        });

    // �ȴ������߳̽���
    playerThread.join();
    computerThread.join();

    Sleep(3000);
    closegraph();
    return;
}