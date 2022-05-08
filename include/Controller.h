#pragma once

#include <SFML/Graphics.hpp>

#include "LevelManager.h"
#include "Board.h"

class Controller{

public:

	Controller();
	~Controller() = default;

	void run();

	void buildResetButton();

	void buildUndoButton();

private:

	Board m_board;

	LevelManager m_manager;

	sf::RenderWindow m_window;

	sf::RectangleShape m_resetButton;
	sf::RectangleShape m_undoButton;

	sf::Color m_bgColor;
};
