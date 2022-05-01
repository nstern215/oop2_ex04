#pragma once

#include <string>

struct Coordinate
{
	unsigned int m_row;
	unsigned int m_col;

	bool operator<(const Coordinate& other) const
	{
		return (m_row < other.m_row && m_col <= other.m_col) ||
			(m_row == other.m_row && m_col < other.m_col);
	}
};

std::ostream& operator << (std::ostream& os, const Coordinate& c)
{
	std::string str;
	str += "{ row: ";
	str += std::to_string(c.m_row);
	str += ", col: ";
	str += std::to_string(c.m_col);
	str += " }";
	
	os << str;
	return os;
}