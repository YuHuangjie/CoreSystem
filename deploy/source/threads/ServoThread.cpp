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
	int32_t timerCount = 0;
	int32_t logCount = 50;
	// initialize servo
	servo = new A3Servo(gPWMIO);
	servo->Run();

	float throttle, roll, pitch, yaw, mode, home;
	while (true) {
		// fetch servo buffer
		throttle 	= gServoBuffer.Throttle;
		roll 		= gServoBuffer.Roll;
		pitch 		= gServoBuffer.Pitch;
		yaw 		= gServoBuffer.Yaw;
		mode		= gServoBuffer.Mode;
		home		= gServoBuffer.Home;
		
		/* log */
		if (timerCount == logCount) {
			std::cout << "Update Servo  Throttle: " << throttle << ", "
				<< "Roll: " << roll << ", "
				<< "Pitch: " << pitch << ", "
				<< "Yaw: " << yaw << ", "
				<< "Mode: " << mode << ", "
				<< "Home: " << home << std::endl << std::endl;
			timerCount = 0;
		}
		else {
			++timerCount;
		}

		// Write PWM to servo every 50 ms
		servo->SetTick(THROTTLE_CHN, throttle);
		servo->SetTick(ROLL_CHN, roll);
		servo->SetTick(PITCH_CHN, pitch);
		servo->SetTick(YAW_CHN, yaw);
		servo->SetTick(MODE_CHN, mode);
		servo->SetTick(HOME_CHN, home);

		// 66 hz send PWM to servo
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}


END_NAMESPACE