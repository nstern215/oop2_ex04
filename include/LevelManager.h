#pragma once

#include <stack>

#include "Graph.h"
#include "Circle.h"
#include "Moves.h"

enum GameDifficulty
{
	STARTER,
	EASY,
	MEDIUM,
	HARD
};


class LevelManager{

public:
	LevelManager() = default;

	void setGameDifficulty();
};