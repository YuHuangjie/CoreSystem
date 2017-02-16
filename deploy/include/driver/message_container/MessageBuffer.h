/*
 * MessageBuffer.h
 *
 *  Created on: Oct 31, 2016
 *      Author: jacob
 */

#ifndef MESSAGE_CONTAINER_MESSAGEBUFFER_H_
#define MESSAGE_CONTAINER_MESSAGEBUFFER_H_

#include "Define.h"
#include "Message.h"
#include <deque>

BEGIN_NAMESPACE

class MessageBuffer
{
public:
	deque<Message> Buffer;
};

END_NAMESPACE

#endif /* MESSAGE_CONTAINER_MESSAGEBUFFER_H_ */
