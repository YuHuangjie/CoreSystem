/*
 * MessageFactory.cpp
 *
 *  Created on: Oct 28, 2016
 *      Author: jacob
 */

#include "MessageFactory.h"

BEGIN_NAMESPACE

MessageHeader MessageFactory::CreateEmptyMessage()
{
	MessageHeader header;
	header.type = NONE;
	header.length = 0;
	header.priority = 0;
	
	return header;
}

MessageHeader MessageFactory::CreateRequestHeartbeatMessage()
{
	MessageHeader header;
	header.type = REQUEST_HEARTBEAT;
	header.length = 0;
	header.priority = 10;
	
	return header;
}

MessageHeader MessageFactory::CreateRespondHeartbeatMessage()
{
	MessageHeader header;
	header.type = RESPOND_HEARTBEAT;
	header.length = 0;
	header.priority = 10;
	
	return header;
}

MessageHeader MessageFactory::CreateRequestUpdateGimbalMessage()
{
	MessageHeader header;
	header.type = REQUEST_UPDATE_GIMBAL;
	header.length = 0;
	header.priority = 8;

	return header;
}

MessageHeader MessageFactory::CreateRespondUpdateGimbalMessage()
{
	MessageHeader header;
	header.type = RESPOND_UPDATE_GIMBAL;
	header.length = 0;
	header.priority = 8;

	return header;
}

MessageHeader MessageFactory::CreateRequestGetRCMessage()
{
	MessageHeader header;
	header.type = REQUEST_GET_RC;
	header.length = 0;
	header.priority = 6;
	
	return header;
}

MessageHeader MessageFactory::CreateRespondGetRCMessage()
{
	MessageHeader header;
	header.type = RESPOND_GET_RC;
	header.length = 0;
	header.priority = 6;
	
	return header;
}

MessageHeader MessageFactory::CreateRequestIMUMessage()
{
	MessageHeader header;
	header.type = REQUEST_IMU;
	header.length = 0;
	header.priority = 7;
	
	return header;
}

MessageHeader MessageFactory::CreateRespondIMUMessage()
{
	MessageHeader header;
	header.type = RESPOND_IMU;
	header.length = 0;
	header.priority = 7;
	
	return header;
}

MessageHeader MessageFactory::CreateRequestUpdateServoMessage()
{
	MessageHeader header;
	header.type = REQUEST_UPDATE_SERVO;
	header.length = 0;
	header.priority = 9;
	
	return header;
}

MessageHeader MessageFactory::CreateRespondUpdateServoMessage()
{
	MessageHeader header;
	header.type = RESPOND_UPDATE_SERVO;
	header.length = 0;
	header.priority = 9;
	
	return header;
}



END_NAMESPACE
