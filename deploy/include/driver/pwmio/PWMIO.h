#ifndef PWMIO_H
#define PWMIO_H

#include "Define.h"

BEGIN_NAMESPACE
	
/*
 * Interface of reading and write PWM signals.
 */
class PWMIO
{
public:
	virtual ~PWMIO()
	{	}
	
	/*
	 * This method provides an interface of reading PWM signal
	 * at given channel. The result is guaranteed to be between -1 and 1.
	 */
	virtual float GetTick(int32_t channel) = 0;
	
	/*
	 * This method provides an interface of writing PWM signal
	 * at given channel. The argument must be in the range of -1 and 1.
	 */
	virtual void SetTick(int32_t channel, float tick) = 0;
	
	/*
	 * Run() method must be called before any requirements are made, such as Read.
	 */
	virtual void Run(void) = 0;
	
	/*
	 * Stop() method
	 */
	virtual void Stop(void) = 0;
	
};

END_NAMESPACE

#endif