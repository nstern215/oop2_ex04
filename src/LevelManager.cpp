#include "LevelManager.h"

LevelManager::LevelManager(){}

void LevelManager::buildGameMap()
{
	for(unsigned int i = 1 ; i <= NUM_OF_ROWS ; i++)
	{
		for(unsigned int j = 1 ; j <= NUM_OF_COLS ; j++)
		{
			bool isEdge = false;

			if ((i == 1) || (i == NUM_OF_ROWS) || (j == 1) || (j == NUM_OF_COLS))
				isEdge = true;

			const Coordinate cor({i, j});
			const Circle c(cor, isEdge);
			m_gameMap.insert(cor, c);
		}
	}
}

void LevelManager::drawGameMap(sf::RenderWindow& window)
{
	for(const auto& cell : m_gameMap)
	{
		cell.data().draw(window);
	}
}
