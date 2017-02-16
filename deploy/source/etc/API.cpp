#include "API.h"
#include <csignal>

BEGIN_NAMESPACE
	
/************************************************
 *		global variables
 ************************************************/
	
/* Data Link global device */
DataLink *gDataLinkDevice;
	
/* heartbeat global */
const int32_t HEARTBEAT_INIT = 100;
int32_t gHeartbeat;	
	
/* Vision Switch global */
bool gVisionSwitch;

/* global Data Link Buffer */
DATALINK_DOWN_FORMAT gDownBuffer;
DATALINK_UP_FORMAT gUpBuffer;
mutex gDownMutex;
	
/* PWM input/output controller global */
PWMIO *gPWMIO;

/* remote control buffer global */
PWMData gRCBuffer;

/* servo buffer global */
PWMData gServoBuffer;

/* gimbal buffer global */
Au::GimbalData gGimbalBuffer;

/* IMU buffer global */
IMUData gIMUBuffer;

/* Message global */
MessageQueue gMessageQueue;

/* message queue mutex global */
mutex gMessageQueueMutex;

/* message buffer global */
MessageBuffer gMessageBuffer;

/* message buffer mutex global */
mutex gMessageBufferMutex;

/***********************************************************
 *		global threads
 **********************************************************/

/* global client thread */
ClientThread clientThread(/*TEST_*/VISION_ADDRESS, CORE_PORT);
/* global server thread */
ServerThread serverThread(/*TEST_*/CORE_ADDRESS, CORE_PORT);
/* global remote controler reading thread */
RCThread rcThread;
/* global IMU reading thread */
IMUThread imuThread;
/* global gimbal controling thread */
GimbalThread gimbalThread;
/* global heartbeat thread */
HeartbeatThread heartbeatThread;
/* global servo thread */
ServoThread servoThread;



void CheckVisionSwitch(void)
{
	// record previous vision switch status
	bool oldVisionSwitch = gVisionSwitch;
	
	if (gRCBuffer.EnableVision < 0.5f) {
		gVisionSwitch = false;
	}
	else if (gHeartbeat <= 1) {
		gVisionSwitch = false;
	}
	else {
		gVisionSwitch = true;
	}
	
	if (oldVisionSwitch && !gVisionSwitch) {
		/* log */
		cerr << "Vision switch turned off!" << endl;
		/* debug */
		cerr << "EnableVision channel: " << gRCBuffer.EnableVision << endl
			<< "Heartbeat: " << gHeartbeat << endl;
	}
	else if (!oldVisionSwitch && gVisionSwitch) {
		cerr << "Vision switch turned on!" << endl;
	}
	
	/* switch Vision from on to off */
	if (oldVisionSwitch && !gVisionSwitch) {
		// clear gimbal buffer
		gGimbalBuffer.Roll = gGimbalBuffer.Pitch = gGimbalBuffer.Yaw
			= gGimbalBuffer.Focus = 0;
	}
}

void Initialize(void)
{
	// ignore SIGPIPE which may crash the program when socket peer disconnected
	signal(SIGPIPE, SIG_IGN);
	
	/* Initialzie PWM Input/Output device */
	gPWMIO = new Au::NavioPWMIO();
	gPWMIO->Run();
	
	/* default vision switch off */
	gVisionSwitch = false;
}

bool PopRequest(Message &request)
{
	request.header = MessageFactory::CreateEmptyMessage();
	
	lock_guard<mutex> lock(gMessageBufferMutex);
	if (gMessageBuffer.Buffer.empty()) {
		return false;
	}
	// get request
	request = gMessageBuffer.Buffer.front();
	// remove request
	gMessageBuffer.Buffer.pop_front();

	return true;
}

