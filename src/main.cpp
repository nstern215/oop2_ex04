#include <iostream>

#include "Coordinate.h"
#include "Graph.h"

int main()
{
	Graph<Coordinate, int> g;

	g.insert({ 1,2 }, 1);
	g.insert({ 2,2 }, 2);

	g.addEdge({ 2,2 }, { 1,2 });
	

	return EXIT_SUCCESS;
}
