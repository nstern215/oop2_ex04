#pragma once

#include <SFML/Graphics.hpp>

#include "LevelManager.h"
#include "Board.h"

class Controller{

public:

	Controller();
	~Controller() = default;

	void run();

private:

	Board m_board;

	LevelManager m_manager;

	sf::RenderWindow m_window;

	sf::Color m_bgColor;
};
