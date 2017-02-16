/*
 * Message.cpp
 *
 *  Created on: Oct 28, 2016
 *      Author: jacob
 */

#include "Message.h"
#include <sstream>
#include <algorithm>

BEGIN_NAMESPACE

string MessageHeader::Pack(void) const
{
	ostringstream oss;
	oss << type << " " << length << " " << priority;
	return oss.str();
}

bool MessageHeader::Unpack(string raw)
{
	// check the validity of input
	if (count(raw.begin(), raw.end(), ' ') != 2) {
		return false;
	}

	istringstream iss(raw);
	int32_t type;
	uint32_t length, priority;
	iss >> type >> length >> priority;
	this->type = (MessageType)type;
	this->length = length;
	this->priority = priority;

	return true;
}

bool Message::operator <(const Message &m) const
{
	return header.priority < m.header.priority;
}

END_NAMESPACE



