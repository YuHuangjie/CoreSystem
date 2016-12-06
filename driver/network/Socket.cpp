#include "Socket.h"
#include <iostream>
#include <cassert>

BEGIN_NAMESPACE

Socket::Socket() : fd(-1)
{
}

Socket::~Socket()
{
	Close();
}

bool Socket::Bind(const string &address, const uint16_t &port)
{
	// necessary variables
	struct in_addr _addr;
//	uint16_t _port;
//	int _fd;

	/* If socket descriptor is valid, do nothing */
	if (fd > 0) {
		return false;
	}

	/*
	 * inet_pton convert address from text form to binary
	 * inet_pton returns 1 on success
	 * inet_pton is declared in <arpa/inet.h>
	 */
	if (inet_pton(AF_INET, address.c_str(), &_addr) <= 0) {
		return false;
	}

	/* check the validity of port, shouldn't be well-known port */
	if (port < 1024) {
		return false;
	}
	else {
//		_port = port;
	}

	/*
	 * socket initialize
	 * socket returns 0 on success
	 */
	if ((/*_*/fd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
		return false;
	}

	/* After we have address and port, we fill in a complete socket address structure */
	sockaddr_in completeAddr;
	completeAddr.sin_family = AF_INET;
	completeAddr.sin_addr = _addr;
	completeAddr.sin_port = htons(/*_*/port);	// htons declared in <arpa/inet.h>

	/*
	 * bind a socket to given address and port
	 * bind returns 0 on success
	 */
	if (bind(/*_*/fd, (struct sockaddr *)&completeAddr, sizeof(completeAddr)) != 0) {
		Close();
		return false;
	}

	fd = /*_*/fd;

	return true;
}

bool Socket::Connect(const string &peerAddr, const uint16_t &peerPort)
{
	in_addr serverAddr;
	sockaddr_in server;

	/* generate a socket descriptor if needed */
	if (fd < 0) {
		fd = socket(AF_INET, SOCK_STREAM, 0);
	}
	if (fd < 0) {
		return false;
	}

	/* convert address argument from the form of text to binary */
	if (inet_pton(AF_INET, peerAddr.c_str(), &serverAddr) <= 0) {
		return false;
	}

	/* Check the validity of peer port, shouldn't be well-known port */
	if (peerPort < 1024) {
		return false;
	}

	/* fill in a complete socket address structure that
	 * contains info of the server to connect */
	server.sin_family = AF_INET;
	server.sin_addr = serverAddr;
	server.sin_port = htons(peerPort);

	/* connect to server */
	if (connect(fd, (struct sockaddr*)&server, sizeof(server)) < 0) {
		return false;
	}

	return true;
}

/*
 * listen for incoming connection
 */
bool Socket::Listen(int backlog) const
{
	if (fd < 0) {
		return false;
	}

	/* set backlog to 0 indicates the backlog
	 * will be set to implementation-defined minimum */
	if (backlog < 0) {
		backlog = 0;
	}

	if (listen(fd, backlog) != 0) {
		return false;
	}

	return true;
}

bool Socket::Accept(Socket &newSock) const
{
	int32_t acceptedFd;
	struct sockaddr_in address;
	int32_t addrlen = sizeof(address);

	/* Check the validity of host socket */
	if (fd < 0) {
		newSock.fd = -1;
		return false;
	}

	/*
	 * Server accepts try to accept an incoming connection.
	 * On success, new socket descriptor is given to newSock and true is returned.
	 * On error, false is returned. newSock is undefined.
	 *
	 * FROM LINUX MANUAL:
	 * If no pending connections are present on the queue, and the  socket  is
     * not  marked  as nonblocking, accept() blocks the caller until a connec‐
     * tion is present.  If the socket is marked nonblocking  and  no  pending
     * connections  are  present  on  the queue, accept() fails with the error
     * EAGAIN or EWOULDBLOCK.
	 */
	acceptedFd = accept(fd, (struct sockaddr*)&address, (socklen_t *)&addrlen);

	if (acceptedFd == -1) {
		newSock.fd = -1;
		return false;
	}

	newSock.fd = acceptedFd;

	return true;
}

int32_t Socket::Read(void *buffer, int32_t length) const
{
	/* Check validity of arguments. */
	if (buffer == nullptr || length <= 0) {
		return -1;
	}
	/* Check validity of active socket */
	if (fd < 0) {
		return -1;
	}

	/*
	 * One call of read may return value less than length.
	 * This method attempt to guarantees length bytes of data are read.
	 * If the actual value  returned is less than length, it means some
	 * error occurs or EOF has been encountered.
	 *
	 * (FROM LINUX MANUAL)
	 * It is not  an error  if  this  number  is smaller than the number
	 * of bytes requested; this may happen for example because fewer bytes
	 * are actually  available right  now  (maybe  because we were close to
	 * end-of-file, or because we are reading from a pipe, or from a terminal),
	 *  or  because  read()  was interrupted by a signal.
     */
	int32_t bytesRead = 0;
	int32_t ret;
	char *p = static_cast<char *>(buffer);

	while (bytesRead < length) {
		/* For void pointers, arithmetics are not allowed */
		ret = read(fd, static_cast<void*>(p + bytesRead), length - bytesRead);

		/* Some errors occur. Return bytes read so far. */
		if (ret < 1) {
			return bytesRead;
		}

		bytesRead += ret;
	}

	return bytesRead;
}

int32_t Socket::Write(const void *buffer, int32_t length) const
{
	/* Check validity of arguments. */
	if (buffer == nullptr || length <= 0) {
		return -1;
	}
	/* Check validity of active socket */
	if (fd < 0) {
		return false;
	}

	/*
	 * This method is similar to Read. I will attempt to write length bytes
	 * to socket descriptor. However, a smaller return value may indicated that
	 * some errors had occurred that I can do nothing with.
	 */
	int32_t bytesWrote = 0;
	int32_t ret;
	const char *p = static_cast<const char *>(buffer);

	while (bytesWrote < length) {
		ret = write(fd, static_cast<const void*>(p + bytesWrote), length - bytesWrote);

		if (ret < 1) {
			return bytesWrote;
		}

		bytesWrote += ret;
	}
	return bytesWrote;
}

//bool Socket::SelectRead(const Socket *insock, const int &input,
//						int **outsock, int &output, uint32_t timeout) const
//{
//	if (insock == nullptr || input <= 0) {
//		return false;
//	}
//	if (fd < 0) {
//		return false;
//	}
//
//	int maxsd = 0 , sd;
//	fd_set readfds;
//
//	// clear the socket set
//	FD_ZERO(&readfds);
//
//	// add child sockets to set
//	for (int i = 0; i != input; ++i) {
//		// socket descriptor
//		sd = insock[i].fd;
//
//		// if valid socket descriptor then add to read list
//		if (sd > 0) {
//			FD_SET(sd, &readfds);
//		}
//
//		// highest file descriptor number, need it for the select function
//		if (sd > maxsd)
//			maxsd = sd;
//	}
//
//	// wait for an activity on one of the sockets for timeout
//	// if timeout is NULL, wait indefinitely
//	struct timeval time = {timeout, 0};
//	int activity = select(maxsd + 1, &readfds, NULL, NULL, &time);
//
//	if (activity < 0) {
//		return false;
//	}
//
//	// check how many readfds are activated
//	output = activity;
//	outsock = new int*;
//	*outsock = new int[output];
//	int checkout = 0;
//
//	for (int i = 0; i != input; ++i) {
//		sd = insock[i].fd;
//
//		// Check if it is activated
//		if (FD_ISSET(sd, &readfds)) {
//			*outsock[checkout++] = i;
//		}
//	}
//
//	assert(checkCount == output);
//	return true;
//}


/*
 * To close properly.
 * NOTE: Even after the socket is closed, the socket will be in TIME_WAIT state.
 * 		 For about 1 or 2 minutes, the same port can't be used to bind another socket.
 */
bool Socket::Close()
{
	/* Close valid socket descriptor */
	if (fd > 0) {
		// clean any errors
		int err = 1;
		socklen_t len = sizeof(err);
		if (getsockopt(fd, SOL_SOCKET, SO_ERROR, (char*)&err, &len) == -1) {
			std::cerr << "get SO_ERROR fail" << std::endl;
		}
		if (err)
			errno = err;
		
		// secondly, terminate the 'reliable' delivery
		if (shutdown(fd, SHUT_RDWR) < 0) {
			if (errno != ENOTCONN && errno != EINVAL)
				std::cerr << "socket shutdown fail" << std::endl;
		}
		if (close(fd) < 0) {
			std::cerr << "close socket fail" << std::endl;	
		}
	}
	
	fd = -1;

	return true;
}

/*
 * Return the local address to which the socket is bound on success.
 * On error, an empty string is returned.
 */
string Socket::GetLocalAddress(void) const
{
	if (fd < 0) {
		return "";
	}

	sockaddr_in addr;
	socklen_t len = sizeof(addr);
	char str[INET_ADDRSTRLEN];

	if (getsockname(fd, (struct sockaddr *)&addr, &len) != 0) {
		return "";
	}

	return string(inet_ntop(AF_INET, &(addr.sin_addr), str, INET_ADDRSTRLEN));
}

/*
 * Return the port to which the socket is bound on success.
 * On error, -1 is returned.
 */
uint16_t Socket::GetLocalPort(void) const
{

	if (fd < 0) {
		return -1;
	}

	sockaddr_in addr;
	socklen_t len = sizeof(addr);

	if (getsockname(fd, (struct sockaddr *)&addr, &len) != 0) {
		return -1;
	}

	return ntohs(addr.sin_port);
}

/*
 * Return the address of the peer connected to host socket on success.
 * On error, an emptry string is returned.
 */
string Socket::GetPeerAddress(void) const
{
	if (fd < 0) {
		return "";
	}

	sockaddr_in addr;
	socklen_t len = sizeof(addr);
	char str[INET_ADDRSTRLEN];

	if (getpeername(fd, (struct sockaddr *)&addr, &len) != 0) {
		return "";
	}

	return string(inet_ntop(AF_INET, &(addr.sin_addr), str, INET_ADDRSTRLEN));
}

/*
 * Return the port of peer connected to the host socket on success.
 * On error, -1 is returned.
 */
uint16_t Socket::GetPeerPort(void) const
{
	if (fd < 0) {
		return -1;
	}

	sockaddr_in addr;
	socklen_t len = sizeof(addr);

	if (getpeername(fd, (struct sockaddr *)&addr, &len) != 0) {
		return -1;
	}

	return ntohs(addr.sin_port);
}


END_NAMESPACE
