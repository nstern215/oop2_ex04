#pragma once

#include "Graph.h"
#include "Circle.h"
#include  "Cat.h"
#include "LevelManager.h"

const int NUM_OF_ROWS = 11;
const int NUM_OF_COLS = 11;

class Board{

public:
	Board();

	void buildGameMap();
	void drawGameMap(sf::RenderWindow& window);
	void setCatPosition();
	void buildGame(sf::RenderWindow& window);
	void buildMapBoarder(sf::RenderWindow& window);
	void newGame();
	void undoMove();
	void moveCat();

	bool firstPlay();
	bool handelMouseClick(sf::Vector2i pressedPoint);

private:

	sf::RectangleShape m_mapBorder;
	Graph<std::pair<int, int>, Circle> m_gameMap;
	std::stack<Moves> m_gameMoveHistory;

	LevelManager m_manager;
	Cat m_gameCat;

	bool m_firstPlay;
};