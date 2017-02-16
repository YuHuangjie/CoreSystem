/*
 * Thread.cpp
 *
 *  Created on: Oct 31, 2016
 *      Author: jacob
 */

#include "Thread.h"

BEGIN_NAMESPACE

Thread::Thread()
{
}

Thread::~Thread()
{
}

bool Thread::Start(void)
{
	t = std::thread(&Thread::Run, this);
	return true;
}

bool Thread::Joinable(void)
{
	return t.joinable();
}

ID Thread::GetID(void)
{
	return t.get_id();
}

uint32_t Thread::HardwareConcurrency(void)
{
	return std::thread::hardware_concurrency();
}

void Thread::Join(void)
{
	t.join();
}

void Thread::Detach(void)
{
	t.detach();
}


END_NAMESPACE
