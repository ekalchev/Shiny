///////////////////////////////////////////////////////////////////////////////
//	File:    Thread.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __THREAD__
#define __THREAD__

#include <windows.h>

class Task;
class TaskManager;
class Thread;
class Semaphore;

class Thread
{
private:
	HANDLE thread;
	DWORD dwGenericThread;
	volatile bool bWorking;
	TaskManager* taskManager;
	int id;
	Task *task;
	Semaphore *semaphore;
private:
	static DWORD WINAPI threadFunc(LPVOID param);
public:
	Thread();
	~Thread();
	void Create(TaskManager* man,Semaphore* sem);
	bool isWorking();
	void Destroy();
};

inline bool Thread::isWorking()
{
	return bWorking;
}




#endif
