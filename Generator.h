#pragma once
#include <stack>
#include <algorithm>
#include "Basic.h"

// Interface_of_Strategy
class MazeGenerator {
public:
	MazeGenerator& operator=(const MazeGenerator&) = delete;
	virtual ~MazeGenerator() = default;

public:
	virtual Map* generate(Size _size) = 0;
};


class _DFS_Generator : public MazeGenerator {
public:
	virtual Map* generate(Size _size) override;
};