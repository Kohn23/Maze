#pragma once
#include <iostream>
#include <vector>
#include <queue>


// �Թ�����״̬
enum Cell { WALL, PATH, PLAYER, FLAG };
// ��ͼ
using Map = std::vector<std::vector<int>>;
// �Թ���С
using Size = std::pair<int, int>;
// ��ṹ
struct Point
{
    int x, y;
    Point(int _x, int _y) :x(_x), y(_y) {}
    // ���غ���
    void operator+=(Point movement) { x += movement.x; y += movement.y; }
    bool operator==(Point p) { return (x == p.x) && (y == p.y); }
};
