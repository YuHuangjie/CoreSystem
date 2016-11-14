#include "A3Servo.h"

BEGIN_NAMESPACE

A3Servo::A3Servo(PWMIO *pwmio)
{
	this->pwmio = pwmio;
}

void A3Servo::SetTick(int32_t channel, float tick)
{
	if (this->pwmio == nullptr) {
		return;
	}
	
	if (channel != THROTTLE_OUT &&
		channel != ROLL_OUT && 
		channel != PITCH_OUT && 
		channel != YAW_OUT) {
		return;
	}

	if (tick <= -1 || tick >= 1) {
		return;
	}

	pwmio->SetTick(channel, tick);
}

float A3Servo::GetTick(int32_t channel)
{
	return 0.0;
}

void A3Servo::Run(void)
{
	return;
}

void A3Servo::Stop(void)
{
	return;
}



END_NAMESPACE