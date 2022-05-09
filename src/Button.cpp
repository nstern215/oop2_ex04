#include "Button.h"

#include <fstream>
#include <filesystem>

//#define FONT_PATH "C:\Users\nomedi1408\source\repos\oop2_ex04\resources\Daughter of Fortune.ttf"

Button::Button(std::string buttonName):
	m_name(buttonName)
{}

void Button::draw(sf::RenderWindow & window)
{
	window.draw(m_shape);

	auto font = sf::Font();
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	sf::Text mode(m_name, font);
	mode.setFillColor(sf::Color(43, 46, 120));
	mode.setOutlineThickness(6);
	mode.setPosition(m_shape.getPosition().x + 30, m_shape.getPosition().y + 5);
	mode.setOrigin(m_shape.getOrigin());
	window.draw(mode);

}

void Button::setPosition(int x, int y)
{
	m_shape.setPosition(x , y);
}

bool Button::handleMouseClick(sf::Vector2i pressedPoint)
{
	int x = pressedPoint.x;
	int y = pressedPoint.y;

	if (m_shape.getGlobalBounds().contains(x, y))
	{
		return true;
	}
	return false;
}

sf::Vector2f Button::getPosition()
{
	return m_shape.getPosition();
}

void Button::buildButton(sf::RenderWindow& window)
{

	float n;

	const auto windowSize = window.getSize();

	const sf::Vector2f buttonSize(static_cast<float>(windowSize.x) * 0.15f, static_cast<float>(windowSize.y) * 0.05f);

	if (m_name == "Reset")
	{
		n = 0.03;
	}
	else if (m_name == "Undo")
	{
		n = 0.82;
	}

	const sf::Vector2f buttonOrigin(static_cast<float>(windowSize.x) * n, static_cast<float>(windowSize.y) * 0.94f);

	m_shape.setSize(buttonSize);
	m_shape.setOutlineThickness(8);
	m_shape.setOutlineColor(sf::Color(183, 186, 156));
	m_shape.setFillColor(sf::Color(143, 145, 121));
	m_shape.setPosition(buttonOrigin);
}

