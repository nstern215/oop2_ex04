#include "LevelManager.h"

void LevelManager::buildGameMap()
{
	int a = 0;
	
	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_COLS; j++)
		{
			 bool isEdge = (i == 1) || (i == NUM_OF_ROWS) || (j == 1) || (j == NUM_OF_COLS);

			
			Circle c({i,j}, isEdge);
			m_gameMap.insert({i,j}, c);
		}
	}
}

void LevelManager::drawGameMap(sf::RenderWindow& window)
{
	int radius = 50;

	
	for (auto& cell : m_gameMap)
	{
		Coordinate cor = cell.data().getCoordinate();

		int x = cor.m_col * (radius * 2);
		int y = cor.m_row* (radius * 2);

		if (cor.m_row % 2 != 0)
			x += radius;

		cell.data().setPosition(x, y);
		
		cell.data().draw(window);
	}
}
