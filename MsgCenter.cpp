#include "conf.h"
#include "MsgCenter.h"

#define TAG "MsgCenter"

using namespace msgmanager;

void MsgCenter::begin()
{
	_msgChain.begin();
	_subsChain.begin();
}

void MsgCenter::end()
{
	_msgChain.end();
	_subsChain.end();
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

	return _subsChain.push_back(subscriber->name(), subscriber);
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

	if (_subsChain.nodeCnt() == 0) {
		MSG_PRINT(TAG, "Subscriber's count is nil.");
		return false;
	}

	subscriber->unsubscribe_all();
	return _subsChain.erase(subscriber->name());
}

/**
 * @brief Notify designated subscriber by designated msg
 * @param subscriberName : Name of subscriber
 * @param msgName        : Name of msg
 * @return true or false
 */
bool MsgCenter::notify(const String &subscriberName, const String &msgName)
{
	auto subscriber = findSubscriber(subscriberName);
	if (!subscriber) {
		MSG_PRINT(TAG, "Subscriber: \"%s\" is not existing.", subscriberName.c_str());
		return false;
	}

	auto msg = findMsg(msgName);
	if (!msg) {
		MSG_PRINT(TAG, "Msg: \"%s\" is not existing.", msgName.c_str());
		return false;
	}

	subscriber->publish(msg);
	return true;
}

/**
 * @brief Notify designated subscriber by designated msg
 * @param subscriberName : The pointer of subscriber
 * @param msgName        : Name of msg
 * @return true or false
 */
bool MsgCenter::notify(subscriber_t *subscriber, const String &msgName)
{
	if (!subscriber) {
		MSG_PRINT(TAG, "Subscriber is null.");
		return false;
	}

	auto msg = findMsg(msgName);
	if (!msg) {
		MSG_PRINT(TAG, "Msg: \"%s\" is not existing.", msgName.c_str());
		return false;
	}

	subscriber->publish(msg);
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

	subscriber->publish(msg);
	return true;
}

/**
 * @brief Add a msg into chain.
 * @param msg : msg
 * @return true or false
 */
bool MsgCenter::addMsg(msg_t *msg)
{
	return _msgChain.push_back(msg->id(), msg);
}

/**
 * @brief remove designated msg out.
 * @param msgName : Name of msg
 * @return true or false
 */
bool MsgCenter::removeMsg(const String &msgName)
{
	if (_msgChain.erase(msgName))
		return true;
	MSG_PRINT(TAG, "Remove \"%s\" failed.", msgName.c_str());
	return false;
}

/**
 * @brief Peek the members of subscribers or msgs.
 */
String MsgCenter::peek(uint8_t member)
{
	Chain& chain = member ? subsChain(): msgChain();
	String peek_result = String(member ? "Subscribers["[chain.nodeCnt()-1] + String("]: ")
										:"Msgs["[chain.nodeCnt()-1] + String("]: "));
	auto probe = chain.head()->next();

	for (size_t i = 1; i < chain.nodeCnt(); ++i) {
		peek_result += probe->name() + (probe->isTail() ? String("") : String("->"));
		probe = probe->next();
	}

	return peek_result;
}

msg_t *MsgCenter::findMsg(const String &msgName)
{
	auto *_node = _msgChain.find(msgName);
	if (_node)
		return _node->node_data<msg_t *>();
	return nullptr;
}

subscriber_t *MsgCenter::findSubscriber(const String &subscriberName)
{
	auto *_node = _subsChain.find(subscriberName);
	if (_node)
		return _node->node_data<subscriber_t *>();
	return nullptr;
}

/**
 * @brief Broadcast a msg by itself pointer
 * @param msg : The pointer of msg
 * @return true or false
 */
bool MsgCenter::broadcast(msg_t *msg)
{
	if (!msg) {
		MSG_PRINT(TAG, "Msg is null.");
		return false;
	}

	auto probe = _subsChain.head()->next();
	for (size_t i = 1; i < _subsChain.nodeCnt(); ++i) {
		probe->node_data<subscriber_t *>()->publish(msg);
		probe = probe->next();
	}

	return true;
}

/**
 * @brief Broadcast a msg by name
 * @param msg : The name of msg
 * @return true or false
 */
bool MsgCenter::broadcast(const String &msgName)
{
	auto msg = findMsg(msgName);
	if (!msg) {
		MSG_PRINT(TAG, "Msg: \"%s\" is not existing.", msgName.c_str());
		return false;
	}

	auto probe = _subsChain.head()->next();
	for (size_t i = 1; i < _subsChain.nodeCnt(); ++i) {
		probe->node_data<subscriber_t *>()->publish(msg);
		probe = probe->next();
	}

	return true;
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

	subscriber_t hotakus("Hotakus");
	subscriber_t trisuborn("Trisuborn");
	subscriber_t someone("someone");

	String str = "Hotakus is a handsome man ";
	msg_t msg("testMsg", &str);
	mc.addMsg(&msg);            // 注册消息

	/* 订阅者订阅消息 */
	hotakus.subscribe_msg(msg.id(), msg_center_test_cb);
	trisuborn.subscribe_msg(msg.id(), msg_center_test_cb);
	someone.subscribe_msg(msg.id(), msg_center_test_cb);

	/* 注册订阅者 */
	mc.subscribe(&hotakus);
	mc.subscribe(&trisuborn);
	mc.subscribe(&someone);

	mc.peek(0);
	mc.peek(1);

	str += "!!!";                                   // 修改消息 01
	mc.notify(hotakus.name(), msg.id());            // 用特定消息通知特定订阅者
	mc.notify(&hotakus, &msg);                      // 用特定消息通知特定订阅者
	str += "!!!";                                   // 修改消息 02
	mc.broadcast(&msg);                             // 广播特定消息到所有订阅此消息的订阅者
	str += "!!! HaHaHa";                            // 修改消息 03
	mc.broadcast(msg.id());                         // 广播特定消息到所有订阅此消息的订阅者

	trisuborn.unsubscribe_msg(msg.id());            // 退订特定消息
	hotakus.unsubscribe_all();                      // 退订所有消息

	/* 订阅者退订所有消息并注销 */
	mc.unsubscribe(&hotakus);
	mc.unsubscribe(&trisuborn);
	mc.unsubscribe(&someone);

	mc.removeMsg(msg.id());             // 注销消息
	mc.end();
}


