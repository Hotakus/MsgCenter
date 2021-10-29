#ifndef _MSGCENTER_H
#define _MSGCENTER_H

#include "conf.h"
#include "chain/Chain.h"

namespace msgmanager {

	/**
	 * @brief Class msg type
	 */
	class msg_t {
	private:
		String _id;
		void* _pData;
	public:
		void set(const String& id, void* pData = nullptr) {
			this->id(id);
			this->pData(pData);
		}

		String& id() {
			return this->_id;
		}

		void id(const String& id) {
			this->_id = id;
		}

		void* pData() {
			return this->_pData;
		}

		void pData(void* pData) {
			this->_pData = pData;
		}
	};

	typedef void (*msg_callback_t)(msg_t* msg);

	/**
	 * @brief Class subscriber type
	 */
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
		bool removeMsg(const String& msgName);
		msg_t* findMsg(const String& msgName);

		bool subscribe(subscriber_t* subscriber);
		bool unsubscribe(subscriber_t* subscriber);
		subscriber_t* findSubscriber(const String& msgName);

		bool notify(subscriber_t* subscriber, msg_t* msg);
		bool notify(const String& subscriberName, const String& msgName);
		bool notify(subscriber_t* subscriber, const String& msgName);

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
