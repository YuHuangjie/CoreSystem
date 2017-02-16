/*
 * MessageQueue.h
 *
 *  Created on: Oct 31, 2016
 *      Author: jacob
 */

#ifndef MESSAGE_CONTAINER_MESSAGEQUEUE_H_
#define MESSAGE_CONTAINER_MESSAGEQUEUE_H_

#include "Define.h"
#include "Message.h"
#include <queue>

using namespace std;

BEGIN_NAMESPACE

class MessageQueue
{
public:
	priority_queue<Message> Queue;
};

END_NAMESPACE

#endif /* MESSAGE_CONTAINER_MESSAGEQUEUE_H_ */
