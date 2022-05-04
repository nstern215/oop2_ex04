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

	
	friend struct Iterator;

	struct Iterator
	{
		Iterator(std::map < T1, std::shared_ptr<Node<T2>>>::iterator iterator) :m_iterator(iterator) {}
		Node<T2>& operator*()	{ return *(m_iterator->second); }
		Node<T2>* operator->()	{ return m_iterator->second.get(); }
		Iterator operator++()	{ return ++m_iterator; }
		bool operator==(const Iterator& other) const { return m_iterator == other.m_iterator; }
		bool operator!=(const Iterator& other) const { return !(m_iterator == other.m_iterator); }
	private:
		std::map < T1, std::shared_ptr<Node<T2>>>::iterator m_iterator;
	};

	Iterator begin()	{ return Iterator(m_nodes.begin()); }
	Iterator end()		{ return Iterator(m_nodes.end()); }
	
	const Node<T2>& operator[](T1 id) const;

private:
	std::map<T1, std::shared_ptr<Node<T2>>> m_nodes;
};

template <typename T1, typename T2>
void Graph<T1, T2>::insert(T1 id, T2 node)
{
	m_nodes.emplace(id, std::make_shared<Node<T2>>(node));
}

template <typename T1, typename T2>
void Graph<T1, T2>::addEdge(T1 id1, T1 id2)
{
	if (!m_nodes.contains(id1) || !m_nodes.contains(id2))
		throw std::exception("Node is not exists in the graph");

	m_nodes.at(id1)->addNeighbor(m_nodes.at(id2));
	m_nodes.at(id2)->addNeighbor(m_nodes.at(id1));
}

template <typename T1, typename T2>
const Node<T2>& Graph<T1, T2>::operator[](T1 id) const
{
	return *m_nodes.at(id);
}

