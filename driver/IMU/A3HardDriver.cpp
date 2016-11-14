#include "A3HardDriver.h"
#include <unistd.h>
#include <iostream>
#include <ctime>

BEGIN_NAMESPACE

A3HardDriver::A3HardDriver(string device, int baudrate)
	: device(device)
	, baudrate(baudrate)
{
	fd = 0;
	sendLock = PTHREAD_MUTEX_INITIALIZER;
	memory = PTHREAD_MUTEX_INITIALIZER;
	msg = PTHREAD_MUTEX_INITIALIZER;
	ack = PTHREAD_MUTEX_INITIALIZER;
}

void A3HardDriver::init()
{
	if (wiringPiSetup() == -1) {
		cerr << "Unable to start wiringPi\n";
		return;
	}

	if (!device.empty()) {
		fd = serialOpen(device.c_str(), baudrate);
	}
	else {
		cerr << "No device provided\n";
		return;
	}

	if (fd < 0) {
		cerr << "Unable to open serial device: " << device << endl;
		return;
	}
}

size_t A3HardDriver::send(const uint8_t *buf, size_t len)
{	
	pthread_mutex_lock(&sendLock);
	size_t sent = write(fd, buf, len);
	if (sent != len) {
		//cout << "unexpected error: sent bytes unequal to given length\n";
		//exit(-1);
		return false;
	}

	return sent;
}

size_t A3HardDriver::readall(uint8_t *buf, size_t maxlen) 
{
	size_t ans = read(fd, buf, maxlen);
	if (ans == -1)
//		cerr << "read false" << endl;
	
	return ans;
}

DJI::time_ms A3HardDriver::getTimeStamp()
{
	return time(NULL);
}

void A3HardDriver::lockMemory()
{
	pthread_mutex_lock(&memory);
}

void A3HardDriver::freeMemory()
{
	pthread_mutex_unlock(&memory);
}

void A3HardDriver::lockMSG()
{
	pthread_mutex_lock(&msg);
}

void A3HardDriver::freeMSG()
{
	pthread_mutex_unlock(&msg);
}

void A3HardDriver::lockACK()
{
	pthread_mutex_lock(&ack);
}

void A3HardDriver::freeACK()
{
	pthread_mutex_unlock(&ack);
}

void A3HardDriver::displayLog(const char *buf)
{
	clog << buf << endl;
}

void A3HardDriver::notify() {}

void A3HardDriver::wait(int timeout) {}

void A3HardDriver::close()
{
	serialClose(fd);
}

END_NAMESPACE