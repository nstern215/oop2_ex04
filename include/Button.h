#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

enum ButtonName {

	RESET = 0,
	UNDO = 1
};

class Button{

public:
	Button(std::string buttonName);

	void draw(sf::RenderWindow& window);

	void setPosition(int x, int y);

	bool handleMouseClick(sf::Vector2i pressedPoint);

	sf::Vector2f getPosition();

	void buildButton(sf::RenderWindow& window);

private:

	sf::RectangleShape m_shape;
	sf::Vector2f m_position;

	std::string m_name;
};