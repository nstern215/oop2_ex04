#include "Cat.h"

Cat::Cat()
{
	m_isOutOfMap = false;
	m_shape.setRadius(35);
	m_shape.setFillColor(sf::Color::Red);
	m_shape.setPosition(m_position);
}

void Cat::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

void Cat::setPosition(int x, int y)
{
	m_shape.setPosition(x, y);
}

sf::Vector2f Cat::getPosition()
{
	return m_shape.getPosition();
}

int Cat::getRadius()
{
	return m_shape.getRadius();
}
