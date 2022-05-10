#include "Cat.h"

Cat::Cat(Coordinate cor)
{
	m_coordinate.m_col = 5;
	m_coordinate.m_row = 5;
	m_isOutOfMap = false;
	m_shape.setRadius(35);
	m_shape.setFillColor(sf::Color::Red);
	m_shape.setPosition(m_position);

	//if (!m_texture.loadFromFile("cat.png")) 
	//{
	//	throw std::runtime_error("Can't load file");
	//}

	//m_shape.setTexture(m_texture, true);
}

Coordinate Cat::getCoordinate() const
{
	return m_coordinate;
}

void Cat::setCoordinants(int x, int y)
{
	m_coordinate.m_row = x;
	m_coordinate.m_col = y;
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
