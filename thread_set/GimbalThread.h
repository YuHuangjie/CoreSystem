#ifndef GIMBALTHREAD_H
#define GIMBALTHREAD_H

#include "Define.h"
#include "Thread.h"
#include "GimbalDataType.h"
#include "PWMIO.h"
#include "SKnightGimbal.h"


BEGIN_NAMESPACE

extern GimbalData gGimbalBuffer;
extern PWMIO *gPWMIO;

class GimbalThread : public Thread
{
public:
	GimbalThread();
	~GimbalThread();

	bool Run(void);

private:
	Gimbal *gimbal;
};

END_NAMESPACE

#endif