#pragma once

#include <SFML/Graphics.hpp>

#include "Coordinate.h"

class Circle{

public:

	Circle(Coordinate cor = { 0,0 }, bool edge = false);
	~Circle() = default;

	void draw(sf::RenderWindow& window);

	Coordinate getCoordinate() const;

	bool isEdge() const { return m_edge; }
	bool isBlocked() const { return !m_active ; }

	void activateCircle();
	void setPosition(int x, int y);

	bool mouseClicked(sf::Vector2i pressedPoint);

	int getRadius();

	sf::Vector2f getPosition();

	void blockCircle();

private:

	sf::CircleShape m_shape;
	sf::Vector2f m_position;

	Coordinate m_coordinate;
	bool m_active;

	bool m_edge;
	bool m_isBlocked = false;
};
