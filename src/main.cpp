#include <iostream>

#include "Coordinate.h"
#include "Graph.h"

int main()
{
	Graph<Coordinate, int> g;

	g.insert({ 1,2 }, new Node<int>());
	g.insert({ 2,2 }, new Node<int>());

	g.addEdge({ 2,2 }, { 1,2 });
	

	return EXIT_SUCCESS;
}
