#include "Maze.h"

void Maze::setGenerator(MazeGenerator* newGenerator) {
	generator.reset(newGenerator);
}

void Maze::setMaze(Size _size, Point start, Point end) {
	try
	{
		if (generator == nullptr)
			throw std::runtime_error("_NULL_Generator");

		maze.reset(generator->generate(_size));
		(*maze)[start.x][start.y] = Cell::PATH;
		(*maze)[end.x][end.y] = Cell::PATH;
		size = _size;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error:" << e.what()  << std::endl << "Using _DFS_Generator..." << std::endl;
		// 默认使用DFS算法
		Maze::setGenerator(new _DFS_Generator);
		maze.reset(generator->generate(_size));
		size = _size;
	}
	return;
}

void Maze::setMaze(Size _size, Point start1, Point end1, Point start2, Point end2) {
	try
	{
		if (generator == nullptr)
			throw std::runtime_error("_NULL_Generator");

		maze.reset(generator->generate(_size));
		(*maze)[start1.x][start1.y] = Cell::PATH;
		(*maze)[start2.x][start2.y] = Cell::PATH;
		(*maze)[end1.x][end1.y] = Cell::PATH;
		(*maze)[end2.x][end2.y] = Cell::PATH;
		size = _size;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error:" << e.what() << std::endl << "Using _DFS_Generator..." << std::endl;
		// 默认使用DFS算法
		Maze::setGenerator(new _DFS_Generator);
		maze.reset(generator->generate(_size));
		size = _size;
	}
	return;
}

bool Maze::query(Point position) {
	if (position.x >= 0
		&& position.x <= size.second - 1
		&& position.y >= 0
		&& position.y <= size.first - 1)
		return (*maze)[position.x][position.y];
	else
		return Cell::WALL;
};

void Maze::updateObject(Player& obj) {
	try
	{
		Point _last_position = obj.fetchPosition();
		if (!query(_last_position))
			throw std::range_error("_Inappropriate_Position");
		// 如果没有移动
		if (obj.emptyPosition()) {
			obj.updateKernel(_last_position);
			return;
		}
		// 如果有移动
		Point _next_position = obj.fetchPosition();
		if (obj.emptyPosition())
		{
			if (query(_next_position))
			{
				obj.updateKernel(_next_position);
			}
			else
			{
				obj.updateKernel(_last_position);
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error:" << e.what() << std::endl;
	}
	return;
}

// dfs搜索路径
Kernel Maze::findPath(Point start, Point end) {
	Map* maze = this->maze.get();
	// 方向
	std::vector<std::vector<int>> dir{ {1,0},{0,1},{-1,0},{0,-1} };
	// DFS栈\为了最后返回一个kernel而用list来模拟栈
	std::list<Point> sp;
	Kernel kernel;
	Point finder = start;
	sp.push_back(finder);
	// DFS
	while (!sp.empty())
	{
		int i = 0;
		for (; i < 4; ++i)
		{
			if (finder.x + dir[i][0] >= 0
				&& finder.x + dir[i][0] <= size.second - 1
				&& finder.y + dir[i][1] >= 0
				&& finder.y + dir[i][1] <= size.first - 1
				&& (*maze)[finder.x + dir[i][0]][finder.y + dir[i][1]] == Cell::PATH)
			{
				// 标记
				(*maze)[finder.x][finder.y] = Cell::FLAG;
				finder.x += dir[i][0];
				finder.y += dir[i][1];
				sp.push_back(finder);
				if (finder == end) {
					for (const auto& point : sp) {
						kernel.push(point);
					}
					return kernel;
				}
				break;
			}
		}
		// 回溯
		if (i == 4)
		{
			(*maze)[finder.x][finder.y] = FLAG;
			sp.pop_back();
			if (!sp.empty()) finder = sp.back();
		}
	}
	// 还原
	for (auto& v1 : (*maze))
	{
		for (auto& v2 : v1)
		{
			if (v2 == Cell::FLAG) v2 = Cell::PATH;
		}
	}

	for (const auto& point : sp) {
		kernel.push(point);
	}
	return kernel;
}
