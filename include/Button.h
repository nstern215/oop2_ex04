#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Button{

public:
	Button(std::string buttonName);

	void draw(sf::RenderWindow& window, int playNum);

	void setPosition(int x, int y);

	bool handleMouseClick(sf::Vector2i pressedPoint);

	sf::Vector2f getPosition();

	void buildButton(sf::RenderWindow& window);

private:

	sf::RectangleShape m_shape;
	sf::Vector2f m_position;

	std::string m_name;
	std::string m_textToPrint;
};