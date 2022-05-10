#pragma once

#include <SFML/Graphics.hpp>

#include "Coordinate.h"
#include "Circle.h"


class Cat{

public:

	Cat(Coordinate cor = {0 , 0});
	~Cat() = default;

	void checkCatSituation(Circle CatsCircle);

	Coordinate getCoordinate() const;

	void setCoordinants(int x, int y);

	void draw(sf::RenderWindow& window);

	void setPosition(int x, int y);

	int getRadius();

	bool catPressed(const int x, const int y);

	sf::Vector2f getPosition();

private:

	Coordinate m_coordinate;
	bool m_active;

	sf::CircleShape m_shape;
	sf::Vector2f m_position;
	sf::Texture m_texture;


	bool m_isOutOfMap;
	
};