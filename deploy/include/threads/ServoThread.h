#ifndef SERVOTHREAD_H
#define SERVOTHREAD_H

#include "Define.h"
#include "Thread.h"
#include "PWMDataType.h"
#include "PWMIO.h"
#include "A3Servo.h"


BEGIN_NAMESPACE

extern PWMData gServoBuffer;
extern PWMIO *gPWMIO;

class ServoThread : public Thread
{
public:
	ServoThread();
	~ServoThread();

	bool Run(void);

private:
	Servo *servo;
};

END_NAMESPACE

#endif