#include <random>

#include "LevelManager.h"

#include <unordered_map>

LevelManager::LevelManager():
	m_level(0)
{}

int LevelManager::getCurrentLevel() const
{
	return m_level;
}

int LevelManager::getNumOfLevels() const
{
	return m_numOfLevels;
}

std::list<std::pair<int, int>> LevelManager::LoadNextLevel()
{
	return LoadLevel(++m_level);
}

std::list<std::pair<int, int>> LevelManager::LoadLevel(int level)
{
	std::list<std::pair<int, int>> levelBoard;

	int max = m_col * m_row - 1;
	
	std::random_device rd;    
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0, max);

	int counter = 0;

	switch (level)
	{
	case 1:
		counter = 14;
		break;
	case 2:
		counter = 10;
		break;
	case 3:
		counter = 8;
		break;
	case 4:
		counter = 6;
		break;
	}

	std::unordered_map<int, int> cache;

	for (int i = 0; i < counter; i++)
	{
		int value = uni(rng);

		if (cache.count(value) != 0)
			value = cache[value];
		else
		{
			cache.insert(std::make_pair<int, int>(std::move(value), std::move(max)));
			uni = std::uniform_int_distribution<int>(0, --max);
		}

		levelBoard.emplace_back(std::make_pair<int, int>(value / m_col, value % m_col));
	}
	
	return levelBoard;
}

void LevelManager::reset()
{
	m_level = 0;
}
