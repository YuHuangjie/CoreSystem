#include "SKnightGimbal.h"

BEGIN_NAMESPACE

SKnightGimbal::SKnightGimbal(PWMIO *pwmio)
{
	this->pwmio = pwmio;
}

void SKnightGimbal::SetTick(int32_t channel, float tick)
{
	if (this->pwmio == nullptr) {
		return;
	}
	
	if (channel != GIMBAL_ROLL_OUT &&
		channel != GIMBAL_PITCH_OUT && 
		channel != GIMBAL_YAW_OUT && 
		channel != GIMBAL_FOCUS_OUT) {
		return;
	}

	if (tick <= -1 || tick >= 1) {
		return;
	}

	pwmio->SetTick(channel, tick);
}

float SKnightGimbal::GetTick(int32_t channel)
{
	return 0.0;
}

void SKnightGimbal::Run(void)
{
	return;
}

void SKnightGimbal::Stop(void)
{
	return;
}



END_NAMESPACE