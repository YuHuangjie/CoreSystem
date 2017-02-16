/*
 * Thread.h
 *
 *  Created on: Oct 31, 2016
 *      Author: jacob
 */

#ifndef THREAD_H_
#define THREAD_H_

#include "Define.h"
#include <thread>

BEGIN_NAMESPACE

typedef std::thread::id ID;

class Thread
{

public:
	Thread();
	virtual ~Thread();

	bool Start();

	/* observers */
	bool Joinable(void);
	ID GetID(void);
	static uint32_t HardwareConcurrency(void);

	/* operations */
	void Join(void);
	void Detach(void);

protected:
	virtual bool Run() = 0;

protected:
	std::thread t;
};

END_NAMESPACE

#endif /* THREAD_H_ */
