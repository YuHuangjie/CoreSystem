#include "GimbalThread.h"
#include <chrono>
#include <cstring>
#include <iostream>

BEGIN_NAMESPACE

GimbalThread::GimbalThread()
{
	std::memset(&gGimbalBuffer, 0, sizeof(gGimbalBuffer));
}

GimbalThread::~GimbalThread()
{
	if (gimbal != nullptr) {
		delete gimbal;
	}
}

bool GimbalThread::Run(void)
{
	// initialize gimbal
	gimbal = new SKnightGimbal(gPWMIO);
	gimbal->Run();

	float roll, pitch, yaw, focus;
	while (true) {
		// analyze gimbal buffer
		roll 	= gGimbalBuffer.Roll;
		pitch 	= gGimbalBuffer.Pitch;
		yaw 	= gGimbalBuffer.Yaw;
		focus 	= gGimbalBuffer.Focus;
		
		/* debug */
//		std::cout << "Update GIMBAL  Roll: " << roll << ", "
//			<< "Pitch: " << pitch << ", "
//			<< "Yaw: " << yaw << ", "
//			<< "Focus: " << focus << std::endl;

		// Write PWM to gimbal every 50 ms
		gimbal->SetTick(GIMBAL_ROLL_OUT, roll);
		gimbal->SetTick(GIMBAL_PITCH_OUT, pitch);
		gimbal->SetTick(GIMBAL_YAW_OUT, yaw);
		gimbal->SetTick(GIMBAL_FOCUS_OUT, focus);

		// halt
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}


END_NAMESPACE