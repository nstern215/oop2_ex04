#pragma once

#include <memory>
#include <map>
#include "BaseNode.h"

template<typename T>
class Graph
{
public:
	void insert(T id, BaseNode* node);
	void addEdge(T id1, T id2);
private:
	std::map<T, BaseNode*> m_nodes;
};

template <typename T>
void Graph<T>::insert(T id, BaseNode* node)
{
	m_nodes.emplace(id, node);
}

template <typename T>
void Graph<T>::addEdge(T id1, T id2)
{
	if (!m_nodes.contains(id1) || !m_nodes.contains(id2))
		throw std::exception("Node is not exists in the graph");

	m_nodes.at(id1)->addNeighbor(m_nodes.at(id2));
	m_nodes.at(id2)->addNeighbor(m_nodes.at(id1));
}

