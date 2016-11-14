#ifndef IMUTHREAD_H
#define IMUTHREAD_H

#include "Define.h"
#include "Thread.h"
#include "IMUA3.h"
#include <mutex>
#include "IMUDataType.h"


BEGIN_NAMESPACE
	
extern IMUData gIMUBuffer;

class IMUThread : public Thread
{
public:
	IMUThread();
	~IMUThread();
	
	bool Run(void);
	
private:
	IMU *imu;
	
	void WriteToIMUBuffer(
		const Acceleration &accel,
		const Velocity &vel,
		const AngVelocity &angVel,
		const Attitude &atti,
		const Magnet &mag);
};

END_NAMESPACE

#endif