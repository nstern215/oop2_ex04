#pragma once

#include "Item.h"
#include "Circle.h"


class Cat: public Item{

public:

	Cat(Coordinate cor = {0 , 0});
	~Cat() = default;

	void checkCatSituation(Circle CatsCircle);

	Coordinate getCoordinate() const;

	void setCoordinants(int x, int y);

	void draw(sf::RenderWindow& window) override;

	void setPosition(int x, int y);

	int getRadius();

	sf::Vector2f getPosition();

	void move(sf::Vector2f newposition);

private:

	sf::CircleShape m_shape;
	sf::Vector2f m_position;

	bool m_isOutOfMap;
	
};