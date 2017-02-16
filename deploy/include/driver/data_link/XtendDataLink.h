#ifndef XTENDDATALINK_H
#define XTENDDATALINK_H

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <pthread.h>
#include <sys/file.h>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <time.h>
#include <mutex>
#include <thread>

#include "DataLink.h"
#include "DataConverter.h"

using namespace std;

BEGIN_NAMESPACE
	
extern DATALINK_DOWN_FORMAT gDownBuffer;
extern DATALINK_UP_FORMAT gUpBuffer;
extern mutex gDownMutex;


/**************************************************
 *		serial device struct
 *************************************************/
typedef struct tty_info_t
{
	int fd;			// serial file descriptor
	pthread_mutex_t mt;
	char name[24];	// serial device name, such as "/dev/ttyS0"
	struct termios ntm;	// new serial device options
	struct termios otm;	// old serial device options
} TTY_INFO;



class XtendDataLink : public DataLink
{
public:
	XtendDataLink(int port, int bardrate, DataLinkID, size_t frameSize = 256);
	~XtendDataLink();

	bool Run(void);
	bool Stop(void);

	bool Send(const std::string &);
	bool Recv(std::string &);

	bool SetDownData(const DATALINK_DOWN_FORMAT &);
	bool GetUpData(DATALINK_UP_FORMAT &);

    string Down2String(const DATALINK_DOWN_FORMAT &) const;
	string Up2String(const DATALINK_UP_FORMAT &) const;
	bool String2Down(const string &, DATALINK_DOWN_FORMAT &) const;
	bool String2Up(const string &, DATALINK_UP_FORMAT &) const;

private:
	// initialize serial device and save options
	TTY_INFO *ReadyTTY(int id);
	// set serial bard rate
	int SetTTYSpeed(int speed);
	int SetTTYParity(int databits, char parity, int stopbits);
	// clean serial device resources
	int CleanTTY(void);
	int SendnTTY(unsigned char *pbuf,int size);
	int RecvnTTY(unsigned char *pbuf,int size, const float &timeout);
	int LockTTY(void);
	int UnlockTTY(void);

	bool ChangeString(const string &);
	void SendThread(void);
	void ListenThread(void);

	int port;
	int bardrate;
	TTY_INFO *ptty;
	string startSign;
	string stopSign;
	size_t frameSize;
	size_t headSize;
	unsigned char *code;
	unsigned char *coderev;

//	DATALINK_DOWN_FORMAT downBuffer;
//	DATALINK_UP_FORMAT upBuffer;
//	mutex downMutex;

	DataLinkID id;

	thread t;
};


END_NAMESPACE

#endif
