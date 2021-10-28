#ifndef CPPTEST_CHAIN_H
#define CPPTEST_CHAIN_H

#include "chain_node_t.h"

class Chain {
private:
	size_t nodeCnt = 0;
	chain_node_t* _head = nullptr;
	chain_node_t* _tail = nullptr;
public:

	chain_node_t* headNode = nullptr;

	void begin();
	void end();

	bool push_back(chain_node_t* _node);
	bool push_front(chain_node_t* _node);
	bool pop();
	bool erase(size_t _id);
	bool insert(chain_node_t* _node, size_t _id);

	chain_node_t* head();
	chain_node_t* tail();


};



#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CPPTEST_CHAIN_H
