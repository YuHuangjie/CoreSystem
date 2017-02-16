/*
 * Network.h
 *
 *  Created on: Oct 28, 2016
 *      Author: jacob
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include "Define.h"
#include "Message.h"
#include "Socket.h"

#include <string>
#include <sstream>

using namespace std;


BEGIN_NAMESPACE


/*
 * Network class inherits Socket class and handles specific task
 * of transferring messages. It simply call Socket member functions
 * to work.
 */
class Network: public Socket
{
public:
	bool WriteMessage(MessageHeader &header, MessageData *const m) const;

	bool ReadMessageHeader(MessageHeader &header) const;

	bool ReadMessage(const MessageHeader &header, MessageData * const m) const;
};


END_NAMESPACE
#endif /* NETWORK_H_ */
