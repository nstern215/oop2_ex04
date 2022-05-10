#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
	void buildAllElements();

	bool isCatWin() const;
	bool isCatLose() const;
	
	Board m_board;

	LevelManager m_manager;

	//sf::Text m_nominator;
	//sf::RectangleShape m_moveNominator;
	sf::RenderWindow m_window;

	Button m_resetButton;
	Button m_undoButton;
	Button m_moveNominator;

	sf::Color m_bgColor;
};
