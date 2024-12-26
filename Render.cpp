#include "Maze.h"

void Render::operator()(Maze& obj, Point player) noexcept {
    const int width = 20;
    if (_need_init)
    {
        initgraph(obj.size.second * width, obj.size.first * width);
        _need_init = false;
    }
    setlinecolor(DARKGRAY);
    setfillcolor(LIGHTGRAY);

    cleardevice();
    // ���þ�̬˽�г�Ա���������Թ�
    drawMaze(obj, player, width);
}

void Render::EndGame() noexcept {
    _need_init = true;
    settextcolor(RED);
    settextstyle(48, 0, _T("Consolas"));
    int x = (getmaxx() - textwidth(_T("You Win!"))) / 2; // �����ı���Ȳ�����
    int y = (getmaxy() - textheight(_T("You Win!"))) / 2 + textheight(_T("You Win!")); // �����ı��߶Ȳ�����
    outtextxy(x, y, _T("You Win!")); // ��ָ��λ�û��� "You Win!" ����
}


void Render::drawMaze(const Maze& obj, Point player, int width) {
    const Map* map = obj.maze.get();
    BeginBatchDraw();
    for (int j = 0; j < obj.size.second; ++j) {
        for (int i = 0; i < obj.size.first; ++i) {
            if ((*map)[i][j] == Cell::WALL) {
                fillrectangle(i * width, j * width, (i + 1) * width - 1, (j + 1) * width - 1);
            }
        }
    }
    setfillcolor(RED);
    fillrectangle(player.x * width, player.y * width, (player.x + 1) * width - 1, (player.y + 1) * width - 1);
    setfillcolor(LIGHTGRAY);
    EndBatchDraw();
}