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
		void *_pData = nullptr;
	public:
		msg_t() = default;
		~msg_t() = default;
		explicit msg_t(const String& id, void* dat = nullptr) {
			_id = id;
			_pData = dat;
		}

		String &id() {
			return this->_id;
		}

		void id(const String &id) {
			this->_id = id;
		}

		void *pData() {
			return this->_pData;
		}

		void pData(void *pData) {
			this->_pData = pData;
		}
	};

	typedef void (*msg_callback_t)(msg_t *msg);

	/**
	 * @brief Class subscriber type
	 */
	class subscriber_t {
	private:
		String _name;
		Chain _msg_list;
	public:
		subscriber_t() {
			_msg_list.begin();
		}

		explicit subscriber_t(const String &name) {
			_msg_list.begin();
			_name = name;
		}

		~subscriber_t() {
			_msg_list.end();
		}

		void name(const String& name) {
			_name = name;
		}

		String& name() {
			return _name;
		}

		Chain& msg_list() {
			return _msg_list;
		}

		/**
		 * @brief Subscribe msg and callback
		 * @param msg  : Msg that want to subscribe
		 * @param _mcb : Callback for the msg
		 */
		void subscribe_msg(const String &msgName, msg_callback_t _mcb)
		{
			if (msg_list().find(msgName)) {
				MSG_PRINT(info.name.c_str(), "msg was subscribed already.");
				return;
			}
			msg_list().push_back(msgName, (void *) _mcb);
		}

		void unsubscribe_msg(const String &msgName)
		{
			msg_list().erase(msgName);
		}

		void unsubscribe_all()
		{
			for (int i = 1; i < msg_list().nodeCnt(); ++i)
				msg_list().pop();
		}

		/**
		 * @brief Run the msg callback
		 * @param msgName : Msg callback name
		 * @param msg     : Msg that want to emit
		 */
		void publish(msg_t *msg)
		{
			auto _node = msg_list().find(msg->id());
			if (_node)
				_node->node_data<msg_callback_t>()(msg);
			else
				MSG_PRINT(info.name.c_str(), "msg callback is null");
		}
	};

	class MsgCenter {
	private:
		Chain _msgChain;
		Chain _subsChain;
	public:
		MsgCenter() = default;
		~MsgCenter() = default;

		void begin();
		void end();
		void peek();

		Chain &msgChain() {
			return this->_msgChain;
		}

		Chain &subsChain() {
			return this->_subsChain;
		}

		bool addMsg(msg_t *msg);
		bool removeMsg(const String &msgName);
		msg_t *findMsg(const String &msgName);

		bool subscribe(subscriber_t *subscriber);
		bool unsubscribe(subscriber_t *subscriber);
		subscriber_t *findSubscriber(const String &msgName);

		bool notify(subscriber_t *subscriber, msg_t *msg);
		bool notify(const String &subscriberName, const String &msgName);
		bool notify(subscriber_t *subscriber, const String &msgName);

		bool broadcast(msg_t *msg);
		bool broadcast(const String &msgName);

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
