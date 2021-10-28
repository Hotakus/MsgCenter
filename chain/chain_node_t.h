#ifndef CPPTEST_CHAIN_NODE_T_H
#define CPPTEST_CHAIN_NODE_T_H

#include "../MsgCenter.h"

class chain_node_t {
private:
	int id = -1;
	void* pData = nullptr;
	chain_node_t* prevNode = nullptr;
	chain_node_t* nextNode = nullptr;
public:
	void set(chain_node_t* _prevNode, chain_node_t* _nextNode, void* _pData = nullptr);
	bool isHead();
	bool isTail();

	chain_node_t* prev();               // Get previous node
	chain_node_t* next();               // Get next node
	template<class T> T* node_data();   // Get data by T
	int node_id();                      // Get node id
};


#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CPPTEST_CHAIN_NODE_T_H
