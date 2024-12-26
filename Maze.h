#pragma once
#include <graphics.h>
#include <list>

#include "Basic.h"
#include "Generator.h"
#include "Object.h"

class Maze final {
    friend class Render;
public:
    ~Maze() = default;
public:
    void setGenerator(MazeGenerator* newGenerator);
    void setMaze(Size _size, Point start, Point end);
    void setMaze(Size _size, Point start1, Point end1, Point start2, Point end2);
    bool query(Point position);
public:
    void updateObject(Player& obj);
    Kernel findPath(Point start, Point end);
private:
    Size size;
    std::unique_ptr<Map> maze;
    std::unique_ptr<MazeGenerator> generator;
};

class Render final {
private:
    bool _need_init{ true };

public:
    void operator()(Maze& obj, Point player1) noexcept;
    void operator()(Maze& obj, Point player1, Point player2) noexcept;
    void WinGame() noexcept;
    void LoseGame() noexcept;

private:
    static void drawMaze(const Maze& obj, Point player1, int width);
    static void drawMaze(const Maze& obj, Point player1, Point player2, int width);
};