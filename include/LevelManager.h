#pragma once

#include <stack>

#include "Graph.h"
#include "Circle.h"
#include "Moves.h"


class LevelManager{

public:
	LevelManager();

	std::list<std::pair<int, int>> LoadLevel(int level);
	std::list<std::pair<int, int>> LoadNextLevel();

	int getCurrentLevel() const;
	int getNumOfLevels() const;

	void reset();

private:
	int m_level;
	const int m_numOfLevels = 4;
	const int m_row = 11;
	const int m_col = 11;
};