#ifndef _MSGCENTER_H
#define _MSGCENTER_H

#include "conf.h"
#include "chain/Chain.h"

namespace msgmanager {

	class msg_t {
	private:
	public:
		String id;
		void* pData;

		void set(String& _id, void* _pData);
		template<class T> T* data();    // Get data by T
	};

	typedef void (*msg_callback_t)(msg_t* msg);
	class subscriber_t {
	public:
		struct {
			String name;
			String msg_id;
			msg_callback_t mcb;
		} info;

		void set(String& _name, String& _msg_id, msg_callback_t _mcb) {
			this->info.name = _name;
			this->info.msg_id = _msg_id;
			this->info.mcb = _mcb;
		}

		void run(msg_t* msg) {
			this->info.mcb(msg);
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
		bool removeMsg(String& msgName);

		bool subscribe(subscriber_t* subscriber);
		bool unsubscribe(subscriber_t* subscriber);
		bool publish();
		bool notify(String& subscriberName);
		bool notify(subscriber_t* subscriber);

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
