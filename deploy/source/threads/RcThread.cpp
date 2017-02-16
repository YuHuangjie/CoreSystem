/*
 * RcThread.cpp
 *
 *  Created on: Nov 1, 2016
 *      Author: jacob
 */

#include "RcThread.h"
#include <chrono>
#include <iostream>

BEGIN_NAMESPACE

RCThread::RCThread()
{	}

RCThread::~RCThread()
{	}

bool RCThread::Run(void)
{
	int32_t timerCount = 0;
	int32_t logCount = 50;
	
	// get and write RC signal every 20 ms to global RC buffer
	while (true) {
		/* Get Ticks on multiple channels */
		gRCBuffer.Throttle		= gPWMIO->GetTick(THROTTLE_CHN);
		gRCBuffer.Roll			= gPWMIO->GetTick(ROLL_CHN);
		gRCBuffer.Pitch			= gPWMIO->GetTick(PITCH_CHN);
		gRCBuffer.Yaw			= gPWMIO->GetTick(YAW_CHN);
		gRCBuffer.EnableVision	= gPWMIO->GetTick(VISION_CHN);
		gRCBuffer.Mode			= gPWMIO->GetTick(MODE_CHN);
		gRCBuffer.Home			= gPWMIO->GetTick(HOME_CHN);
		
		/* Write to down buffer of data link */
		WriteDownBuffer(gRCBuffer.Roll, gRCBuffer.Pitch, gRCBuffer.Yaw, gRCBuffer.Throttle);
		
		/* log */
		if (timerCount == logCount) {
			std::cout << "Receive RC: Throttle: " << gRCBuffer.Throttle << ", "
				<< "Roll: " << gRCBuffer.Roll << ", " 
				<< "Pitch: " << gRCBuffer.Pitch << ", "
				<< "Yaw: " << gRCBuffer.Yaw << ", "
				<< "VIsion: " << gRCBuffer.EnableVision << ", "
				<< "Mode: " << gRCBuffer.Mode << ", "
				<< "Home: " << gRCBuffer.Home << std::endl << std::endl;
			timerCount = 0;
		}
		else {
			++timerCount;
		}


		/* wait for 20 ms */
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}

void RCThread::WriteDownBuffer(float roll, float pitch, float yaw, float throttle)
{
	for (int i = 0; i != 5; ++i) {
		if (gDownMutex.try_lock()) {
			gDownBuffer.roll = roll;
			gDownBuffer.pitch = pitch;
			gDownBuffer.yaw = yaw;
			gDownBuffer.throttle = throttle;
			
			gDownMutex.unlock();
			return;
		}
	}
}


END_NAMESPACE
