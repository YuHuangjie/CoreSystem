/*
 * MessageFactory.h
 *
 *  Created on: Oct 28, 2016
 *      Author: jacob
 */

#ifndef MESSAGEFACTORY_H_
#define MESSAGEFACTORY_H_

#include "Define.h"
#include "Message.h"

BEGIN_NAMESPACE

class MessageFactory
{
public:
	static MessageHeader CreateEmptyMessage();

	/* heartbeat message */
	static MessageHeader CreateRequestHeartbeatMessage();
	static MessageHeader CreateRespondHeartbeatMessage();
	
	/* gimbal control command */
	static MessageHeader CreateRequestUpdateGimbalMessage();
	static MessageHeader CreateRespondUpdateGimbalMessage();

	/* retrieve remote control data message */
	static MessageHeader CreateRequestGetRCMessage();
	static MessageHeader CreateRespondGetRCMessage();
	
	/* retrieve IMU data message */
	static MessageHeader CreateRequestIMUMessage();
	static MessageHeader CreateRespondIMUMessage();
	
	/* gimbal control command */
	static MessageHeader CreateRequestUpdateServoMessage();
	static MessageHeader CreateRespondUpdateServoMessage();
};



END_NAMESPACE
#endif /* MESSAGEFACTORY_H_ */
