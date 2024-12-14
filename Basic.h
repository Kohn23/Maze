#pragma once
#include <iostream>
#include <vector>


// 迷宫格子状态
enum Cell { PATH, WALL, PLAYER };

// 地图
using Map = std::vector<std::vector<int>>;
// 迷宫大小
using Size = std::pair<int, int>;

// 点结构
struct Point
{
    int x, y;
    Point(int _x, int _y) :x(_x), y(_y) {}
};
