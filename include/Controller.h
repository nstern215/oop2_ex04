#pragma once

#include <SFML/Graphics.hpp>

#include "LevelManager.h"

class Controller{

public:

	Controller();
	~Controller() = default;

	void run();

	void handelClick();
	
private:

	LevelManager m_manager;

	sf::RenderWindow m_window;

	sf::Color m_bgColor;
};
