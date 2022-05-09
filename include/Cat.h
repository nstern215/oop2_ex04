#pragma once

#include "Item.h"
#include "Circle.h"
#include "Graph.h"
#include "Node.h"


class Cat: public Item{

public:

#define START_COL 5
#define START_ROW 5

	Cat(Coordinate cor = {0 , 0});
	~Cat() = default;

	void checkCatSituation(Circle CatsCircle);

	Coordinate getCoordinate() const;

	void setCoordinants(int x, int y);

	void draw(sf::RenderWindow& window) override;

	void setPosition(int x, int y);

	int getRadius() const;

	sf::Vector2f getPosition() const;

	//void move(sf::Vector2f newposition);
	void move(Graph<std::pair<int, int>, Circle>::Iterator begin, Graph<std::pair<int, int>, Circle>::Iterator end, Node<Circle>* catLocation);

private:

	sf::CircleShape m_shape;
	sf::Vector2f m_position;

	bool m_isOutOfMap;
	
};
