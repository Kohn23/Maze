#include "Generator.h"

// 利用迭代进行DFS迷宫生成
Map* _DFS_Generator::generate(Size _size) {
	// 初始地图
	Map* maze = new Map;
	for (int i = 0; i < _size.first; ++i)
		maze->push_back(std::vector<int>());
	for (auto& row : *maze)
		for (int j = 0; j < _size.second; ++j)
			row.push_back(Cell::WALL);
    // 随机种子
    srand(static_cast<unsigned int>(time(NULL)));
    // 递归栈
    std::stack<Point> sp;
	// 方向
	static std::vector<std::vector<int>> dir{ {1,0},{-1,0},{0,1},{0,-1} };
	// （坐标为奇数）初始位置
	Point digger((rand() % (_size.first - 2) + 1) | 1, (rand() % (_size.second - 2) + 1) | 1);
	sp.push(digger);
    // DFS过程
    while (!sp.empty())
    {
        if ((*maze)[digger.x][digger.y] != Cell::PATH)
            (*maze)[digger.x][digger.y] = Cell::PATH;
        // 打乱方向
        std::random_shuffle(dir.begin(), dir.end());
        int i = 0;
        for (; i < 4; ++i)
        {
            if (digger.x + 2 * dir[i][0] >= 1 
                && digger.x + 2 * dir[i][0] <= _size.second - 2 
                && digger.y + 2 * dir[i][1] >= 1 
                && digger.y + 2 * dir[i][1] <= _size.first - 2
                && (*maze)[digger.x + 2 * dir[i][0]][digger.y + 2 * dir[i][1]] == Cell::WALL)
            {
                (*maze)[digger.x + dir[i][0]][digger.y + dir[i][1]] = Cell::PATH;
                digger.x += 2 * dir[i][0];
                digger.y += 2 * dir[i][1];
                sp.push(digger);
                break;
            }
        }
        if (i == 4) sp.pop();
        if (!sp.empty()) digger = sp.top();
    }

	return maze;
}