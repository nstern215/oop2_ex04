#pragma once

#include <unordered_map>
#include <queue>
#include "Node.h"

enum NodeColor
{
	WHITE = 0,
	GRAY = 1,
	BLACK = 2
};

template <typename T>
class GraphAlgorithm
{
public:
	void BFS(Node<T>* startingNode, bool (filter)(Node<T>*) = nullptr) const;
	bool isForeignsNodes(Node<T>* a, Node<T>* b) const;
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

