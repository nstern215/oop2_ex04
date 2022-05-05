#pragma once

#include <SFML/Graphics.hpp>

#include "Graph.h"
#include "Coordinate.h"
#include "Circle.h"


const int NUM_OF_ROWS = 11;
const int NUM_OF_COLS = 11;

class LevelManager{

public:
	LevelManager();
	~LevelManager() = default;

	void handleClickEvent();

	void buildGameMap();

	void drawGameMap(sf::RenderWindow& window);

private:

	Graph<Coordinate, Circle> m_gameMap;
};