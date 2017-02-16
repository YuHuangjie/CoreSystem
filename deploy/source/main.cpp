#include <iostream>
#include "API.h"

using namespace std;

extern Au::DATALINK_DOWN_FORMAT Au::gDownBuffer;

int main()
{
	/* global init */
	Au::Initialize();
	cout << "init end" << endl;
	
	/* Initialize data link */
	Au::InitializeDataLink();
	
	/* activate child threads */
//	Au::serverThread.Start();
//	Au::clientThread.Start();
//	Au::rcThread.Start();
//	Au::imuThread.Start();
//	Au::gimbalThread.Start();
//	Au::servoThread.Start();
//	Au::heartbeatThread.Start();

	int32_t ret;
	int32_t i = 0;
	Au::Message request;
	
	/* main thread acts on requests*/
	while (true) {
		/* check tx1 switch */
		Au::CheckVisionSwitch();
		
		/* pass rc signal to servo if vision is disabled */
		Au::UpdateServo();
		
		/* Check any request messages on gMessageBuffer */
		if (Au::PopRequest(request)) {
			Au::RequestHandler(request);
		}
		
		/* test data link */
		i++;
		Au::gDownBuffer.roll = i;
	}
}
