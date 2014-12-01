///////////////////////////////////////////////////////////////////////////////
//	File:    Event.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __EVENT__
#define __EVENT__

#include <windows.h>

class Event
{
private:
	HANDLE theEvent;
public:
	Event();
	~Event();
	void SetSignalState();
	void ResetState();
	void* GetHandle();
};

inline void* Event::GetHandle()
{
	return theEvent;
}


#endif