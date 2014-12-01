///////////////////////////////////////////////////////////////////////////////
//	File:    Win32Thread.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Thread.h"
#include "Task.h"
#include "TaskManager.h"
#include "Semaphore.h"

Thread::Thread() : thread(NULL),bWorking(false),task(NULL),taskManager(NULL)
{

}

Thread::~Thread()
{

}

void Thread::Create(TaskManager* man,Semaphore* sem)
{	
	thread = ::CreateThread(NULL,0,Thread::threadFunc,(LPVOID)this,0,&dwGenericThread);
	assert(thread != NULL);
	semaphore = sem;
	taskManager = man;
}

void Thread::Destroy()
{
	TerminateThread(thread,0);
	CloseHandle(thread);
}

DWORD WINAPI Thread::threadFunc(LPVOID param)
{
	while(true)
	{
		Thread* thread = (Thread*) param;
		assert(thread->semaphore != NULL);		

		WaitForSingleObject((HANDLE)thread->semaphore->GetHandle(),INFINITE);
		thread->bWorking = true;

		Task *task = thread->taskManager->getTask();
		assert(task != NULL);
		task->Do();
			
		//mark task as finished
		task->setState(Task::E_FINISHED);					
		task->SignalEvent();
		thread->bWorking = false;
	}
	return 0;
}