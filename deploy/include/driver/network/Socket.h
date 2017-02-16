#ifndef SOCKET_H
#define SOCKET_H

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <unistd.h>
#include <cstdint>
#include <string>
#include "Define.h"

using namespace std;

BEGIN_NAMESPACE

class Socket
{
public:
	Socket();
	~Socket();

	bool Bind(const string &address, const uint16_t &port);
	bool Listen(int backlog = 3) const;
	bool Accept(Socket &newSock) const;
/*
 * Select method is omitted because I don't think we need it.
 */
	bool Connect(const string &peerAddr, const uint16_t &peerPort);

	int32_t Read(void *buffer, int32_t length) const;
	int32_t Write(const void *buffer, int32_t length) const;

	/*
	 * setsockopt(fd, , SOL_SOCKET, SO_REUSEADDR)
	 * This method won't help too much, if you want to avoid address reuse.
	 * Please refer this site: http://hea-www.harvard.edu/~fine/Tech/addrinuse.html
	 * To avoid address reuse, the best method is to close normally(maybe this
	 * 	is the only method in our system).
	 * 	So it almost always have bad results to terminate a server/client using Ctrl+C.
	 */

	string GetLocalAddress(void) const;	// return "" on error
	uint16_t GetLocalPort(void) const;	// return -1 on error
	string GetPeerAddress(void) const;	// return "" on error
	uint16_t GetPeerPort(void) const;	// return -1 on error

	bool Close();

public:
	int32_t fd;

};

END_NAMESPACE
#endif
