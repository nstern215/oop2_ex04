#include "Cat.h"

#include "CatAlgorithm.h"

Cat::Cat(Coordinate cor)
{
	m_coordinate.m_col = START_COL;
	m_coordinate.m_row = START_ROW;
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

sf::Vector2f Cat::getPosition() const
{
	return m_shape.getPosition();
}

int Cat::getRadius() const
{
	return m_shape.getRadius();
}

void Cat::move(Graph<std::pair<int, int>, Circle>::Iterator begin, Graph<std::pair<int, int>, Circle>::Iterator end, Node<Circle>* catLocation)
{
	const CatAlgorithm cat;
	const Coordinate dest = cat.move(begin, end, catLocation);

	if (dest.m_col != -1)
		setCoordinants(dest.m_row, dest.m_col);
}


bool Cat::catPressed(const int x, const int y)
{
	if (m_shape.getGlobalBounds().contains(x, y))
	{
		return false;
	}
	return true;
}
