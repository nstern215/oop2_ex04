#pragma once
#include <unordered_set>

class BaseNode
{
public:
	void addNeighbor(BaseNode* node);
private:
	std::unordered_set<BaseNode*> m_neighbors;
};
