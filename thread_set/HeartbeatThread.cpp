#include "HeartbeatThread.h"
#include <chrono>
#include <iostream>

BEGIN_NAMESPACE
	
HeartbeatThread::HeartbeatThread()
{
	gHeartbeat = 0;
}

bool HeartbeatThread::Run(void)
{
	/* decrease heartbeat every 10 ms */
	while (true) {
		if (gHeartbeat > 0) {
			gHeartbeat--;
//			std::cout << "HEART: " << gHeartbeat << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
	
END_NAMESPACE