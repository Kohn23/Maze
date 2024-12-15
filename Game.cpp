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
            std::cout << std::endl << "�����ڴ���" << std::endl;
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

// ��ģʽ��С�Թ���ֻ��һ����·��ʹ��DFS�㷨�����Թ�
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
        // ����Ƿ񵽴��յ�
        if (player.front().x == end.x && player.front().y == end.y)
        {
            render.EndGame();
            Sleep(3000);
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
    }

    closegraph();
    return;
}