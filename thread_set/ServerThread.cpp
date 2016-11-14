/*
 * ServerThread.cpp
 *
 *  Created on: Oct 31, 2016
 *      Author: jacob
 */

#include "ServerThread.h"
#include "Message.h"
#include "StdMessage.h"
#include <iostream>

BEGIN_NAMESPACE

ServerThread::ServerThread(const string &address, const uint16_t &port) :
	address(address),
	port(port),
	online(false)
{

}

ServerThread::~ServerThread()
{
}

bool ServerThread::Run(void)
{
	int32_t ret;

	/* Bind a socket and listen for incoming connections */
	ret = net.Bind(address, port);
	if (ret == false) {
		cout << "SERVER: bind fail" << endl;
		return false;
	}

	ret = net.Listen();
	if (ret == false) {
		cout << "SERVER: listen fail" << endl;
		return false;
	}

	/* Accept incoming connection */
	ret = net.Accept(peer);
	if (ret == false) {
		cout << "SERVER: accept fail" << endl;
		return false;
	}

	SetOnline(true);
	
	cout << "SERVER: accepted" << endl;

	/* receive messages sent by client, and push them to global message vector */
	MessageHeader header;
	MessageData *data = nullptr;
	Message msg;
	while (online) {
		/* receive message */
		ret = peer.ReadMessageHeader(header);
		if (ret == false) { return false; }
		ret = SelectMessageReader(header, &data);
		if (ret == false) { return false; }

		/* add this message to global message buffer */
		msg.header = header;
		msg.data = data;
		PushToBuffer(msg);
	}
}

bool ServerThread::SelectMessageReader(const MessageHeader &head, MessageData **data)
{
	switch (head.type) {
		
	case REQUEST_GET_RC:
		*data = nullptr;
		peer.ReadMessage(head, *data);
		break;
		
	case RESPOND_GET_RC:
		*data = new ClassicPWMMsg();
		peer.ReadMessage(head, *data);
		break;
		
	case REQUEST_IMU:
		// no memory allocated
		*data = nullptr;
		peer.ReadMessage(head, *data);
		break;
	case RESPOND_IMU:
		*data = new ClassicIMUMsg();
		peer.ReadMessage(head, *data);
		break;
		
	case REQUEST_UPDATE_GIMBAL:
		*data = new ClassicGimbalMsg();
		peer.ReadMessage(head, *data);
		break;

	case RESPOND_UPDATE_GIMBAL:
		*data = new Float32Msg();
		peer.ReadMessage(head, *data);
		break;
		
	case REQUEST_HEARTBEAT:
	case RESPOND_HEARTBEAT:
		*data = nullptr;
		peer.ReadMessage(head, *data);
		break;
		
	case REQUEST_UPDATE_SERVO:
		*data = new ClassicPWMMsg();
		peer.ReadMessage(head, *data);
		break;
		
	case RESPOND_UPDATE_SERVO:
		*data = new Float32Msg();
		peer.ReadMessage(head, *data);
		break;

	default:
		*data = nullptr;
		cerr << "SERVER: unhandled type of message" << endl;
		break;
	}

	return true;
}

bool ServerThread::PushToBuffer(Message msg)
{
	lock_guard<mutex> lock(gMessageBufferMutex);
	gMessageBuffer.Buffer.push_back(msg);
}

void ServerThread::SetOnline(bool online)
{
	this->online = online;
}

bool ServerThread::IsOnline(void) const
{
	return online;
}

END_NAMESPACE
