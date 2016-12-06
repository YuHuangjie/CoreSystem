#ifndef IMUA3_H
#define IMUA3_H

#include "Define.h"
#include "IMU.h"
#include "IMUDataType.h"
#include <string>
#include <iostream>
#include <DJI_API.h>
#include <DJI_Flight.h>
#include "Thread.h"
#include "A3HardDriver.h"

BEGIN_NAMESPACE
	
class PollThread : public Thread
{
public:
	PollThread();
	void SetAPI(CoreAPI *api);
	CoreAPI *api;
	
protected:
	bool Run(void);
};


class IMUA3 : public IMU
{
public:
	IMUA3();
	~IMUA3();

	Acceleration GetAcceleration(void);
	Attitude GetAttitude(void);
	Velocity GetVelocity(void);
	AngVelocity GetAngVelocity(void);
	Magnet GetMagnet(void);
	Battery GetBattery(void);
	GPS GetGPS(void);
	
	void Run(void);

	void Stop(void);
	
private:
	void OpenPort(void);
	void ClosePort(void);
	
private:
	const string device;
	const int32_t baudrate;
	
	A3HardDriver *driver;
	CoreAPI *api;
	Flight *flight;
	
	PollThread pollThread;
	
	Acceleration accel;
	Velocity vel;
	AngVelocity angVel;
	Attitude atti;
	Magnet mag;
	Battery battery;
	GPS gps;
	
	friend class PollThread;
};

END_NAMESPACE

#endif