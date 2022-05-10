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
private:
	void resetGame();
	void undoMove();
	void drawAllElements();
	void buildAllElements();

	bool isCatWin() const;
	bool isCatLose() const;

	void showWinMessage();
	void showLoseMessage();

	void LoadNextLevel();
	
	Board m_board;

	LevelManager m_levelManager;

	sf::RenderWindow m_window;

	Button m_resetButton;
	Button m_undoButton;
	Button m_moveNominator;
	
	sf::Color m_bgColor;

	bool m_showMessage = false;
	sf::Text m_message;
	sf::Font m_messageFont;
};
