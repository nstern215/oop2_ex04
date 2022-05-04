#pragma once
#include <iostream>
#include <unordered_set>
#include <memory>

template<typename T>
class Node
{
public:
	Node(T data = {});
	Node(const Node& other);
	void addNeighbor(std::shared_ptr<Node<T>> node);
	T data() const;
private:
	std::unordered_set<std::shared_ptr<Node<T>>> m_neighbors;
	T m_data;
};

template <typename T>
Node<T>::Node(const Node& other):
	m_data(other.data())
{
	std::cout << "copy ctor" << std::endl;
}

template <typename T>
Node<T>::Node(T data):
	m_data(data)
{}

template <typename T>
void Node<T>::addNeighbor(std::shared_ptr<Node<T>> node)
{
	m_neighbors.insert(node);
}

template <typename T>
T Node<T>::data() const
{
	return m_data;
}
