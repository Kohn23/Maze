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
            render.EndGame();
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
    
    Player player(start);
    maze.setGenerator(new _DFS_Generator);
    maze.setMaze({ width,height }, start, end);
    while (true)
    {
        maze.updateObject(player);
        render(maze,player.getPosition());
        // ����Ƿ񵽴��յ�
        if (player.getPosition() == end)
        {
            render.EndGame();
            Sleep(3000);
            break;
        }

        // �����ƶ�
        player.move();
    }

    closegraph();
    return;
}

//#include <thread>
//#include <atomic>
//#include <mutex>
//
//// ȫ�ֱ���
//std::atomic<bool> gameRunning(true); // ��Ϸ����״̬��־
//std::mutex gameMutex; // ����ͬ��������Ϸ״̬�Ļ�����
//
//void Game::HardMode() {
//    int width = 49;
//    int height = 49;
//    Point start(0, 1);
//    Point end(width - 1, height - 2);
//
//    Player player(start);
//    ComputerPlayer computerPlayer(end); // ��������һ��ComputerPlayer��
//    maze.setGenerator(new _DFS_Generator);
//    maze.setMaze({ width, height }, start, end);
//
//    // ����̺߳���
//    std::thread playerThread([&]() {
//        while (gameRunning) {
//            std::unique_lock<std::mutex> lock(gameMutex);
//            maze.updateObject(player);
//            render(maze, player.getPosition());
//            if (player.getPosition() == end) {
//                render.EndGame();
//                gameRunning = false;
//            }
//            lock.unlock();
//            player.move();
//            Sleep(100); // ģ����Ҳ������ӳ�
//        }
//        });
//
//    // ��������̺߳���
//    std::thread computerThread([&]() {
//        while (gameRunning) {
//            std::unique_lock<std::mutex> lock(gameMutex);
//            maze.updateObject(computerPlayer);
//            render(maze, computerPlayer.getPosition());
//            if (computerPlayer.getPosition() == end) {
//                render.EndGame();
//                gameRunning = false;
//            }
//            lock.unlock();
//            computerPlayer.move();
//            Sleep(100); // ģ�������Ҳ������ӳ�
//        }
//        });
//
//    // �ȴ������߳̽���
//    playerThread.join();
//    computerThread.join();
//
//    closegraph();
//    return;
//}