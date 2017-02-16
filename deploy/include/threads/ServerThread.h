/*
 * ServerThread.h
 *
 *  Created on: Oct 31, 2016
 *      Author: jacob
 */

#ifndef THREAD_SET_SERVERTHREAD_H_
#define THREAD_SET_SERVERTHREAD_H_

#include "Define.h"
#include "Thread.h"
#include <string>
#include "Network.h"
#include "MessageBuffer.h"
#include <mutex>

using namespace std;


BEGIN_NAMESPACE

extern MessageBuffer gMessageBuffer;
extern mutex gMessageBufferMutex;

class ServerThread : public Thread
{
public:
	ServerThread(const string &server, const uint16_t &port);
	virtual ~ServerThread();

	bool Run(void);
	bool IsOnline(void) const;
	void SetOnline(bool online);

private:
	/* Server network information */
	Network net;
	Network peer;
	string address;
	uint16_t port;
	bool online;

	/*  */
	bool SelectMessageReader(const MessageHeader &header, MessageData **data);
	bool PushToBuffer(Message header);
};

END_NAMESPACE

#endif /* THREAD_SET_SERVERTHREAD_H_ */
