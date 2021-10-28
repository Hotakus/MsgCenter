#ifndef CPPTEST_MSGCENTER_H
#define CPPTEST_MSGCENTER_H

#include "conf.h"

namespace msgmanager {
	class msg_t {
	private:

	public:
		String id;
		void* pData;
		void set(String& _id, void* _pData) {
			this->id = _id;
			this->pData = _pData;
		}

		// Get data by T
		template<class T> T* data() {
			return ((T*)pData);
		}
	};

	typedef void (*msg_callback_t)(msg_t* msg);
	class subscriber_t {
	public:
		String name;
		String msg_id;
		msg_callback_t mcb;
		void set(String& _name, String& _msg_id, msg_callback_t _mcb) {
			this->name = _name;
			this->msg_id = _msg_id;
			this->mcb = _mcb;
		}
	};

	class MsgCenter {
	private:
		msg_t** pMsgBuff = nullptr;
		subscriber_t** pSubscriberBuff = nullptr;

		size_t msgCnt = 0;
		size_t subscriberCnt = 0;

		void _addMsg(String& msgName, void *pData);
	public:
		MsgCenter();
		~MsgCenter();

		void begin();
		void end();
		static void peek();

		bool addMsg(String& msgName);
		bool addMsg(String& msgName, void* pData);
		bool removeMsg(String& msgName);

		bool subscribe(subscriber_t* subscriber);
		bool unsubscribe(subscriber_t* subscriber);
		bool publish();
		bool notify(String& subscriberName);

	};
};


#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CPPTEST_MSGCENTER_H
