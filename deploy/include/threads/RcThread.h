/*
 * RcThread.h
 *
 *  Created on: Nov 1, 2016
 *      Author: jacob
 */

#ifndef THREAD_SET_RCTHREAD_H_
#define THREAD_SET_RCTHREAD_H_

#include "Define.h"
#include "PWMIO.h"
#include "Thread.h"
#include "PWMDataType.h"
#include "DataLinkFormat.h"
#include <mutex>

BEGIN_NAMESPACE
	
extern PWMData gRCBuffer;
extern PWMIO *gPWMIO;

/***********
 * global down buffer
 **********/
extern DATALINK_DOWN_FORMAT gDownBuffer;
extern std::mutex gDownMutex;

class RCThread : public Thread
{
public:
	RCThread();
	virtual ~RCThread();

	bool Run(void);

private:
	void WriteDownBuffer(float roll, float pitch, float yaw, float throttle);

};

END_NAMESPACE

#endif /* THREAD_SET_RCTHREAD_H_ */
