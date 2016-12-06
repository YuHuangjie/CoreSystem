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
	int32_t timerCount = 0;
	int32_t logCount = 50;
	
	// initialize IMU device
	imu->Run();
	
	Acceleration accel;
	Velocity vel;
	AngVelocity angVel;
	Attitude atti;
	Magnet mag;
	Battery bat;
	GPS gps;
	// get and write IMU data every 20 ms to global buffer
	while (true) {
		// get IMU data
		accel = imu->GetAcceleration();
		vel = imu->GetVelocity();
		angVel = imu->GetAngVelocity();
		atti = imu->GetAttitude();
		mag = imu->GetMagnet();
		bat = imu->GetBattery();
		gps = imu->GetGPS();
		
		/* Write to global IMU buffer */
		WriteToIMUBuffer(accel, vel, angVel, atti, mag, bat, gps);
		
		/* log */
		if (timerCount == logCount) {
			cout << "IMU ROLL: " << atti.roll << ", "
			<< "YAW: " << atti.yaw << ", "
			<< "PITCH: " << atti.pitch
			<< endl
			<< "IMU Acceleration x: " << accel.ax << ", "
			<< "y: " << accel.ay << ", "
			<< "z: " << accel.az 
			<< endl
			<< "IMU Velocity x: " << vel.vx << ", "
			<< "y: " << vel.vy << ", "
			<< "z: " << vel.vz 
			<< endl
			<< "IMU Angular Velocity x: " << angVel.wx << ", "
			<< "y: " << angVel.wy << ", "
			<< "z: " << angVel.wz
			<< endl
			<< "IMU Magnet x: " << mag.mx << ", "
			<< "y: " << mag.my << ", "
			<< "z: " << mag.mz
			<< endl
//			<< "IMU GPS date" << gps.date << ", time: " << gps.time << ", "
			<< "longitude: " << gps.longitude << ", latitude: " << gps.latitude << ", "
			<< "altitude: " << gps.altitude << ", height: " << gps.height << ", "
//			<< "velocity north: " << gps.vel_N << ", velocity east: " << gps.vel_E << ", "
//			<< "velocity down: " << gps.vel_D << ", " 
			<< "health: " << (int32_t)gps.health
			<< endl
			<< "Battery: " << (int32_t)bat.battery
			<< endl << endl;
			timerCount = 0;
		}
		else {
			++timerCount;
		}
		
		/* wait for 10 ms */
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void IMUThread::WriteToIMUBuffer(
	const Acceleration &accel,
	const Velocity &vel,
	const AngVelocity &angVel,
	const Attitude &atti,
	const Magnet &mag,
	const Battery &bat,
	const GPS &gps)
{
//	std::lock_guard<std::mutex> lock(gIMUBufferMutex);
	gIMUBuffer.accel = accel;
	gIMUBuffer.vel = vel;
	gIMUBuffer.angVel = angVel;
	gIMUBuffer.atti = atti;
	gIMUBuffer.mag = mag;
	gIMUBuffer.bat = bat;
	gIMUBuffer.gps = gps;
}

END_NAMESPACE