#pragma once

#include <string>

struct Coordinate
{
	int m_row;
	int m_col;

	bool operator<(const Coordinate& other) const
	{
		return (m_row < other.m_row&& m_col < other.m_col);
	}

	bool operator==(const Coordinate& other) const
	{
		return m_col == other.m_col && m_row == other.m_row;
	}

	bool operator==(const std::pair<int, int>& other) const
	{
		return m_col == other.second && m_row == other.first;
	}
};