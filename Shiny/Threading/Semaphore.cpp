///////////////////////////////////////////////////////////////////////////////
//	File:    Semaphore.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Semaphore.h"

#define MAX_COUNT 10000

Semaphore::Semaphore()
{
	semaphore = CreateSemaphore( 
        NULL,           // default security attributes
        0,				// initial count
        MAX_COUNT,		// maximum count
        NULL);          // unnamed semaphore
}

Semaphore::~Semaphore()
{
	CloseHandle(semaphore);
}

void Semaphore::Release()
{
         ReleaseSemaphore( 
                        semaphore,    // handle to semaphore
                        1,            // increase count by one
                        NULL);       // not interested in previous count
}