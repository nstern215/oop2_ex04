#pragma once

//#include <SFML/Graphics.hpp>

#include "Item.h"

class Circle: public Item{

public:

	Circle(Coordinate cor = { 0,0 }, bool edge = false);
	~Circle() = default;

	void draw(sf::RenderWindow& window) override;

	//void setSize(sf::Vector2f size) override;

	Coordinate getCoordinate() const;

	void setPosition(int x, int y);

private:

	sf::CircleShape m_shape;
	sf::Vector2f m_position;

	bool m_edge;
};
