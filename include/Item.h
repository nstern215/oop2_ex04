#pragma once

#include <SFML/Graphics.hpp>

#include "Coordinate.h"

class Item{

public:

	Item(Coordinate cor = { 0,0 });
	virtual ~Item() = default;

	virtual void draw(sf::RenderWindow& window) = 0;

protected:

	Coordinate m_coordinate;
	bool m_active;

};