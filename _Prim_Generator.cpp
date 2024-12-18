#include "Generator.h"


Map* _Prim_Generator::generate(Size _size) {
	Map* maze = new Map;
    // 先初始化地图，再形成基础
    for (int i = 0; i < _size.first; ++i)
        maze->push_back(std::vector<int>());
    for (auto& row : *maze)
        for (int j = 0; j < _size.second; ++j)
            row.push_back(Cell::WALL);
    for (int i = 1; i <= _size.first - 2; i += 2)
        for (int j = 1; j <= _size.second - 2; j += 2)
            (*maze)[i][j] = Cell::PATH;
    // 随机种子
    srand(static_cast<unsigned int>(time(NULL)));
    // 记录容器
    std::vector<Point> vp;
    // 随机初始化挖墙起点
    Point digger((rand() % (_size.first - 2) + 1) | 1, (rand() % (_size.second - 2) + 1) | 1);
    if (digger.x - 1 >= 2) vp.push_back(Point(digger.x - 1, digger.y));
    if (digger.x + 1 <= _size.first - 3) vp.push_back(Point(digger.x + 1, digger.y));
    if (digger.y - 1 >= 2) vp.push_back(Point(digger.x, digger.y - 1));
    if (digger.y + 1 <= _size.second - 3) vp.push_back(Point(digger.x, digger.y + 1));

    // 标记该通路
    (*maze)[digger.x][digger.y] = Cell::FLAG;
    int pos = 0;
    // 后续迭代生成迷宫
    while (!vp.empty())
    {
        // 在墙容器中随机选取一堵墙
        pos = rand() % vp.size();
        digger = vp[pos];
        // 记录该墙是否打通
        bool flag = false;
        if ((*maze)[digger.x + 1][digger.y] == Cell::WALL) // 判断是属于行还是属于列的墙
        {
            if ((*maze)[digger.x][digger.y - 1] != (*maze)[digger.x][digger.y + 1]) //判断两侧是否一侧为PATH，另一侧为Cell::FLAG
            {
                (*maze)[digger.x][digger.y] = Cell::PATH;
                // 对新加入的通路进行标记
                if ((*maze)[digger.x][digger.y - 1] == Cell::FLAG) { (*maze)[digger.x][digger.y + 1] = Cell::FLAG; ++digger.y; }
                else { (*maze)[digger.x][digger.y - 1] = Cell::FLAG; --digger.y; }
                flag = true;
            }
        }
        else
        {
            if ((*maze)[digger.x - 1][digger.y] != (*maze)[digger.x + 1][digger.y])
            {
                (*maze)[digger.x][digger.y] = Cell::PATH;
                // 对新加入的通路进行标记
                if ((*maze)[digger.x - 1][digger.y] == Cell::FLAG) { (*maze)[digger.x + 1][digger.y] = Cell::FLAG; ++digger.x; }
                else { (*maze)[digger.x - 1][digger.y] = Cell::FLAG; --digger.x; }
                flag = true;
            }
        }
        if (flag)
        {
            if (digger.x - 1 >= 2 && (*maze)[digger.x - 1][digger.y] == Cell::WALL) vp.push_back(Point(digger.x - 1, digger.y));
            if (digger.x + 1 <= _size.first - 3 && (*maze)[digger.x + 1][digger.y] == Cell::WALL) vp.push_back(Point(digger.x + 1, digger.y));
            if (digger.y - 1 >= 2 && (*maze)[digger.x][digger.y - 1] == Cell::WALL) vp.push_back(Point(digger.x, digger.y - 1));
            if (digger.y + 1 <= _size.second - 3 && (*maze)[digger.x][digger.y + 1] == Cell::WALL) vp.push_back(Point(digger.x, digger.y + 1));
        }
        // 用最后一个元素来覆盖这个元素
        vp[pos] = *(vp.end() - 1);
        vp.pop_back();
    }
    // 将被标记的通路还原
    for (auto& v1 : (*maze))
        for (auto& v2 : v1)
            if (v2 == Cell::FLAG) v2 = Cell::PATH;
    return maze;
}


