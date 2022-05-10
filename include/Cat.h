#pragma once

#include <SFML/Graphics.hpp>

#include "Coordinate.h"
#include "Circle.h"
#include "Graph.h"
#include "Node.h"


class Cat{

public:

#define START_COL 5
#define START_ROW 5

	Cat(Coordinate cor = {0 , 0});
	~Cat() = default;

	void checkCatSituation(Circle CatsCircle);

	Coordinate getCoordinate() const;

	void setCoordinants(int x, int y);

	void draw(sf::RenderWindow& window);

	void setPosition(int x, int y);

	int getRadius() const;

	bool catPressed(const int x, const int y);

	sf::Vector2f getPosition() const;

	void move(Graph<std::pair<int, int>, Circle>::Iterator begin, Graph<std::pair<int, int>, Circle>::Iterator end, Node<Circle>* catLocation);

private:

	Coordinate m_coordinate;
	bool m_active;

	sf::CircleShape m_shape;
	sf::Vector2f m_position;

	bool m_isOutOfMap;

	std::unique_ptr<sf::Texture> m_texture;
};
