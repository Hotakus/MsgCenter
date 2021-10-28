#include "conf.h"
#include "MsgCenter.h"



using namespace msgmanager;

MsgCenter::MsgCenter()
{

}

MsgCenter::~MsgCenter()
{

}

void MsgCenter::begin()
{
	this->pMsgBuff = (msg_t **) MSG_ALLOC(sizeof(msg_t *));
	this->pSubscriberBuff = (subscriber_t **) MSG_ALLOC(sizeof(subscriber_t *));
}

void MsgCenter::end()
{
	for (size_t i = 0; i < msgCnt; ++i)
		if (this->pMsgBuff[i])
			MSG_FREE(this->pMsgBuff[i]);
	MSG_FREE(this->pMsgBuff);

	for (size_t i = 0; i < subscriberCnt; ++i)
		if (this->pSubscriberBuff[i])
			MSG_FREE(this->pSubscriberBuff[i]);
	MSG_FREE(this->pSubscriberBuff);
}

bool MsgCenter::subscribe(subscriber_t *subscriber)
{
	if (!subscriber) {
		MSG_PRINT(TAG, "Subscriber is null.");
		return false;
	}
	subscriberCnt += 1;
	MSG_REALLOC(pSubscriberBuff, (sizeof(subscriber_t *) * subscriberCnt));
	pSubscriberBuff[subscriberCnt - 1] = (subscriber_t *) MSG_ALLOC(sizeof(subscriber_t));
	pSubscriberBuff[subscriberCnt - 1]->set(subscriber->name, subscriber->msg_id, subscriber->mcb);
	return true;
}

bool MsgCenter::unsubscribe(subscriber_t *subscriber)
{
	if (!subscriber) {
		MSG_PRINT(TAG, "Subscriber is null.");
		return false;
	}

	if (subscriberCnt == 0) {

		return false;
	}

	subscriberCnt -= 1;
	MSG_FREE(pSubscriberBuff[subscriberCnt]);
	MSG_REALLOC(pSubscriberBuff, (sizeof(subscriber_t *) * subscriberCnt));

	return true;
}

bool MsgCenter::publish()
{
	return false;
}

bool MsgCenter::notify(String &subscriberName)
{
	subscriber_t *subscriber = nullptr;
	msg_t *msg = nullptr;

	for (size_t i = 0; i < subscriberCnt; ++i) {
		if (pSubscriberBuff[i]->name == subscriberName) {
			subscriber = pSubscriberBuff[i];
		}
	}
	if (!subscriber) {
		MSG_PRINT(TAG, "Subscriber is not existing.");
		return false;
	}

	for (size_t i = 0; i < msgCnt; ++i) {
		if (pMsgBuff[i]->id == subscriber->msg_id) {
			msg = pMsgBuff[i];
		}
	}
	if (!msg) {
		MSG_PRINT(TAG, "Msg: \"%s\" is not existing.", subscriber->msg_id.c_str());
		return false;
	}

	subscriber->mcb(msg);

	return true;
}

void MsgCenter::_addMsg(String &msgName, void *pData)
{
	msgCnt += 1;
	MSG_REALLOC(pMsgBuff, (sizeof(msg_t *) * msgCnt));
	pMsgBuff[msgCnt - 1] = (msg_t *) MSG_ALLOC(sizeof(msg_t));
	pMsgBuff[msgCnt - 1]->set(msgName, pData);
}

bool MsgCenter::addMsg(String &msgName)
{
	_addMsg(msgName, nullptr);
	return true;
}

bool MsgCenter::addMsg(String &msgName, void *pData)
{
	_addMsg(msgName, pData);
	return true;
}

bool MsgCenter::removeMsg(String &msgName)
{
	for (size_t i = 0; i < msgCnt; ++i) {
		if (pMsgBuff[i]->id == msgName) {
			msgCnt -= 1;
			MSG_FREE(pMsgBuff[msgCnt]);
			MSG_REALLOC(pMsgBuff, (sizeof(msg_t *) * msgCnt));
			return true;
		}
	}

	MSG_PRINT(TAG, "Remove \"%s\" failed.", msgName.c_str());
	return false;
}

void MsgCenter::peek()
{

}
