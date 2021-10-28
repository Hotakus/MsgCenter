#ifndef _CHAIN_NODE_T_H
#define _CHAIN_NODE_T_H

#include <utility>

#include "../conf.h"

class chain_node_t {
private:
	String nodeName = "";
	void* pData = nullptr;
	chain_node_t* prevNode = nullptr;
	chain_node_t* nextNode = nullptr;
public:


	void set(chain_node_t* _prevNode, chain_node_t* _nextNode, void* _pData = nullptr);
	bool isHead();
	bool isTail();

	chain_node_t* prev();               // Get previous node
	chain_node_t* next();               // Get next node
	template<class T> T* node_data() {
		T* t = (T*)pData;
		return (t);
	}

	String& name() {
		return nodeName;
	}
	void name(String _name) {
		nodeName = std::move(_name);
	}
};


#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CPPTEST_CHAIN_NODE_T_H
