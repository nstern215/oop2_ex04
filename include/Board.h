#pragma once

#include "Graph.h"
#include "Circle.h"
#include  "Cat.h"
#include "LevelManager.h"

#define FONT_PATH "C:\Fonts\Daughter of Fortune.ttf"

const int NUM_OF_ROWS = 11;
const int NUM_OF_COLS = 11;

class Board{

public:
	Board();

	void buildGameMap();

	void handelMouseClick(sf::Vector2i pressedPoint);

	void drawGameMap(sf::RenderWindow& window);

	void setCatPosition();

	void buildGame(sf::RenderWindow& window);

	void buildMapBoarder(sf::RenderWindow& window);

	bool firstPlay();

	void newGame();

private:

	sf::RectangleShape m_mapBorder;

	std::stack<Moves> m_gameMoveHistory;
	Graph<std::pair<int, int>, Circle> m_gameMap;

	LevelManager m_manager;
	Cat m_gameCat;

	bool m_firstPlay;
};