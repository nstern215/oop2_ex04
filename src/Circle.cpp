#include "Circle.h"

Circle::Circle(Coordinate cor, bool edge):
	Item(cor),
	m_edge(edge)
{
	m_shape.setRadius(35);
	m_shape.setFillColor(sf::Color::Green);
}

void Circle::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}


Coordinate Circle::getCoordinate() const
{
	return m_coordinate;
}

//void Circle::setPosition(sf::Vector2f position)
//{
//	m_shape.setPosition(position);
//}

sf::Vector2f Circle::getPosition()
{
	return m_position;
}

int Circle::getRadius()
{
	return m_shape.getRadius();
}

void Circle::setPosition(int x, int y)
{
	m_shape.setPosition(x, y);
}