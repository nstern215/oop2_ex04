#include "Circle.h"

Circle::Circle(Coordinate cor, bool edge):
	Item(cor),
	m_edge(edge)
{
	m_shape.setRadius(35);
	m_shape.setFillColor(sf::Color(252, 248, 3));
}

void Circle::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}


Coordinate Circle::getCoordinate() const
{
	return m_coordinate;
}

sf::Vector2f Circle::getPosition()
{
	return m_position;
}

int Circle::getRadius()
{
	return m_shape.getRadius();
}

void Circle::activateCircle()
{
	m_active = true;
	m_shape.setFillColor(sf::Color(252, 248, 3));
}

void Circle::setPosition(int x, int y)
{
	m_shape.setPosition(x, y);
}

bool Circle::mouseClicked(sf::Vector2i pressedPoint)
{
	if (m_active)
	{
		int x = pressedPoint.x;
		int y = pressedPoint.y;

		if (m_shape.getGlobalBounds().contains(x, y))
		{
			m_shape.setFillColor(sf::Color(3, 173, 35));
			m_active = false;

			return true;
		}
	}
	return false;
}
