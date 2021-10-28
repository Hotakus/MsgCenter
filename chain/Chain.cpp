#include "Chain.h"

void Chain::begin()
{
}

void Chain::end()
{

}

bool Chain::push_back(chain_node_t *_node)
{
	return false;
}

bool Chain::push_front(chain_node_t *_node)
{
	return false;
}

bool Chain::pop()
{
	return false;
}

bool Chain::erase(size_t _id)
{
	return false;
}

bool Chain::insert(chain_node_t *_node, size_t _id)
{
	return false;
}

chain_node_t *Chain::head()
{
	return this->_head;
}

chain_node_t *Chain::tail()
{
	return this->_tail;
}
