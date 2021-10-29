#include "chain_node_t.h"

/**
 * @brief set this node
 * @param _prevNode : previous node
 * @param _nextNode : next node
 * @param pData 	: data pointer
 */
void chain_node_t::set(chain_node_t *_prevNode, chain_node_t *_nextNode, void *_pData)
{
	this->prevNode = _prevNode;
	this->nextNode = _nextNode;
	this->pData = _pData;
}

bool chain_node_t::isHead()
{
	if (!prevNode) return true;
	return false;
}

bool chain_node_t::isTail()
{
	if (!nextNode) return true;
	return false;
}

chain_node_t *chain_node_t::prev()
{
	return this->prevNode;
}


chain_node_t *chain_node_t::next()
{
	return this->nextNode;
}

void chain_node_t::prev(chain_node_t *_node)
{
	this->prevNode = _node;
}

void chain_node_t::next(chain_node_t *_node)
{
	this->nextNode = _node;
}
