#ifndef HEARTBEATTHREAD_H
#define HEARTBEATTHREAD_H

#include "Define.h"
#include "Thread.h"


BEGIN_NAMESPACE
	
extern int32_t gHeartbeat;

class HeartbeatThread : public Thread
{
public:	
	HeartbeatThread();
	bool Run(void);
};
	
END_NAMESPACE

#endif