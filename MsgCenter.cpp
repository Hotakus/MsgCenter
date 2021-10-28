#include "conf.h"
#include "MsgCenter.h"

#define TAG "MsgCenter"

using namespace msgmanager;

MsgCenter::MsgCenter()
{

}

MsgCenter::~MsgCenter()
{

}

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

bool MsgCenter::subscribe(subscriber_t *subscriber)
{
	if (!subscriber) {
		MSG_PRINT(TAG, "Subscriber is null.");
		return false;
	}
	subsChain.push_back(subscriber->info.name, subscriber);
	return true;
}

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

bool MsgCenter::publish()
{
	return false;
}

bool MsgCenter::notify(String &subscriberName)
{
	auto _node = subsChain.find(subscriberName);
	auto subscriber = _node ? _node->node_data<subscriber_t>() : nullptr;
	if (!subscriber) {
		MSG_PRINT(TAG, "Subscriber: \"%s\" is not existing.", subscriberName.c_str());
		return false;
	}

	_node = msgChain.find(subscriber->info.msg_id);
	auto msg = _node ? _node->node_data<msg_t>() : nullptr;
	if (!msg) {
		MSG_PRINT(TAG, "Msg: \"%s\" is not existing.", subscriber->info.msg_id.c_str());
		return false;
	}

	subscriber->run(msg);
	return true;
}


bool MsgCenter::notify(subscriber_t *subscriber)
{
	if (!subscriber) {
		MSG_PRINT(TAG, "Subscriber is null.");
		return false;
	}
	auto msg = msgChain.find(subscriber->info.msg_id)->node_data<msg_t>();
	if (!msg) {
		MSG_PRINT(TAG, "Msg: \"%s\" is not existing.", subscriber->info.msg_id.c_str());
		return false;
	}
	subscriber->run(msg);
	return true;
}

bool MsgCenter::addMsg(msg_t *msg)
{
	return msgChain.push_back(msg->id, msg);
}

bool MsgCenter::removeMsg(String &msgName)
{
	if (msgChain.erase(msgName))
		return true;
	MSG_PRINT(TAG, "Remove \"%s\" failed.", msgName.c_str());
	return false;
}

void MsgCenter::peek()
{

}

template<class T>
T *msg_t::data()
{
	return ((T *) pData);
}

void msg_t::set(String &_id, void *_pData)
{
	this->id = _id;
	this->pData = _pData;
}