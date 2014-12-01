///////////////////////////////////////////////////////////////////////////////
//	File:    SingleLock.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "SingleLock.h"

SingleLock::SingleLock()
{
	//Initilize the critical section
	InitializeCriticalSection(&cs);
}

SingleLock::~SingleLock()
{
	DeleteCriticalSection(&cs);
}

void SingleLock::Lock()
{
	// Lock the Critical section
	EnterCriticalSection(&cs);
}

void SingleLock::Unlock()
{
	//Release the Critical section
	LeaveCriticalSection(&cs);
}