#include "IMUA3.h"
#include <ctime>
#include <unistd.h>

using namespace DJI;
using namespace DJI::onboardSDK;

#define PI 3.1415927

BEGIN_NAMESPACE
	
/*
 * implement Poll Thread 
 */
PollThread::PollThread()
{ 
}

void PollThread::SetAPI(CoreAPI *api)
{
	this->api = api;
}

bool PollThread::Run(void)
{
	float timeout = 2;
	clock_t start;
	
	while (true)
	{
		if (api == nullptr) { 
			return false;
		}
		start = clock();
		api->sendPoll();
		api->readPoll();
		
		while (clock() - start < (CLOCKS_PER_SEC * timeout / 1000))
			usleep(1000);
	}
}

/*
 * Implement A3 IMU data retriving
 */

IMUA3::IMUA3()
	: device("/dev/ttyS0")
	, baudrate(115200)
{
	driver = new A3HardDriver(device, baudrate);
	api = new CoreAPI(driver);
	api->setVersion(versionA3_31);
	flight = new Flight(api);
	pollThread.SetAPI(api);
}

IMUA3::~IMUA3()
{
	delete flight;
	flight = nullptr;
	delete api;
	api = nullptr;
	delete driver;
	driver = nullptr;
	
	if (pollThread.Joinable()) {
		pollThread.Join();
	}
}

void IMUA3::OpenPort()
{
	driver->init();
}

void IMUA3::ClosePort()
{
	driver->close();
}

void IMUA3::Run(void)
{
	OpenPort();
	pollThread.Start();
}

void IMUA3::Stop(void)
{
	ClosePort();
}

Attitude IMUA3::GetAttitude(void)
{
	Attitude ret;
	Angle roll  = flight->getRoll();	// DJI data type
	Angle yaw   = flight->getYaw();
	Angle pitch = flight->getPitch();
	ret.roll   = roll * 180 / PI;
	ret.yaw    = yaw * 180 / PI;
	ret.pitch  = pitch * 180 / PI;
	return ret;
}

Battery IMUA3::GetBattery(void)
{
	Battery ret;
	BroadcastData broadcast = api->getBroadcastData();	// DJI data type
	ret.battery = broadcast.battery;
	return ret;	
}

Acceleration IMUA3::GetAcceleration(void)
{
	Acceleration ret;
	CommonData acce = flight->getAcceleration();	// DJI data type
	ret.ax = acce.x;
	ret.ay = acce.y;
	ret.az = acce.z;
	return ret;
}

Velocity IMUA3::GetVelocity(void)
{
	Velocity ret;
	VelocityData vel = flight->getVelocity();	// DJI data type
	ret.vx = vel.x;
	ret.vy = vel.y;
	ret.vz = vel.z;
	return ret;
}

AngVelocity IMUA3::GetAngVelocity(void)
{
	AngVelocity ret;
	CommonData angVel = flight->getYawRate();	// DJI data type
	ret.wx = angVel.x;
	ret.wy = angVel.y;
	ret.wz = angVel.z;
	return ret;
}

Magnet IMUA3::GetMagnet(void)
{
	Magnet ret;
	MagnetData mag = flight->getMagnet();	// DJI data type
	ret.mx = mag.x;
	ret.my = mag.y;
	ret.mz = mag.z;
	return ret;
}

GPS IMUA3::GetGPS(void)
{
	GPS ret;
	PositionData gps = flight->getPosition();
//	GPSData gpsDetail = (api->getBroadcastData()).gps;
//	ret.date = gpsDetail.date;
//	ret.time = gpsDetail.time;
//	ret.longitude = gpsDetail.longitude;
//	ret.latitude = gpsDetail.latitude;
//	ret.altitude = gpsDetail.Hmsl;
//	ret.vel_N = gpsDetail.velocityNorth;
//	ret.vel_E = gpsDetail.velocityEast;
//	ret.vel_D = gpsDetail.velocityGround;
	ret.longitude = gps.longitude * 180 / PI;
	ret.latitude = gps.latitude * 180 / PI;
	ret.altitude = gps.altitude;
	
	ret.height = gps.height;
	ret.health = gps.health;
	return ret;
}
	
END_NAMESPACE