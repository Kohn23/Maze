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

bool Maze::query(Point position) {
	if (position.x >= 0
		&& position.x <= size.second - 1
		&& position.y >= 0
		&& position.y <= size.first - 1)
		return (*maze)[position.x][position.y];
	else
		return Cell::WALL;
};

void Maze::updateObject(Object& obj) {
	try
	{
		Point _last_position = obj.updateKernel();
		if (!query(_last_position))
			throw std::range_error("_Inappropriate_Position");
		// 如果没有移动
		if (obj.emptyPosition()) {
			obj.updateKernel(_last_position);
			return;
		}
		// 如果有移动
		Point _next_position = obj.updateKernel();
		if (query(_next_position))
		{
			obj.updateKernel(_next_position);
		}
		else
		{
			obj.updateKernel(_last_position);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error:" << e.what() << std::endl;
	}
	return;
}