#pragma once

#include "Circle.h"
#include "Coordinate.h"
#include "Graph.h"


class CatAlgorithm
{
public:
#define LOW_RISK 0
#define MID_RISK 1
#define HIGH_RISK 2
#define VERY_HIGH_RISK 1
	
	Coordinate move(Graph<std::pair<int, int>, Circle>::Iterator begin, Graph<std::pair<int, int>, Circle>::Iterator end,
		Node<Circle>* catLocation) const;

private:
	int calcRailRisk(Node<Circle>* dest) const;
	int calcVertexRisk(Node<Circle>* vertex) const;
};
