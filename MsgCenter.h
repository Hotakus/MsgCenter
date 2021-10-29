#ifndef _MSGCENTER_H
#define _MSGCENTER_H

#include <utility>

#include "conf.h"
#include "chain/Chain.h"

namespace msgmanager {

	class msg_t {
	private:
	public:
		String id;
		void* pData;

		void set(String _id, void* _pData);
		template<class T> T* data();    // Get data by T
	};

	typedef void (*msg_callback_t)(msg_t* msg);
	class subscriber_t {
	public:
		typedef struct _info{
			String name;
			Chain msg_list;
		} info_t;

		info_t info;

		subscriber_t() {
			info.msg_list.begin();
		}

		~subscriber_t() {
			info.msg_list.end();
		}

		void set(String& _name) {
			this->info.name = _name;
		}

		/**
		 * @brief Subscribe msg and callback
		 * @param msg  : Msg that want to subscribe
		 * @param _mcb : Callback for the msg
		 */
		void subscribe_msg(String msg, msg_callback_t _mcb) {
			info.msg_list.push_back(std::move(msg), (void*)_mcb);
		}

		/**
		 * @brief Run the msg callback
		 * @param msgName : Msg callback name
		 * @param msg     : Msg that want to emit
		 */
		void publish(const String& msgName, msg_t* msg) {
			auto _node = this->info.msg_list.find(msgName);
			if (_node)
				_node->node_data<msg_callback_t>()(msg);
			else
				MSG_PRINT("", "msg callback is null");
		}
	};

	class MsgCenter {
	private:
		Chain msgChain;
		Chain subsChain;
	public:
		MsgCenter();
		~MsgCenter();

		void begin();
		void end();
		static void peek();

		bool addMsg(msg_t* msg);
		bool removeMsg(String msgName);
		msg_t* findMsg(String msgName);

		bool subscribe(subscriber_t* subscriber);
		bool unsubscribe(subscriber_t* subscriber);
		subscriber_t* findSubscriber(String msgName);
		bool notify(String& subscriberName, String& msgName);
		bool notify(subscriber_t* subscriber, String& msgName);

		static void msg_center_test();
	};
};




#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //_MSGCENTER_H
