#pragma once

//#include <SFML/Graphics.hpp>

#include "Item.h"

class Circle: public Item{

public:

	Circle(Coordinate cor = { 0,0 }, bool edge = false);
	~Circle() = default;

	void draw(sf::RenderWindow& window) override;

	Coordinate getCoordinate() const;

	bool isEdge() const { return m_edge; }
	bool isBlocked() const { return m_isBlocked; }

	void activateCircle();
	void setPosition(int x, int y);

	bool mouseClicked(sf::Vector2i pressedPoint);

	int getRadius();

	sf::Vector2f getPosition();

private:

	sf::CircleShape m_shape;
	sf::Vector2f m_position;

	bool m_edge;
	bool m_isBlocked = false;
};
