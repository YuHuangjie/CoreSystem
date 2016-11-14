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
	// get and write RC signal every 20 ms to global RC buffer
	while (true) {
		/* Get Ticks on multiple channels */
		gRCBuffer.Throttle		= gPWMIO->GetTick(THROTTLE_IN);
		gRCBuffer.Roll			= gPWMIO->GetTick(ROLL_IN);
		gRCBuffer.Pitch			= gPWMIO->GetTick(PITCH_IN);
		gRCBuffer.Yaw			= gPWMIO->GetTick(YAW_IN);
		gRCBuffer.EnableVision	= gPWMIO->GetTick(VISION_IN);
		
		/* debug */
//		std::cout << "Throttle: " << gRCBuffer.Throttle << ", "
//			<< "Roll: " << gRCBuffer.Roll << ", " 
//			<< "Pitch: " << gRCBuffer.Pitch << ", "
//			<< "Yaw: " << gRCBuffer.Yaw << ", "
//			<< "VIsion: " << gRCBuffer.EnableVision << std::endl;

		/* wait for 20 ms */
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}


END_NAMESPACE
