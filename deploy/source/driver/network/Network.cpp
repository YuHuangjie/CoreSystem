#include "Network.h"
#include <algorithm>
BEGIN_NAMESPACE

/*
 * Send a message header and it's related following Message m to peer.
 * Because header and Message are considered as struct, we should ensure
 * they get serialized correctly. So, here's a rule, every struct
 * (even single variable) that has a chance to be sent on wire should
 * provide a Pack method for serialization, and an Unpack method for
 * deserialization.
 *
 * The protocol of writing a message is as following:
 * 	{LengthOfHeader(int32_t)}  {header(string)}  {data(string)}
 */
bool Network::WriteMessage(MessageHeader &header, MessageData *const m) const
{
	int32_t sizeOfHeader = 0;
	string dataPack = "";	// string of data
	string headerPack = "";	// string of header
	ostringstream oss;
	int32_t ret;

	if (m != nullptr) {
		dataPack = m->Pack();
	}
	else {
		dataPack = "";
	}
	// note data string size is less by 1 than it's raw char data
	header.length = dataPack.size() + 1;
	headerPack = header.Pack();


	// sent size of header
	// note string size is less by 1 than it's raw char data
	sizeOfHeader = headerPack.size() + 1;
	ret = Write(&sizeOfHeader, sizeof(sizeOfHeader));
	if (ret != sizeof(sizeOfHeader)) {
		return false;
	}

	// send header
	ret = Write(headerPack.c_str(), sizeOfHeader);
	if (ret != sizeOfHeader) {
		return false;
	}

	// send data, even if data is empty, an ending \0 should be sent
	ret = Write(dataPack.c_str(), header.length);
	if (ret != header.length) {
		return false;
	}

	return true;

}

bool Network::ReadMessage(const MessageHeader &header, MessageData * const m) const
{
	uint32_t sizeOfMsg = header.length;
	char buffer[1024];
	string raw;
	int32_t ret;

	// receive raw message data
	ret = Read(buffer, sizeOfMsg);
	if (ret != sizeOfMsg) {
		return false;
	}
	if (ret > 1) {
		// reconstruct Message m
		raw = string(buffer);
		m->Unpack(raw);
	}

	return true;
}

bool Network::ReadMessageHeader(MessageHeader &header) const
{
	char buffer[1024];
	int32_t sizeOfHeader = 0;
	int32_t ret;

	// receive header size
	ret = Read(&sizeOfHeader, sizeof(sizeOfHeader));
	if (ret != sizeof(sizeOfHeader)) {
		return false;
	}

	// receive header raw data
	ret = Read(buffer, sizeOfHeader);
	if (ret != sizeOfHeader) {
		return false;
	}

	// reconstruct header
	string raw(buffer);
	ret = header.Unpack(raw);
	if (ret == 0) {
		return false;
	}

	return true;
}


END_NAMESPACE
