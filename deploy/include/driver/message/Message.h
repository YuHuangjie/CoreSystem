#ifndef MESSAGE_H
#define MESSAGE_H

#include "Define.h"
#include <cstdint>
#include <string>
#include <sstream>

using namespace std;

BEGIN_NAMESPACE

enum MessageType
{
	NONE,
	
	/* heartbeat */
	REQUEST_HEARTBEAT,
	RESPOND_HEARTBEAT,
	
	/* update gimbal data */
	REQUEST_UPDATE_GIMBAL,
	RESPOND_UPDATE_GIMBAL,
	
	/* retrieve rc data */
	REQUEST_GET_RC,
	RESPOND_GET_RC,
	
	/* retrieve imu data */
	REQUEST_IMU,
	RESPOND_IMU,
	
	/* update servo */
	REQUEST_UPDATE_SERVO,
	RESPOND_UPDATE_SERVO,
};

class MessageHeader
{

public:
	string Pack(void) const;
	bool Unpack(string raw);

	MessageType type;
	uint32_t length;
	uint32_t priority;
};

class MessageData
{
public:
	virtual ~MessageData()
	{	}
	virtual string Pack(void) const = 0;
	virtual bool Unpack(string &raw) = 0;

};

class Message
{
public:
	bool operator< (const Message &m) const ;
	MessageHeader header;
	MessageData *data;
};

END_NAMESPACE

#endif
