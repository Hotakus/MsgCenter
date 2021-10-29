/******************************************************************
 * @file Chain.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief chain
 * @version 1.0
 * @date 2021/10/30 2:35
 * @copyright Copyright (c) 2021/10/30
*******************************************************************/
#ifndef _CHAIN_H
#define _CHAIN_H

#include "chain_node_t.h"

class Chain {
private:
	size_t _nodeCnt = 1;
	chain_node_t* _head = nullptr;
	chain_node_t* _tail = nullptr;
	chain_node_t* _curr = nullptr;
public:
	Chain();
	~Chain();

	void begin();
	void end();

	bool push_back(String _name,void* _pData);
	bool push_front(chain_node_t* _node);
	bool pop();
	bool erase(const String& name);
	bool insert(chain_node_t* _node, size_t _id);

	chain_node_t* find(const String& name);

	chain_node_t* head();
	chain_node_t* tail();

	size_t nodeCnt() {
		return this->_nodeCnt;
	}
};



#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //_CHAIN_H
