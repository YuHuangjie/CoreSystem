#ifndef DATALINK_H
#define DATALINK_H

#include <string>

#include "Define.h"
#include "DataLinkFormat.h"

BEGIN_NAMESPACE

class DataLink
{
public:
	virtual ~DataLink() {}

	virtual bool Run(void) = 0;
	virtual bool Stop(void) = 0;

	virtual bool Send(const std::string&) = 0;
	virtual bool Recv(std::string &) = 0;

	virtual bool SetDownData(const DATALINK_DOWN_FORMAT &) = 0;
	virtual bool GetUpData(DATALINK_UP_FORMAT &) = 0;

	virtual std::string Down2String(const DATALINK_DOWN_FORMAT &) const = 0;
	virtual std::string Up2String(const DATALINK_UP_FORMAT &) const = 0;
	virtual bool String2Down(const std::string &, DATALINK_DOWN_FORMAT &) const = 0;
	virtual bool String2Up(const std::string &, DATALINK_UP_FORMAT &) const = 0;

};

/**************************************************
 *      Data Link Identity
 *************************************************/
 enum DataLinkID
 {
     DataLinkSender = 0,
     DataLinkReciever = 1,
 };

END_NAMESPACE

#endif
