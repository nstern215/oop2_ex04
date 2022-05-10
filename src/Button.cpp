#include "Button.h"

#include <fstream>
#include <filesystem>

Button::Button(std::string buttonName):
	m_name(buttonName)
{}

void Button::draw(sf::RenderWindow & window, int playNum)
{
	window.draw(m_shape);

	auto font = sf::Font();
	font.loadFromFile("Daughter of Fortune.ttf");
	sf::Text mode;
	mode.setFillColor(sf::Color(43, 46, 120));
	mode.setOutlineThickness(3);
	mode.setPosition(m_shape.getPosition().x + 15, m_shape.getPosition().y - 10);

	if (m_name == "MoveNominator")
	{	
		std::string str1 = "Number Of Moves: ";
		std::string str2 = std::to_string(playNum);

		m_textToPrint = str1 + str2;

		mode.setScale(static_cast<float>(m_shape.getSize().x * 0.0035), static_cast<float>(m_shape.getSize().y * 0.03));
	}
	else
	{
		m_textToPrint = m_name;
		mode.setScale(static_cast<float>(m_shape.getSize().x) * 0.01f, static_cast<float>(m_shape.getSize().y) * 0.03f);
	}
	mode.setString(m_textToPrint);
	mode.setFont(font);
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
	
	sf::Vector2f buttonSize;

	if (m_name == "MoveNominator")
	{
		buttonSize.x = static_cast<float>(windowSize.x) * 0.52f;
		buttonSize.y = static_cast<float>(windowSize.y) * 0.07f;

		n = 0.25;
	}
	else
	{
		buttonSize.x = static_cast<float>(windowSize.x) * 0.17f;
		buttonSize.y = static_cast<float>(windowSize.y) * 0.07f;

		if (m_name == "Reset")
		{
			n = 0.03;
		}
		else if (m_name == "Undo")
		{
			n = 0.82;
		}
	}	

	const sf::Vector2f buttonOrigin(static_cast<float>(windowSize.x) * n, static_cast<float>(windowSize.y) * 0.92f);

	m_shape.setSize(buttonSize);
	m_shape.setOutlineThickness(5);
	m_shape.setOutlineColor(sf::Color(183, 186, 156));
	m_shape.setFillColor(sf::Color(143, 145, 121));
	m_shape.setPosition(buttonOrigin);
}

