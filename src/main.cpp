#include <iostream>

#include "Coordinate.h"
#include "Graph.h"
#include "Controller.h"


int main()
{
	
	Controller gameController;

	gameController.run();

	//Graph<std::pair<int, int>, int> g;

	//g.insert({ 1,2 }, 1);
	//g.insert({ 2,2 }, 2);

	//g.addEdge({ 2,2 }, { 1,2 });
	//
	//g.insert({ 2,1 }, 2);

	return EXIT_SUCCESS;
}
