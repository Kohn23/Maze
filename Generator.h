#pragma once
#include <stack>
#include <ctime>
#include <algorithm>

#include "Basic.h"

// ���Խӿ�
class MazeGenerator {
public:
	MazeGenerator& operator=(const MazeGenerator&) = delete;
	virtual ~MazeGenerator() = default;

public:
	virtual Map* generate(Size _size) = 0;
};

// �������
class _DFS_Generator final : public MazeGenerator {
public:
	virtual Map* generate(Size _size) override;
};

class _Prim_Generator final : public MazeGenerator {
public:
	virtual Map* generate(Size _size) override;
};