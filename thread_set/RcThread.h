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


BEGIN_NAMESPACE
	
extern PWMData gRCBuffer;
extern PWMIO *gPWMIO;

class RCThread : public Thread
{
public:
	RCThread();
	virtual ~RCThread();

	bool Run(void);

private:

};

END_NAMESPACE

#endif /* THREAD_SET_RCTHREAD_H_ */
