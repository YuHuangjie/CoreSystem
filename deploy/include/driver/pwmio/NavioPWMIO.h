#ifndef NAVIOPWMIO_H
#define NAVIOPWMIO_H

#include "PWMIO.h"
#include <gpio.h>
#include <PCA9685.h>
#include <pigpio.h>
#include <mutex>

BEGIN_NAMESPACE
	
class NavioPWMIO : public PWMIO
{
public:
	NavioPWMIO();
	~NavioPWMIO();
	
	float GetTick(int32_t channel);
	void SetTick(int32_t channel, float tick);
	
	void Run(void);
	void Stop(void);
	
private:
//	PCA9685 *pwm;
	std::mutex pwmMutex;
};
	
	
END_NAMESPACE
	
#endif