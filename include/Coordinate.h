#pragma once

#include <string>

struct Coordinate
{
	unsigned int m_row;
	unsigned int m_col;

	std::string to_string() const;

	bool operator<(const Coordinate& other) const
	{
		return m_row < other.m_row || (m_row == other.m_row && m_col < other.m_col);
	}
};

std::string Coordinate::to_string() const
{
	std::string str;
	str += "{ row: ";
	str += std::to_string(m_row);
	str += ", col: ";
	str += std::to_string(m_col);
	str += " }";

	return str;
}

std::ostream& operator << (std::ostream& os, const Coordinate& c)
{
	os << c.to_string();
	return os;
}