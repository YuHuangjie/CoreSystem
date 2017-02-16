#ifndef A3SERVO_H
#define A3SERVO_H

#include "Servo.h"
#include "PWMIO.h"

BEGIN_NAMESPACE

class A3Servo : public Servo
{
public:
	A3Servo(PWMIO *);

	void SetTick(int32_t channel, float tick);
	float GetTick(int32_t channel);

	void Run(void);
	void Stop(void);

private:
	PWMIO *pwmio;
}
;

END_NAMESPACE

#endif