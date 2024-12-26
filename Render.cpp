#include "Maze.h"

void Render::operator()(Maze& obj, Point player1) noexcept {
    const int width = 20;
    if (_need_init)
    {
        initgraph(obj.size.second * width, obj.size.first * width);
        _need_init = false;
    }
    setlinecolor(DARKGRAY);
    setfillcolor(LIGHTGRAY);

    cleardevice();
    // 调用静态私有成员函数绘制迷宫
    drawMaze(obj, player1, width);
}

void Render::operator()(Maze& obj, Point player1, Point player2) noexcept {
    const int width = 20;
    if (_need_init)
    {
        initgraph(obj.size.second * width, obj.size.first * width);
        _need_init = false;
    }
    setlinecolor(DARKGRAY);
    setfillcolor(LIGHTGRAY);

    cleardevice();
    // 调用静态私有成员函数绘制迷宫
    drawMaze(obj, player1, player2, width);
}

void Render::drawMaze(const Maze& obj, Point player1, int width) {
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
    fillrectangle(player1.x * width, player1.y * width, (player1.x + 1) * width - 1, (player1.y + 1) * width - 1);
    setfillcolor(LIGHTGRAY);
    EndBatchDraw();
}

void Render::drawMaze(const Maze& obj, Point player1, Point player2, int width) {
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
    fillrectangle(player1.x * width, player1.y * width, (player1.x + 1) * width - 1, (player1.y + 1) * width - 1);
    setfillcolor(GREEN);
    fillrectangle(player2.x * width, player2.y * width, (player2.x + 1) * width - 1, (player2.y + 1) * width - 1);
    setfillcolor(LIGHTGRAY);
    EndBatchDraw();
}


void Render::EndGame() noexcept {
    _need_init = true;
    settextcolor(RED);
    settextstyle(48, 0, _T("Consolas"));
    int x = (getmaxx() - textwidth(_T("You Win!"))) / 2; // 计算文本宽度并居中
    int y = (getmaxy() - textheight(_T("You Win!"))) / 2 + textheight(_T("You Win!")); // 计算文本高度并居中
    outtextxy(x, y, _T("You Win!")); // 在指定位置绘制 "You Win!" 文字
}