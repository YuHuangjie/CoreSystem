#ifndef DATALINKFORMAT_H
#define DATALINKFORMAT_H

#include "Define.h"

BEGIN_NAMESPACE

enum DATALINK_PARAM_TYPE
{
	DATALINK_PARAM_NONE
};

struct DATALINK_DOWN_FORMAT
{
	int32_t roll;
	int32_t pitch;
	int32_t yaw;
	int32_t throttle;

	float imu_roll;
	float imu_pitch;
	float imu_yaw;

	float gps_lontitude;
	float gps_latitude;
	float gps_altitude;
	float gps_height;

	float pressure_altitude;

	float u_x, u_y, u_z;
	float omega_x, omega_y, omega_z;

	float a_x, a_y, a_z;

	DATALINK_PARAM_TYPE param_type;
	char param[20];
};

struct DATALINK_UP_FORMAT
{
	int32_t roll;
	int32_t pitch;
	int32_t yaw;
	int32_t throttle;

	char options[4];

	DATALINK_PARAM_TYPE param_type;
	char param[20];
};


END_NAMESPACE

#endif