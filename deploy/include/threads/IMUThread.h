#ifndef IMUTHREAD_H
#define IMUTHREAD_H

#include "Define.h"
#include "Thread.h"
#include "IMUA3.h"
#include <mutex>
#include "IMUDataType.h"
#include "DataLinkFormat.h"

BEGIN_NAMESPACE
	
extern IMUData gIMUBuffer;

/****************************
 *	data link down buffer
 ****************************/
extern DATALINK_DOWN_FORMAT gDownBuffer;
extern mutex gDownMutex;

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
		const Magnet &mag,
		const Battery &bat,
		const GPS &gps);
	
	void WriteDownBuffer(
		const Attitude &atti,
		const GPS &gps,
		const Velocity &,
		const Acceleration &accel,
		const AngVelocity &angVel);
};

END_NAMESPACE

#endif