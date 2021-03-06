#ifndef IMUDATATYPE_H
#define IMUDATATYPE_H

#include "Define.h"

BEGIN_NAMESPACE

typedef struct Acceleration
{
	float ax;
	float ay;
	float az;
} Acceleration;

typedef struct Velocity
{
	float vx;
	float vy;
	float vz;
} Velocity;

typedef struct AngVelocity
{ 
	float wx;
	float wy;
	float wz;
} AngVelocity;

typedef struct Attitude
{
	double yaw;
	double roll;
	double pitch;
} Attitude;

typedef struct Magnet
{
	int16_t mx;
	int16_t my;
	int16_t mz;
} Magnet;

typedef struct GimbalAttitude
{
	float roll;
	float pitch;
	float yaw;
	uint8_t rollLimit;
	uint8_t pitchLimit;
	uint8_t yawLimit;
} GimbalAttitude;

typedef struct Battery
{
	uint8_t battery;
} Battery;

typedef struct GPS
{
	uint32_t date;	// not used
	uint32_t time;	// not used
	double longitude;
	double latitude;
	double altitude;
	float height;
	float vel_N;	// not used
	float vel_E;	// not used
	float vel_D;	// not used
	uint8_t health;
} GPS;

typedef struct IMUData
{
	Acceleration accel;
	Velocity vel;
	AngVelocity angVel;
	Attitude atti;
	Magnet mag;
	Battery bat;
	GPS gps;
} IMUData;

END_NAMESPACE

#endif