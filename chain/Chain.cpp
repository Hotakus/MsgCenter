#include "Chain.h"

#define TAG             "Chain"
#define CHAIN_PRINT_D   MSG_PRINT
#define CHAIN_ALLOC     MSG_ALLOC
#define CHAIN_REALLOC   MSG_REALLOC
#define CHAIN_FREE      MSG_FREE

Chain::Chain()
{

}

Chain::~Chain()
{

}

/**
 * @brief Call this function before using chain.
 */
void Chain::begin()
{
	_head = new chain_node_t();
	_head->set(nullptr, nullptr, (void *) "chain_head");
	_head->name("chain_head");
	_curr = _head;
	_tail = _curr;
}

/**
 * @brief Release all used resources, call it after using done.
 */
void Chain::end()
{
	chain_node_t* probe = _head;
	chain_node_t* _next;
	for (; _nodeCnt; --_nodeCnt) {
		_next = probe->next();
		delete probe;
		probe = _next;
	}

	_head = nullptr;
	_tail = nullptr;
	_curr = nullptr;
}

/**
 * @brief Push the pointer of data into chain.
 * @param _name		: Chain node's name
 * @param _pData	: Pointer of data
 * @return
 */
bool Chain::push_back(String _name, void *_pData)
{
	_nodeCnt += 1;
	auto *_node = new chain_node_t();
	_curr->set(_curr->prev(), _node, _curr->node_data<void*>());
	_node->set(_curr, nullptr, _pData);
	_node->name(std::move(_name));
	_curr = _node;
	_tail = _node;
	return true;
}

/**
 * @brief
 * @param _node
 * @return
 */
bool Chain::push_front(chain_node_t *_node)
{
	return false;
}

/**
 * @brief
 * @return
 */
bool Chain::pop()
{
	erase(_tail->name());
	return false;
}

/**
 * @brief Delete a node designated.
 * @param name : Node's name
 * @return     : Bool
 */
bool Chain::erase(String name)
{
	chain_node_t *probe = _head;
	for (int i = 0; i < _nodeCnt; ++i) {
		if (probe->name() == name) {
			if (probe->isHead())
				return false;
			chain_node_t* _node = probe->prev();
			_node->set(_node->prev(), probe->next(), _node->node_data<void*>());
			if (_node->isTail()) {
				_tail = _node;
				_curr = _node;
			} else
				probe->next()->set(_node, probe->next()->next(), probe->next()->node_data<void*>());
			delete probe;
			_nodeCnt -= 1;
			return true;
		}
		probe = probe->next();
	}
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

/**
 * @brief Find and return the node designated.
 * @param name : Node's name
 * @return     : Nullptr or pointer of node.
 */
chain_node_t *Chain::find(String name)
{
	chain_node_t* probe = _head;
	for (int i = 0; i < _nodeCnt; ++i) {
		if (probe->name() == name)
			return probe;
		probe = probe->next();
	}
	return nullptr;
}
