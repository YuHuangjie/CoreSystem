#include "IMUThread.h"
#include "MessageFactory.h"
#include <chrono>
#include <cstring>

BEGIN_NAMESPACE

IMUThread::IMUThread()
{
	imu = new IMUA3();
	
	std::memset(&gIMUBuffer, 0, sizeof(gIMUBuffer));
}

IMUThread::~IMUThread()
{
	imu->Stop();
	delete imu;
	imu = nullptr;
}

bool IMUThread::Run(void)
{
	// initialize IMU device
	imu->Run();
	
	Acceleration accel;
	Velocity vel;
	AngVelocity angVel;
	Attitude atti;
	Magnet mag;
	// get and write IMU data every 20 ms to global buffer
	while (true) {
		// get IMU data
		accel = imu->GetAcceleration();
		vel = imu->GetVelocity();
		angVel = imu->GetAngVelocity();
		atti = imu->GetAttitude();
		mag = imu->GetMagnet();
		
		/* Write to global IMU buffer */
		WriteToIMUBuffer(accel, vel, angVel, atti, mag);
		
		/* wait for 10 ms */
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void IMUThread::WriteToIMUBuffer(
	const Acceleration &accel,
	const Velocity &vel,
	const AngVelocity &angVel,
	const Attitude &atti,
	const Magnet &mag)
{
//	std::lock_guard<std::mutex> lock(gIMUBufferMutex);
	gIMUBuffer.accel = accel;
	gIMUBuffer.vel = vel;
	gIMUBuffer.angVel = angVel;
	gIMUBuffer.atti = atti;
	gIMUBuffer.mag = mag;
}

END_NAMESPACE