#pragma once

#include <iostream>
#include <memory>
#include <map>
#include "Node.h"

template<typename T1, typename T2>
class Graph
{
public:
	void insert(T1 id, T2 node);
	void addEdge(T1 id1, T1 id2);

	
	friend class Iterator;

	class Iterator
	{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = Node<T2>;
		using pointer = value_type*;
		using reference = value_type&;
		
		Iterator(std::map < T1, std::shared_ptr<Node<T2>>>::iterator iterator);
		reference operator*();
		pointer operator->();
		Iterator operator++();
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
	private:
		std::map < T1, std::shared_ptr<Node<T2>>>::iterator m_iterator;
	};

	Iterator begin();
	Iterator end();
	
	Node<T2>& operator[](T1 id) const;

private:
	std::map<T1, std::shared_ptr<Node<T2>>> m_nodes;
};

template <typename T1, typename T2>
void Graph<T1, T2>::insert(T1 id, T2 node)
{
	auto result = m_nodes.try_emplace(id, std::make_shared<Node<T2>>(node));
}

template <typename T1, typename T2>
void Graph<T1, T2>::addEdge(T1 id1, T1 id2)
{
	if (m_nodes.count(id1) == 0 || m_nodes.count(id2) == 0)
		return;

	m_nodes.at(id1)->addNeighbor(m_nodes.at(id2));
	m_nodes.at(id2)->addNeighbor(m_nodes.at(id1));
}

template <typename T1, typename T2>
Node<T2>& Graph<T1, T2>::operator[](T1 id) const
{
	return *m_nodes.at(id);
}

template <typename T1, typename T2>
typename Graph<T1, T2>::Iterator Graph<T1, T2>::begin()
{
	return Iterator(m_nodes.begin());
}

template <typename T1, typename T2>
typename Graph<T1, T2>::Iterator Graph<T1, T2>::end()
{
	return Iterator(m_nodes.end());
}

//Iterator
template <typename T1, typename T2>
Graph<T1, T2>::Iterator::Iterator(typename std::map<T1, std::shared_ptr<Node<T2>>>::iterator iterator):
	m_iterator(iterator)
{}

template <typename T1, typename T2>
typename Graph<T1, T2>::Iterator::reference Graph<T1, T2>::Iterator::operator*()
{
	return *(m_iterator->second);
}

template <typename T1, typename T2>
typename Graph<T1, T2>::Iterator::pointer Graph<T1, T2>::Iterator::operator->()
{
	return m_iterator->second.get();
}

template <typename T1, typename T2>
typename Graph<T1, T2>::Iterator Graph<T1, T2>::Iterator::operator++()
{
	return ++m_iterator;
}

template <typename T1, typename T2>
bool Graph<T1, T2>::Iterator::operator==(const Iterator& other) const
{
	return m_iterator == other.m_iterator;
}

template <typename T1, typename T2>
bool Graph<T1, T2>::Iterator::operator!=(const Iterator& other) const
{
	return !(m_iterator == other.m_iterator);
}
