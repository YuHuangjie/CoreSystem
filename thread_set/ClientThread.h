/*
 * ClientThread.h
 *
 *  Created on: Oct 31, 2016
 *      Author: jacob
 */

#ifndef THREAD_SET_CLIENTTHREAD_H_
#define THREAD_SET_CLIENTTHREAD_H_

#include "Define.h"
#include "Thread.h"
#include <string>
#include <mutex>
#include "Network.h"
#include "Message.h"
#include "MessageQueue.h"

using namespace std;


BEGIN_NAMESPACE

extern MessageQueue gMessageQueue;
extern mutex gMessageQueueMutex;

class ClientThread : public Thread
{
public:
	ClientThread(const string &server, const uint16_t &port);
	virtual ~ClientThread();

	bool Run(void);
	bool IsOnline(void) const;
	void SetOnline(bool online);

private:
	/* connection information */
	Network net;
	string server;
	uint16_t port;
	bool online;

	/*  */
	bool SendMessageOnce(void);
};

END_NAMESPACE

#endif /* THREAD_SET_CLIENTTHREAD_H_ */
