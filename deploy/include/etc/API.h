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

#include "XtendDataLink.h"

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
	
/****************************************************
 *		Function prototype 
 ****************************************************/
void Initialize(void);
bool PopRequest(Message &msg);
void RequestHandler(Message &msg);
void MessageRespondGetIMU(void);
void MessageRespondGetRC(void);
void MessageRespondUpdateGimbal(const ClassicGimbalMsg *msg);
void MessageRespondHeartbeat(void);
void MessageRespondUpdateServo(const ClassicPWMMsg *msg);
void CheckVisionSwitch(void);
void UpdateServo(float throttle, float roll, float pitch, float yaw, float mode, float home);
void UpdateServo(void);
bool InitializeDataLink(void);


/************************************************
 *		Global Threads
 ************************************************/
extern ClientThread clientThread;
extern ServerThread serverThread;
extern RCThread rcThread;
extern IMUThread imuThread;
extern GimbalThread gimbalThread;
extern HeartbeatThread heartbeatThread;
extern ServoThread servoThread;


/**************************************************
 *		Data Link global device
 **************************************************/
// extern DataLink *gDataLinkDevice;

/*******************************************************
 *		global Data Link Buffer
 *****************************************************/
// extern DATALINK_DOWN_FORMAT gDownBuffer;
// extern DATALINK_UP_FORMAT gUpBuffer;
// extern mutex gDownMutex;

/*************************************
 *       heartbeat global
 *************************************/
// extern int32_t gHeartbeat;	

/*************************************
 *		Vision Switch global 
 *************************************/
// extern bool gVisionSwitch;

/*****************************************************
 *		PWM input/output controller global 
 *****************************************************/
// extern PWMIO *gPWMIO;

/****************************************************
 *		remote control buffer global 
 ***************************************************/
// extern PWMData gRCBuffer;

/**************************************************
 *		gimbal buffer global 
 **************************************************/
// extern Au::GimbalData gGimbalBuffer;

/***************************************************
 *		servo buffer global 
 ****************************************************/
// extern PWMData gServoBuffer;

/*************************************************
 *		IMU buffer global 
 *************************************************/
// extern IMUData gIMUBuffer;

/************************************************
 *		Message global 
 ************************************************/
//extern MessageQueue gMessageQueue;
//extern mutex gMessageQueueMutex;
//extern MessageBuffer gMessageBuffer;
//extern mutex gMessageBufferMutex;



END_NAMESPACE

#endif