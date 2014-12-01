///////////////////////////////////////////////////////////////////////////////
//	File:    Task.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __TASK__
#define __TASK__

#include "Event.h"


class Task
{
private:
	Event theEvent;
public:
	enum E_STATE
	{
		E_WAITING,
		E_WORKING,
		E_FINISHED
	};
	E_STATE state;
public:
	Task::Task();
	virtual void Do() = 0;
	virtual ~Task();
	E_STATE getState();
	void setState(Task::E_STATE taskState);
	void SignalEvent();
	void ResetEvent();
	Event* GetEvent();
};

inline void Task::setState(Task::E_STATE taskState)
{
	state = taskState;
}

inline Task::E_STATE Task::getState()
{
	return state;
}

inline Event* Task::GetEvent()
{
	return &theEvent;
}

inline void Task::ResetEvent()
{
	theEvent.ResetState();
}

inline void Task::SignalEvent()
{
	theEvent.SetSignalState();
}

#endif