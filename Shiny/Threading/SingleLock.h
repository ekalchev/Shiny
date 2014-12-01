///////////////////////////////////////////////////////////////////////////////
//	File:    SingleLock.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __SINGLELOCK__
#define __SINGLELOCK__

#include <windows.h>

class SingleLock
{
private:
	CRITICAL_SECTION cs;
public:
	SingleLock();
	~SingleLock();
	void Lock();
	void Unlock();
};


#endif