#include "StdMessage.h"

BEGIN_NAMESPACE
	
/*
 * Single float data message
 */
string Float32Msg::Pack(void) const
{
	ostringstream oss;
	oss << data;
	return oss.str();
}

bool Float32Msg::Unpack(string &raw)
{
	if (raw.empty())
		return false;

	istringstream iss(raw);
	iss >> data;
	return true;
}


/*
 * Classic IMU message containing Acceleration, Velocity, Angular Velocity,
 * Attitude, Magnet
 */
ClassicIMUMsg::ClassicIMUMsg(const IMUData &data)
{
	this->data = data;
}

string ClassicIMUMsg::Pack(void) const
{
	ostringstream oss;
	oss << data.accel.ax   << " " << data.accel.ay   << " " << data.accel.az    << " "
		<< data.vel.vx	   << " " << data.vel.vy     << " " << data.vel.vz      << " "
		<< data.angVel.wx  << " " << data.angVel.wy  << " " << data.angVel.wz   << " "
		<< data.atti.roll  << " " << data.atti.yaw   << " " << data.atti.pitch  << " "
		<< data.mag.mx     << " " << data.mag.my     << " " << data.mag.mz;
	return oss.str();
}

bool ClassicIMUMsg::Unpack(string &raw)
{
	if (raw.empty())
		return false;
	
	istringstream iss(raw);
	iss >> data.accel.ax   >> data.accel.ay   >> data.accel.az
		>> data.vel.vx     >> data.vel.vy     >> data.vel.vz
		>> data.angVel.wx  >> data.angVel.wy  >> data.angVel.wz
		>> data.atti.roll  >> data.atti.yaw   >> data.atti.pitch
		>> data.mag.mx     >> data.mag.my     >> data.mag.mz;
	return true;
}
	
/*
 * Classic PWM message containing Throttle, Roll, Yaw, Pitch, EnableVision
 * and three reserved member
 */
ClassicPWMMsg::ClassicPWMMsg(const PWMData &data)
{
	this->data = data;
}


string ClassicPWMMsg::Pack(void) const
{
	ostringstream oss;
	oss << data.Throttle << " " << data.Roll << " "
		<< data.Pitch << " " << data.Yaw << " "
		<< data.EnableVision << " " << data._n2 << " "
		<< data._n3 << " " << data._n4;
	return oss.str();
}

bool ClassicPWMMsg::Unpack(string &raw) 
{
	if (raw.empty()) {
		return false;
	}
	
	istringstream iss(raw);
	iss >> data.Throttle >> data.Roll >> data.Pitch >> data.Yaw
		>> data.EnableVision >> data._n2 >> data._n3 >> data._n4;
	return true;
}

/*
 * Classic Gimbal Message containing Roll, Pitch, Yaw, Focus and four reserved 
 * member
 */
ClassicGimbalMsg::ClassicGimbalMsg(const GimbalData &data)
{
	this->data = data;
}

string ClassicGimbalMsg::Pack(void) const 
{
	ostringstream oss;
	oss << data.Roll << " " << data.Pitch << " "
		<< data.Yaw << " " << data.Focus << " "
		<< data._n1 << " " << data._n2 << " "
		<< data._n3 << " " << data._n4;
	return oss.str();
}

bool ClassicGimbalMsg::Unpack(string &raw)
{
	if (raw.empty()) {
		return false;
	}

	istringstream iss(raw);
	iss >> data.Roll >> data.Pitch >> data.Yaw >> data.Focus
		>> data._n1 >> data._n2 >> data._n3 >> data._n4;
	return true;
}

END_NAMESPACE