#pragma once
#include <iostream>
#include <vector>


// �Թ�����״̬
enum Cell { PATH, WALL, PLAYER };

// ��ͼ
using Map = std::vector<std::vector<int>>;
// �Թ���С
using Size = std::pair<int, int>;

// ��ṹ
struct Point
{
    int x, y;
    Point(int _x, int _y) :x(_x), y(_y) {}
};
