#include <iostream>
#include "API.h"

using namespace std;

int main()
{
	/* global init */
	Au::Initialize();
	cout << "init end" << endl;
	
	/* activate child threads */
	Au::serverThread.Start();
	Au::clientThread.Start();
	Au::rcThread.Start();
	Au::imuThread.Start();
	Au::gimbalThread.Start();
	Au::servoThread.Start();
	Au::heartbeatThread.Start();

	int32_t ret;
	/* main thread acts on requests*/
	Au::Message request;
	while (true) {
		/* check tx1 switch */
		Au::CheckVisionSwitch();
		
		/* pass rc signal to servo if vision is disabled */
		Au::UpdateRC2Servo();
		
		/* Check any request messages on gMessageBuffer */
		if (Au::PopRequest(request)) {
			Au::RequestHandler(request);
		}
	}
}
