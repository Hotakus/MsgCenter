#include "conf.h"
#include "MsgCenter.h"

#define TAG "MsgCenter"

using namespace msgmanager;

MsgCenter::MsgCenter() = default;

MsgCenter::~MsgCenter() = default;

void MsgCenter::begin()
{
	msgChain.begin();
	subsChain.begin();
}

void MsgCenter::end()
{
	msgChain.end();
	subsChain.end();
}

/**
 * @brief Subscribe.
 * @param subscriber : The pointer of subscriber
 * @return true or false
 */
bool MsgCenter::subscribe(subscriber_t *subscriber)
{
	if (!subscriber) {
		MSG_PRINT(TAG, "Subscriber is null.");
		return false;
	}
	subsChain.push_back(subscriber->info.name, subscriber);
	return true;
}

/**
 * @brief Unsubscribe
 * @param subscriber : The pointer of subscriber
 * @return true or false
 */
bool MsgCenter::unsubscribe(subscriber_t *subscriber)
{
	if (!subscriber) {
		MSG_PRINT(TAG, "Subscriber is null.");
		return false;
	}

	if (subsChain.nodeCnt() == 0) {
		MSG_PRINT(TAG, "Subscriber's count is nil.");
		return false;
	}

	subsChain.erase(subscriber->info.name);
	return true;
}

/**
 * @brief Notify designated subscriber by designated msg
 * @param subscriberName : Name of subscriber
 * @param msgName        : Name of msg
 * @return true or false
 */
bool MsgCenter::notify(const String &subscriberName, const String &msgName)
{
	if (subscriberName == "") {
		MSG_PRINT(TAG, "Subscriber name is null.");
		return false;
	}
	auto _node = subsChain.find(subscriberName);
	auto subscriber = _node ? _node->node_data<subscriber_t *>() : nullptr;
	if (!subscriber) {
		MSG_PRINT(TAG, "Subscriber: \"%s\" is not existing.", subscriberName.c_str());
		return false;
	}

	_node = msgChain.find(msgName);
	auto msg = _node ? _node->node_data<msg_t *>() : nullptr;
	if (!msg) {
		MSG_PRINT(TAG, "Msg: \"%s\" is not existing.", msgName.c_str());
		return false;
	}

	subscriber->publish(msgName, msg);
	return true;
}

/**
 * @brief Notify designated subscriber by designated msg
 * @param subscriberName : The pointer of subscriber
 * @param msgName        : Name of msg
 * @return true or false
 */
bool MsgCenter::notify(subscriber_t *subscriber, const String& msgName)
{
	if (!subscriber) {
		MSG_PRINT(TAG, "Subscriber is null.");
		return false;
	}

	auto _node = msgChain.find(msgName);
	auto msg = _node ? _node->node_data<msg_t *>() : nullptr;
	if (!msg) {
		MSG_PRINT(TAG, "Msg: \"%s\" is not existing.", msgName.c_str());
		return false;
	}

	subscriber->publish(msgName, msg);
	return true;
}

/**
 * @brief Notify designated subscriber by designated msg
 * @param subscriber : The pointer of subscriber
 * @param msg        : The pointer of msg
 * @return true or false
 */
bool MsgCenter::notify(subscriber_t *subscriber, msg_t *msg)
{
	if (!subscriber) {
		MSG_PRINT(TAG, "Subscriber is null.");
		return false;
	}

	if (!msg) {
		MSG_PRINT(TAG, "Msg is null.");
		return false;
	}

	subscriber->publish(msg->id(), msg);
	return true;
}

/**
 * @brief Add a msg into chain.
 * @param msg : msg
 * @return true or false
 */
bool MsgCenter::addMsg(msg_t *msg)
{
	return msgChain.push_back(msg->id(), msg);
}

/**
 * @brief remove designated msg out.
 * @param msgName : Name of msg
 * @return true or false
 */
bool MsgCenter::removeMsg(const String &msgName)
{
	if (msgChain.erase(msgName))
		return true;
	MSG_PRINT(TAG, "Remove \"%s\" failed.", msgName.c_str());
	return false;
}

void MsgCenter::peek()
{

}

msg_t *MsgCenter::findMsg(const String &msgName)
{
	chain_node_t *_node = msgChain.find(msgName);
	if (_node)
		return _node->node_data<msg_t *>();
	return nullptr;
}

subscriber_t *MsgCenter::findSubscriber(const String &subscriberName)
{
	chain_node_t *_node = msgChain.find(subscriberName);
	if (_node)
		return _node->node_data<subscriber_t *>();
	return nullptr;
}


static void msg_center_test_cb(msg_t *msg)
{
	auto *str = (String *) msg->pData();

#if IS_ARDUINO == 0
	cout << "Hello world!!! " << *str << endl;
#else
	Serial.println(*str);
#endif
}

void MsgCenter::msg_center_test()
{
	MsgCenter mc;
	mc.begin();

	subscriber_t subscriber;
	String name = "Hotakus";
	subscriber.set(name);

	String str = "Hotakus is a handsome man.";
	msg_t msg;
	String msg_id = "testMsg";
	msg.set(msg_id, &str);

	String str2 = "Trisuborn is a handsome man.";
	String msg_id2 = "testMsg2";
	msg_t msg2;
	msg2.set(msg_id2, &str2);

	subscriber.subscribe_msg(msg_id2, msg_center_test_cb);
	subscriber.subscribe_msg(msg_id, msg_center_test_cb);  // 订阅者订阅消息
	mc.subscribe(&subscriber);                                  // 注册订阅者
	mc.addMsg(&msg);                                            // 注册消息
	mc.addMsg(&msg2);

	mc.notify(&subscriber, msg_id);                          // 通知订阅者
	mc.notify(&subscriber, msg_id2);

	mc.removeMsg(msg2.id());
	mc.removeMsg(msg.id());                                    // 注销消息
	mc.unsubscribe(&subscriber);                                // 注销订阅者

	mc.end();
}
