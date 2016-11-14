#ifndef IMU_H
#define IMU_H

#include "Define.h"
#include "IMUDataType.h"

BEGIN_NAMESPACE

class IMU
{
public:
	virtual ~IMU()
	{	}
	
	// Get IMU information
	virtual Acceleration GetAcceleration(void) = 0;
	virtual Velocity GetVelocity(void) = 0;
	virtual AngVelocity GetAngVelocity(void) = 0;
	virtual Attitude GetAttitude(void) = 0;
	virtual Magnet GetMagnet(void) = 0;
	
	/*
	 * Run() method must be called before making any requirements
	 */
	virtual void Run(void) = 0;
	
	/*
	 * Stop() method
	 */
	virtual void Stop(void) = 0;
};

END_NAMESPACE

#endif