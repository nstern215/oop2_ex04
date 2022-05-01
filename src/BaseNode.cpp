#include "../include/BaseNode.h"

void BaseNode::addNeighbor(BaseNode* node)
{
	m_neighbors.insert(node);
}
