#ifndef A3HARDDRIVER_H
#define A3HARDDRIVER_H

#include "Define.h"
#include <cstdint>
#include <string>
#include <pthread.h>
#include <wiringSerial.h>
#include <wiringPi.h>
#include <DJI_HardDriver.h>

using namespace DJI::onboardSDK;
using namespace std;

BEGIN_NAMESPACE

class A3HardDriver : public HardDriver
{
public:
	A3HardDriver(string device, int baudrate);

	void init();
	DJI::time_ms getTimeStamp();
	size_t send(const uint8_t *buf, size_t len);
	size_t readall(uint8_t *buf, size_t maxlen);

	void lockMemory();
	void freeMemory();

	void lockMSG();
	void freeMSG();

	void lockACK();
	void freeACK();

	void notify();
	void wait(int timeout);

	void displayLog(const char *buf = 0);
	
	void close();

private:
	string device;
	int baudrate;
	int fd;

	pthread_mutex_t sendLock;
	pthread_mutex_t memory;
	pthread_mutex_t msg;
	pthread_mutex_t ack;
};

END_NAMESPACE

#endif