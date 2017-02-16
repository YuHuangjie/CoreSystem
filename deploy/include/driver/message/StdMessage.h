/*
 * StdMessage.h
 *
 *  Created on: Oct 28, 2016
 *      Author: jacob
 */

#ifndef STDMESSAGE_H_
#define STDMESSAGE_H_

#include "Define.h"
#include "Message.h"
#include <string>
#include <sstream>
#include "IMUDataType.h"
#include "PWMDataType.h"
#include "GimbalDataType.h"

using namespace std;

BEGIN_NAMESPACE

/*
 * Float32Msg
 */
class Float32Msg : public MessageData
{
public:
	Float32Msg() {}
	Float32Msg(float data) { this->data = data; }

	string Pack(void) const;
	bool Unpack(string &raw);

public:
	float data;
};

/*
 * ClassicIMUMsg
 */
class ClassicIMUMsg : public MessageData
{
public:
	ClassicIMUMsg() {	}
	ClassicIMUMsg(const IMUData &data);
	
	string Pack(void) const;
	bool Unpack(string &raw);
	
public:
	IMUData data;
};

/*
 * ClassicPWMMsg
 */
class ClassicPWMMsg : public MessageData
{
public:
	ClassicPWMMsg()	{	}
	ClassicPWMMsg(const PWMData &data);
	
	string Pack(void) const;
	bool Unpack(string &raw);
	
public:
	PWMData data;
};

/* 
 * ClassicGimbalMsg
 */
class ClassicGimbalMsg : public MessageData
{
public:
	ClassicGimbalMsg() {	}
	ClassicGimbalMsg(const GimbalData &data);

	string Pack(void) const;
	bool Unpack(string &raw);

public:
	GimbalData data;
};

END_NAMESPACE

#endif /* STDMESSAGE_H_ */
