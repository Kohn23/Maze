#pragma once
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Maze.h"
#include "Object.h"

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
	void HardMode();

private:
	Maze maze;
	Render render;
	HWND console;
};