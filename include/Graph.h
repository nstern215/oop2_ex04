#pragma once

#include <memory>
#include <map>
#include "Node.h"

template<typename T1, typename T2>
class Graph
{
public:
	void insert(T1 id, Node<T2>* node);
	void addEdge(T1 id1, T1 id2);
private:
	std::map<T1, Node<T2>*> m_nodes;
};

template <typename T1, typename T2>
void Graph<T1, T2>::insert(T1 id, Node<T2>* node)
{
	m_nodes.emplace(id, node);
}

template <typename T1, typename T2>
void Graph<T1, T2>::addEdge(T1 id1, T1 id2)
{
	if (!m_nodes.contains(id1) || !m_nodes.contains(id2))
		throw std::exception("Node is not exists in the graph");

	m_nodes.at(id1)->addNeighbor(m_nodes.at(id2));
	m_nodes.at(id2)->addNeighbor(m_nodes.at(id1));
}

