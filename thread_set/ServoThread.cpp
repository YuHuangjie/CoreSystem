#include "ServoThread.h"
#include <chrono>
#include <cstring>
#include <iostream>

BEGIN_NAMESPACE

ServoThread::ServoThread()
{
	std::memset(&gServoBuffer, 0, sizeof(gServoBuffer));
}

ServoThread::~ServoThread()
{
	if (servo != nullptr) {
		delete servo;
	}
}

bool ServoThread::Run(void)
{
	// initialize servo
	servo = new A3Servo(gPWMIO);
	servo->Run();

	float throttle, roll, pitch, yaw;
	while (true) {
		// fetch servo buffer
		throttle 	= gServoBuffer.Throttle;
		roll 	= gServoBuffer.Roll;
		pitch 	= gServoBuffer.Pitch;
		yaw 	= gServoBuffer.Yaw;
		
		/* debug */
//		std::cout << "Update Servo  Throttle: " << throttle << ", "
//			<< "Roll: " << roll << ", "
//			<< "Pitch: " << pitch << ", "
//			<< "Yaw: " << yaw << std::endl;

		// Write PWM to servo every 50 ms
		servo->SetTick(THROTTLE_OUT, throttle);
		servo->SetTick(ROLL_OUT, roll);
		servo->SetTick(PITCH_OUT, pitch);
		servo->SetTick(YAW_OUT, yaw);

		// 66 hz send PWM to servo
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}
}


END_NAMESPACE