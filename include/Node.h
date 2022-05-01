#pragma once
#include <unordered_set>

template<typename T>
class Node
{
public:
	void addNeighbor(Node<T>* node);
private:
	std::unordered_set<Node<T>*> m_neighbors;
};

template <typename T>
void Node<T>::addNeighbor(Node<T>* node)
{
	m_neighbors.insert(node);
}
