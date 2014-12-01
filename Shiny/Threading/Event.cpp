///////////////////////////////////////////////////////////////////////////////
//	File:    Event.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////



#include "stdafx.h"
#include "Event.h"

Event::Event() : theEvent(NULL)
{
	theEvent = CreateEvent( 
            NULL,     // no security attributes
            FALSE,    // auto-reset event
            FALSE,     // initial state is signaled
            NULL);    // object not named
	assert(theEvent != NULL);
}

Event::~Event()
{
	CloseHandle(theEvent);
}

void Event::SetSignalState()
{
	SetEvent(theEvent);
}

void Event::ResetState()
{
	ResetEvent(theEvent);
}