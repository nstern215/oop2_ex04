#pragma once
#include <unordered_set>
#include <memory>

template<typename T>
class Node
{
public:
	Node(T data = {});
	void addNeighbor(std::shared_ptr<Node<T>> node);
private:
	std::unordered_set<std::shared_ptr<Node<T>>> m_neighbors;
	T m_data;
};

template <typename T>
Node<T>::Node(T data):
	m_data(data)
{}

template <typename T>
void Node<T>::addNeighbor(std::shared_ptr<Node<T>> node)
{
	m_neighbors.insert(node);
}
