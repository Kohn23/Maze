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
    void updateObject(Player& obj);
    bool query(Point position);
public:
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
    void operator()(Maze& obj, Point player) noexcept;
    void EndGame() noexcept;

private:
    static void drawMaze(const Maze& obj, Point player, int width);
};