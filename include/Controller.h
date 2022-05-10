#pragma once

#include <SFML/Graphics.hpp>

#include "LevelManager.h"
#include "Board.h"
#include "Button.h"

class Controller{

public:

	Controller();
	~Controller() = default;

	void run();

	void resetGame();

	void undoMove();

	void drawAllElements();
private:

	bool isCatWin() const;
	bool isCatLose() const;
	
	Board m_board;

	LevelManager m_manager;

	sf::RenderWindow m_window;

	Button m_resetButton;
	Button m_undoButton;

	sf::Color m_bgColor;
};
