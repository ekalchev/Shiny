///////////////////////////////////////////////////////////////////////////////
//	File:    Semaphore.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////



#ifndef __SEMAPHORE__
#define __SEMAPHORE__

#include <windows.h>

class Semaphore
{
private:
	HANDLE semaphore;
public:
	Semaphore();
	~Semaphore();
	void Release();
	void* GetHandle();
};

inline void* Semaphore::GetHandle()
{
	return (void*)semaphore;
}

#endif