#pragma once
#include <graphics.h>
#include "Generator.h"

class Maze final {
    friend class Render;
public:
    ~Maze() = default;
public:
    void SetGenerator(MazeGenerator* newGenerator);
    void SetMaze(Size _size, Point start, Point end);
    void GetPlayer(Point player);
    bool Query(Point position);
    void Disp();
private:
    Size size;
    std::unique_ptr<Map> maze;
    std::unique_ptr<MazeGenerator> generator;
};

class Render final {
private:
    static bool _need_init;

public:
    void operator()(Maze& obj) noexcept {
        const int width = 15;
        if (_need_init)
        {
            initgraph(obj.size.second * width, obj.size.first * width);
            _need_init = false;
        }
        setlinecolor(DARKGRAY);
        setfillcolor(LIGHTGRAY);

        cleardevice();
        // 调用静态私有成员函数绘制迷宫
        drawMaze(obj, width);
    }

private:
    static void drawMaze(const Maze& obj, int width) {
        const Map* map = obj.maze.get();
        for (int j = 0; j < obj.size.second; ++j) {
            for (int i = 0; i < obj.size.first; ++i) {
                if ((*map)[i][j] == Cell::WALL) {
                    fillrectangle(i * width, j * width, (i + 1) * width - 1, (j + 1) * width - 1);
                }
                else if ((*map)[i][j] == Cell::PLAYER) {
                    setfillcolor(RED);
                    fillrectangle(i * width, j * width, (i + 1) * width - 1, (j + 1) * width - 1);
                    setfillcolor(LIGHTGRAY);
                }
            }
        }
    }

};

