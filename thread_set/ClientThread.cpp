/*
 * ClientThread.cpp
 *
 *  Created on: Oct 31, 2016
 *      Author: jacob
 */

#include "ClientThread.h"
#include <chrono>
#include <iostream>
#include "StdMessage.h"

BEGIN_NAMESPACE

ClientThread::ClientThread(const string &server, const uint16_t &port) :
	server(server),
	port(port),
	online(false)
{	}

ClientThread::~ClientThread()
{	}

bool ClientThread::Run(void)
{
	online = false;
	int32_t ret;

	/* Try to connect to remote server with given address and port */
	while (!online) {
		ret = net.Connect(server, port);
		if (ret) {
			SetOnline(true);
		}
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	
	std::cout << "CLIENT: connected" << std::endl;
	
	/* After connection established, send messages in the global message queue */
	while (online) {
		if (!SendMessageOnce()) {
			return false;
		}
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}

bool ClientThread::SendMessageOnce(void)
{
	lock_guard<mutex> lock(gMessageQueueMutex);
	
	if (!gMessageQueue.Queue.empty()) {
		Message msg = gMessageQueue.Queue.top();
		gMessageQueue.Queue.pop();
		
		if (!net.WriteMessage(msg.header, msg.data)) {
			return false;
		}
		// release respond message
		delete msg.data;
		msg.data = nullptr;
	}
	return true;
}

bool ClientThread::IsOnline(void) const
{
	return online;
}

void ClientThread::SetOnline(bool online)
{
	this->online = online;
}

END_NAMESPACE
