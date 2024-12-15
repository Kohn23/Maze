#pragma once
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Maze.h"

class Game final {
public:
	Game(void) = default;
	~Game(void) = default;
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

public:
	void initGame();

private:
	char Menu();
	void EasyMode();

private:
	Maze maze;
	Render render;
	Player player;
};