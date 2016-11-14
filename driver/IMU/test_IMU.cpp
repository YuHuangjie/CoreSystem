#include "IMU.h"
#include "IMUA3.h"
#include <iostream>
#include "Message.h"
#include <mutex>
#include "MessageQueue.h"
#include "MessageBuffer.h"
#include "IMUThread.h"
#include "StdMessage.h"

using namespace std;
using namespace Au;

// rc related buffer and mutex
Message gRCRollBuffer;
Message gRCYawBuffer;
Message gRCPitchBuffer;
Message gRCThrottleBuffer;

mutex gRCRollBufferMutex;
mutex gRCYawBufferMutex;
mutex gRCPitchBufferMutex;
mutex gRCThrottleBufferMutex;

// message related buffer and mutex
MessageQueue gMessageQueue;
mutex gMessageQueueMutex;
MessageBuffer gMessageBuffer;
mutex gMessageBufferMutex;

// imu related buffer and mutex
Message gIMUBuffer;
mutex gIMUBufferMutex;

int main()
{
	IMUThread imuThread;
	imuThread.Start();
	ClassicIMUMsg *imuData;
	
	while (true) {
		imuData = (ClassicIMUMsg*)(gIMUBuffer.data);
		cout << imuData->atti.roll << " " 
			<< imuData->atti.yaw << " "
			<< imuData->atti.pitch << " "
			<< endl;
	}
	
}