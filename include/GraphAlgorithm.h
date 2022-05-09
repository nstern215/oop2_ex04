#pragma once
#include <unordered_map>
#include <queue>



#include "Circle.h"
#include "Coordinate.h"
#include "Graph.h"
#include "Node.h"

//------------------------------------------------
//class Circle
//{
//public:
//	Circle(bool edge = false) : m_isEdge(edge) {}
//	bool isEdge() const { return m_isEdge; }
//	bool isBlocked() const { return m_isBlocked; }
//private:
//	bool m_isEdge = false;
//	bool m_isBlocked = false;
//};
//------------------------------------------------

template <typename T>
class GraphAlgorithm
{
public:
	void BFS(Node<T>* startingNode, bool (filter)(Node<T>*) = nullptr) const;
	bool isForeignsNodes(Node<T>* a, Node<T>* b) const;
private:

};

enum NodeColor
{
	WHITE = 0,
	GRAY = 1,
	BLACK = 2
};

template <typename T>
void GraphAlgorithm<T>::BFS(Node<T>* startingNode, bool (filter)(Node<T>*)) const
{
	std::unordered_map<const Node<T>*, NodeColor> colors;
	std::queue<Node<T>*> nodesQueue;

	colors.insert({ startingNode, GRAY });

	startingNode->setDistance(0);
	startingNode->setParent(nullptr);

	nodesQueue.push(startingNode);

	while (!nodesQueue.empty())
	{
		Node<T>* node = nodesQueue.front();
		nodesQueue.pop();

		if (filter != nullptr && filter(node))
		{
			node->setDistance(0);
			node->setParent(nullptr);

			colors.insert({ node, BLACK });

			continue;
		}

		int distance = node->distance() + 1;

		for (auto& n : *node)
		{
			Node<T>* currentNode = &n;
			if (colors.find(currentNode) != colors.end())
				continue;

			colors.insert({ currentNode, GRAY });
			n.setDistance(distance);
			n.setParent(node);

			nodesQueue.push(currentNode);
		}

		colors.find(node)->second = BLACK;
	}
}

template <typename T>
bool GraphAlgorithm<T>::isForeignsNodes(Node<T>* a, Node<T>* b) const
{
	for (const auto& neighbor : *a)
		if (&neighbor == b)
			return false;

	return true;
}

class CatAlgorithm
{
public:
	Coordinate move(Graph<std::pair<int, int>, Circle>::Iterator begin, Graph<std::pair<int, int>, Circle>::Iterator end,
		Node<Circle>* catLocation) const;

private:
	bool isBlockCircle(Node<Circle>* c);
	int calcRailRisk(Node<Circle>* dest) const;
	int calcVertexRisk(Node<Circle>* vertex) const;
};

inline Coordinate CatAlgorithm::move(Graph<std::pair<int, int>, Circle>::Iterator begin, Graph<std::pair<int, int>, Circle>::Iterator end, Node<Circle>* catLocation) const
{
	auto iterator = begin;
	for (; iterator != end; ++iterator)
	{
		iterator->setDistance(0);
		iterator->setParent(nullptr);
	}
	
	for (auto& n : *catLocation)
	{
		if (n.data().isEdge() && !n.data().isBlocked())
			return n.data().getCoordinate();
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
		
		return {-1, -1};
	}

	std::ranges::sort(edges, [](Node<Circle>& a, Node<Circle>& b) {return a.distance() < b.distance(); });

	const int minDistance = edges[0].distance();
	
	std::vector < std::pair<Node<Circle>*, int>> railsRisk;
	for(auto& node : edges)
	{
		if (node.distance() != minDistance) continue;

		railsRisk.push_back({ &node, calcRailRisk(&node) });
	}

	std::ranges::sort(railsRisk, [](std::pair<Node<Circle>*, int> a, std::pair<Node<Circle>*, int> b) {return a.second < b.second; });

	Node<Circle>* dest = railsRisk[0].first;

	if(dest->parent() != catLocation)
	{
		do
		{
			dest = dest->parent();
		} while (dest->parent() != catLocation);
	}

	return dest->data().getCoordinate();
}


inline bool CatAlgorithm::isBlockCircle(Node<Circle>* c)
{
	return c->data().isBlocked();
}

inline int CatAlgorithm::calcRailRisk(Node<Circle>* dest) const
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

inline int CatAlgorithm::calcVertexRisk(Node<Circle>* vertex) const
{

	std::vector<Node<Circle>> blocked;
	std::copy_if(vertex->begin(), vertex->end(), std::back_inserter(blocked), [](Node<Circle>& n) {return n.data().isBlocked(); });

	if (blocked.empty())
		return 0;

	if (blocked.size() == 1)
		return 1;

	if (blocked.size() >= 3)
		return 3;

	GraphAlgorithm<Circle> algo;
	const bool result = algo.isForeignsNodes(&blocked[0], &blocked[1]);

	return result ? 2 : 1;
}
