#pragma once
#include <iostream>
#include <unordered_set>
#include <memory>

template<typename T>
class Node
{
public:
	Node(T data = {});
	void addNeighbor(std::shared_ptr<Node<T>> node);
	T data() const;

	Node<T>* parent() const;
	void setParent(Node<T>* parent);

	int distance() const;
	void setDistance(int distance);

	friend class Iterator;
	friend class Const_Iterator;

	class Iterator
	{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = Node<T>;
		using pointer = value_type*;
		using reference = value_type&;

		Iterator(std::unordered_set <std::shared_ptr<Node<T>>>::iterator iterator) :m_iterator(iterator) {}
		Node<T>& operator*() { return *m_iterator->get(); }
		Node<T>* operator->() { return m_iterator->get(); }
		Iterator operator++() { return ++m_iterator; }
		bool operator==(const Iterator& other) const { return m_iterator == other.m_iterator; }
		bool operator!=(const Iterator& other) const { return !(m_iterator == other.m_iterator); }
	private:
		std::unordered_set <std::shared_ptr<Node<T>>>::iterator m_iterator;
	};

	Iterator begin() const	{ return Iterator(m_neighbors.begin()); }
	Iterator end() const	{ return Iterator(m_neighbors.end()); }
private:
	std::unordered_set<std::shared_ptr<Node<T>>> m_neighbors;
	T m_data;
	Node<T>* m_parent = nullptr;
	int m_distance = 0;
};

template <typename T>
Node<T>::Node(T data) :
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

template <typename T>
Node<T>* Node<T>::parent() const
{
	return m_parent;
}

template <typename T>
void Node<T>::setParent(Node<T>* parent)
{
	m_parent = parent;
}

template <typename T>
int Node<T>::distance() const
{
	return m_distance;
}

template <typename T>
void Node<T>::setDistance(int distance)
{
	m_distance = distance;
}

