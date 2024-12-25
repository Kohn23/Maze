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
		// Ĭ��ʹ��DFS�㷨
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
};

void Maze::Update(Object& obj) {
	try
	{
		Point _last_position = obj.updateKernel();
		if (!Query(_last_position))
			throw std::range_error("_Inappropriate_Position");
		// ���û���ƶ�
		if (obj.emptyPosition()) {
			obj.updateKernel(_last_position);
			(*maze)[_last_position.x][_last_position.y] = Cell::PLAYER;
			return;
		}
		// ������ƶ�
		Point _next_position = obj.updateKernel();
		if (Query(_next_position))
		{
			obj.updateKernel(_next_position);
			(*maze)[_last_position.x][_last_position.y] = Cell::PATH;
			(*maze)[_next_position.x][_next_position.y] = Cell::PLAYER;
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