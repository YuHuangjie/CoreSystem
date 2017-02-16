#ifndef SKNIGHTGIMBAL_H
#define SKNIGHTGIMBAL_H

#include "Gimbal.h"
#include "PWMIO.h"

BEGIN_NAMESPACE

class SKnightGimbal : public Gimbal
{
public:
	SKnightGimbal(PWMIO *);

	void SetTick(int32_t channel, float tick);
	float GetTick(int32_t channel);

	void Run(void);
	void Stop(void);

private:
	PWMIO *pwmio;
};

END_NAMESPACE

#endif