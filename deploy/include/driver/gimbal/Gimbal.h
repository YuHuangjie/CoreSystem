#ifndef GIMBAL_H
#define GIMBAL_H

#include "Define.h"

BEGIN_NAMESPACE

class Gimbal
{
public:
	Gimbal() {	}
	virtual ~Gimbal() {	}

	virtual void SetTick(int32_t channel, float tick) = 0;
	virtual float GetTick(int32_t channel) = 0;

	virtual void Run(void) = 0;
	virtual void Stop(void) = 0;
};

END_NAMESPACE

#endif