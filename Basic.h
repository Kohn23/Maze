#pragma once
#include <iostream>
#include <vector>
#include <queue>


// 迷宫格子状态
enum Cell { WALL, PATH, PLAYER, FLAG };
// 地图
using Map = std::vector<std::vector<int>>;
// 迷宫大小
using Size = std::pair<int, int>;
// 点结构
struct Point
{
    int x, y;
    Point(int _x, int _y) :x(_x), y(_y) {}
    // 重载函数
    void operator+=(Point movement) { x += movement.x; y += movement.y; }
    bool operator==(Point p) { return (x == p.x) && (y == p.y); }
};
