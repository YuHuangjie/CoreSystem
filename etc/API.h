#ifndef API_H
#define API_H

#include "Define.h"
#include "ClientThread.h"
#include "ServerThread.h"
#include "RcThread.h"
#include "GimbalThread.h"
#include "HeartbeatThread.h"
#include "IMUThread.h"
#include "ServoThread.h"

#include "MessageBuffer.h"
#include "MessageQueue.h"
#include "MessageFactory.h"
#include "StdMessage.h"

#include "NavioPWMIO.h"
#include "GimbalDataType.h"
#include "IMUDataType.h"
#include "PWMDataType.h"

#include <mutex>


BEGIN_NAMESPACE
	
/* 
 * Function prototype 
 */
void Initialize(void);
bool PopRequest(Message &msg);
void RequestHandler(Message &msg);
void MessageRespondGetIMU(void);
void MessageRespondGetRC(void);
void MessageRespondUpdateGimbal(const ClassicGimbalMsg *msg);
void MessageRespondHeartbeat(void);
void MessageRespondUpdateServo(const ClassicPWMMsg *msg);
void CheckVisionSwitch(void);
void UpdateServo(float throttle, float roll, float pitch, float yaw);
void UpdateRC2Servo(void);

/*
 * global variables
 */
extern int32_t gHeartbeat;	
extern bool gVisionSwitch;

extern PWMIO *gPWMIO;

extern PWMData gRCBuffer;
extern Au::GimbalData gGimbalBuffer;
extern PWMData gServoBuffer;
extern IMUData gIMUBuffer;

extern MessageQueue gMessageQueue;
extern mutex gMessageQueueMutex;
extern MessageBuffer gMessageBuffer;
extern mutex gMessageBufferMutex;

extern ClientThread clientThread;
extern ServerThread serverThread;
extern RCThread rcThread;
extern IMUThread imuThread;
extern GimbalThread gimbalThread;
extern HeartbeatThread heartbeatThread;
extern ServoThread servoThread;



END_NAMESPACE

#endif