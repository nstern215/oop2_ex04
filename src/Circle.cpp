#include "Circle.h"

Circle::Circle(Coordinate cor, bool edge):
	Item(cor),
	m_edge(edge)
{
	m_shape.setRadius(50);
	m_shape.setFillColor(sf::Color::Green);
	/*m_position.x = cor.m_col;
	m_position.y = cor.m_row;*/
	m_shape.setPosition(m_position);
}

void Circle::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}


Coordinate Circle::getCoordinate() const
{
	return m_coordinate;
}

void Circle::setPosition(int x, int y)
{
	m_shape.setPosition(x, y);
}
