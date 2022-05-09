#include "Coordinate.h"
#include "CatAlgorithm.h"

#include "GraphAlgorithm.h"

Coordinate CatAlgorithm::move(Graph<std::pair<int, int>, Circle>::Iterator begin, Graph<std::pair<int, int>, Circle>::Iterator end, Node<Circle>* catLocation) const
{
	for (auto& n : *catLocation)
	{
		if (n.data().isEdge() && !n.data().isBlocked())
			return n.data().getCoordinate();
	}

	auto iterator = begin;
	for (; iterator != end; ++iterator)
	{
		iterator->setDistance(0);
		iterator->setParent(nullptr);
	}

	const GraphAlgorithm<Circle> gAlgo;
	gAlgo.BFS(catLocation, [](Node<Circle>* c) {return c->data().isBlocked(); });

	std::vector<Node<Circle>> edges;
	std::copy_if(begin, end, std::back_inserter(edges), [](Node<Circle> c) {return c.data().isEdge() && c.parent() != nullptr; });

	if (edges.empty()) //the cat cannot reach the edge of the board
	{
		for (auto& node : *catLocation)
			if (!node.data().isBlocked())
				return node.data().getCoordinate();

		return { -1, -1 };
	}

	std::ranges::sort(edges, [](Node<Circle>& a, Node<Circle>& b) {return a.distance() < b.distance(); });

	const int minDistance = edges[0].distance();

	std::vector < std::pair<Node<Circle>*, int>> railsRisk;
	for (auto& node : edges)
	{
		if (node.distance() != minDistance) continue;

		railsRisk.push_back({ &node, calcRailRisk(&node) });
	}

	std::ranges::sort(railsRisk, [](std::pair<Node<Circle>*, int> a, std::pair<Node<Circle>*, int> b) {return a.second < b.second; });

	Node<Circle>* dest = railsRisk[0].first;

	if (dest->parent() != catLocation)
	{
		do
		{
			dest = dest->parent();
		} while (dest->parent() != catLocation);
	}

	return dest->data().getCoordinate();
}

int CatAlgorithm::calcRailRisk(Node<Circle>* dest) const
{
	int risk = 0;

	Node<Circle>* vertex = dest;

	while (vertex->parent() != nullptr)
	{
		risk += calcVertexRisk(vertex);
		vertex = vertex->parent();
	}

	return risk;
}

int CatAlgorithm::calcVertexRisk(Node<Circle>* vertex) const
{
	std::vector<Node<Circle>> blocked;
	std::copy_if(vertex->begin(), vertex->end(), std::back_inserter(blocked), [](Node<Circle>& n) {return n.data().isBlocked(); });

	if (blocked.empty())
		return LOW_RISK;

	if (blocked.size() == 1)
		return MID_RISK;

	if (blocked.size() >= 3)
		return VERY_HIGH_RISK;

	const GraphAlgorithm<Circle> algo;
	const bool result = algo.isForeignsNodes(&blocked[0], &blocked[1]);

	return result ? HIGH_RISK : MID_RISK;
}