void RequestHandler(Message &msg)
{
		/* debug */
	cout << msg.header.type << ", " << msg.header.length << ", "
		<< msg.header.priority << ", " << static_cast<void*>(msg.data) << endl;
	switch (msg.header.type) {

	case REQUEST_GET_RC:
		MessageRespondGetRC();
		delete msg.data;
		msg.data = nullptr;
		break;
		
	case REQUEST_IMU:
		MessageRespondGetIMU();
		delete msg.data;
		msg.data = nullptr;
		break;
		
	case REQUEST_UPDATE_GIMBAL:
		MessageRespondUpdateGimbal(static_cast<ClassicGimbalMsg*>(msg.data));
		delete msg.data;
		msg.data = nullptr;
		break;
		
	case REQUEST_HEARTBEAT:
		MessageRespondHeartbeat();
		delete msg.data;
		msg.data = nullptr;
		break;
		
	case REQUEST_UPDATE_SERVO:
		MessageRespondUpdateServo(static_cast<ClassicPWMMsg*>(msg.data));
		delete msg.data;
		msg.data = nullptr;
		break;
		
	default:
		cerr << "wrong type of request!" << endl;
		break;
	}
}

void MessageRespondGetRC(void)
{
	Message respond;
	
	respond.header = MessageFactory::CreateRespondGetRCMessage();
	respond.data = new ClassicPWMMsg(gRCBuffer);
	lock_guard<mutex> lock(gMessageQueueMutex);
	gMessageQueue.Queue.push(respond);
}

void MessageRespondGetIMU(void)
{
	Message respond;
	
	/* Get the current imu data */
	respond.header = MessageFactory::CreateRespondIMUMessage();
	respond.data = new ClassicIMUMsg(gIMUBuffer);
	/* Push respond message to message queue for client thread to deal with */
	lock_guard<mutex> lock(gMessageQueueMutex);
	gMessageQueue.Queue.push(respond);
}

void MessageRespondUpdateGimbal(const ClassicGimbalMsg *msg)
{
	bool reacted = false;
	
	if (gVisionSwitch) {
		// send gimba msg to gimbal buffer
		gGimbalBuffer.Roll	= msg->data.Roll;
		gGimbalBuffer.Pitch = msg->data.Pitch;
		gGimbalBuffer.Yaw	= msg->data.Yaw;
		gGimbalBuffer.Focus = msg->data.Focus;
		reacted = true;
	}
	
	Message respond;

	/* respond true or false */
	respond.header = MessageFactory::CreateRespondUpdateGimbalMessage();
	respond.data = new Float32Msg(reacted);
	lock_guard<mutex> lock(gMessageQueueMutex);
	gMessageQueue.Queue.push(respond);	
}

void MessageRespondUpdateServo(const ClassicPWMMsg *msg)
{
	bool reacted = false;
	
	if (gVisionSwitch) {
		// send msg data to servo buffer
		UpdateServo(msg->data.Throttle,
			msg->data.Roll,
			msg->data.Pitch,
			msg->data.Yaw,
			gRCBuffer.Mode,
			gRCBuffer.Home);
		reacted = true;
	}
	
	Message respond;
	/* respond true or false */
	respond.header = MessageFactory::CreateRespondUpdateServoMessage();
	respond.data = new Float32Msg(reacted);
	lock_guard<mutex> lock(gMessageQueueMutex);
	gMessageQueue.Queue.push(respond);
}

void MessageRespondHeartbeat(void)
{
	// update heartbeat
	gHeartbeat = HEARTBEAT_INIT;
	
	// respond heartbeat
	/* do nothing to respond heartbeat message */
}

void UpdateServo(float throttle, float roll, float pitch, float yaw, float mode, float home)
{
	// update servo buffer
	gServoBuffer.Throttle = throttle;
	gServoBuffer.Roll = roll;
	gServoBuffer.Pitch = pitch;
	gServoBuffer.Yaw = yaw;
	gServoBuffer.Mode = mode;
	gServoBuffer.Home = home;
}

void UpdateServo(void)
{
	// update servo using rc data if Extended computing system is disabled
	if (!gVisionSwitch) {
		UpdateServo(
			gRCBuffer.Throttle,
			gRCBuffer.Roll,
			gRCBuffer.Pitch,
			gRCBuffer.Yaw,
			gRCBuffer.Mode,
			gRCBuffer.Home);
	}
}

bool InitializeDataLink(void)
{
	gDataLinkDevice = new XtendDataLink(0, 115200, DataLinkSender);
	bool ret = gDataLinkDevice->Run();
	
	return ret;
}


END_NAMESPACE