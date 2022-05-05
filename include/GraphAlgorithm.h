#pragma once
#include <unordered_map>
#include <queue>

#include "Node.h"

//------------------------------------------------
class Circle
{
public:
	Circle(bool edge = false) : m_isEdge(edge) {}
	bool isEdge() const { return m_isEdge; }
	bool isBlocked() const { return m_isBlocked; }
private:
	bool m_isEdge = false;
	bool m_isBlocked = false;
};
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
	
	while(!nodesQueue.empty())
	{
		Node<T>* node = nodesQueue.front();
		nodesQueue.pop();

		if (filter != nullptr && filter(node))
		{
			node->setDistance(0);
			node->setParent(nullptr);

			colors.insert({node, BLACK});

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
	Node<Circle>* move(Graph<Coordinate, Circle>::Iterator begin, Graph<Coordinate, Circle>::Iterator end,
		Node<Circle>* catLocation) const;

private:
	bool isBlockCircle(Node<Circle>* c);
	int calcRailRisk(Node<Circle>* dest) const;
	int calcVertexRisk(Node<Circle>* vertex) const;
};

inline Node<Circle>* CatAlgorithm::move(Graph<Coordinate, Circle>::Iterator begin, Graph<Coordinate, Circle>::Iterator end, Node<Circle>* catLocation) const
{
	GraphAlgorithm<Circle> gAlgo;
	gAlgo.BFS(catLocation, [](Node<Circle>* c) {return c->data().isBlocked(); });

	std::vector<Node<Circle>> edges;
	std::copy_if(begin, end, std::back_inserter(edges), [](Node<Circle> c) {return c.data().isEdge() && c.parent() != nullptr; });

	if (edges.empty()) //the cat cannot reach the edge of board
	{
		return catLocation->begin().operator->();
	}

	/*if (std::count(edges.begin(), edges.end(), [](Node<Circle>& c){return !c.data().isBlocked();}) == 1)
	{
		
	}*/
	
	std::ranges::sort(edges, [](Node<Circle>& a, Node<Circle>& b) {return a.distance() < b.distance(); });

	
	
	return nullptr;
}


inline bool CatAlgorithm::isBlockCircle(Node<Circle>* c)
{
	return c->data().isBlocked();
}

inline int CatAlgorithm::calcRailRisk(Node<Circle>* dest) const
{
	int risk = 0;

	Node<Circle>* vertex = dest;

	while(vertex->parent() != nullptr)
	{
		risk += calcVertexRisk(vertex);
		vertex = vertex->parent();
	}
	
	return risk;
}

inline int CatAlgorithm::calcVertexRisk(Node<Circle>* vertex) const
{
	if (std::count((*vertex).begin(), (*vertex).end(), [](Node<Circle>& c) {return !c.data().isBlocked(); }) == 1)
	{
		
	}
	
	return 0;
}
