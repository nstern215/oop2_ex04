#pragma once

#include <SFML/Graphics.hpp>

#include "Graph.h"
#include "Coordinate.h"
#include "Circle.h"


const int NUM_OF_ROWS = 3;
const int NUM_OF_COLS = 3;

class LevelManager{

public:
	LevelManager() = default;

	void handleClickEvent();

	void buildGameMap();

	void drawGameMap(sf::RenderWindow& window);

private:

	Graph<std::pair<int, int>, Circle> m_gameMap;
};