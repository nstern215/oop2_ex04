#include <iostream>

#include "Coordinate.h"
#include "Graph.h"

int main()
{
	Graph<Coordinate> g;

	g.insert({ 1,2 }, new BaseNode());
	g.insert({ 2,2 }, new BaseNode());

	g.addEdge({ 2,2 }, { 1,2 });
	

	return EXIT_SUCCESS;
}
