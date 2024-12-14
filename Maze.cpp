#include "Maze.h"

void Maze::SetGenerator(MazeGenerator* newGenerator) {
	generator.reset(newGenerator);
}

void Maze::SetMaze(Size _size, Point start, Point end) {
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
		Maze::SetGenerator(new _DFS_Generator);
		maze.reset(generator->generate(_size));
		size = _size;
	}
	return;
}

bool Maze::Query(Point position) {
	if (position.x >= 0
		&& position.x <= size.second - 1
		&& position.y >= 0
		&& position.y <= size.first - 1)
		return (*maze)[position.x][position.y];
	else
		return Cell::WALL;
}

void Maze::GetPlayer(Point player) {
	try
	{
		if(Query(player))
			throw std::range_error("_Inappropriate_Position");

		(*maze)[player.x][player.y] = Cell::PLAYER;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error:" << e.what() << std::endl;
	}
	return;
}


