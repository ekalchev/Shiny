///////////////////////////////////////////////////////////////////////////////
//	File:    TaskManager.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////



#ifndef __TASKMANAGER__
#define __TASKMANAGER__

#include <vector>
#include <windows.h>
#include "SingleLock.h"

class Thread;
class Task;
class Event;
class Semaphore;

class TaskManager
{
private:
	int poolSize;
	Thread *threadPool;
	Event *events;
	std::vector<Task*> taskList;
	static TaskManager* instance;
	SingleLock cs;
	Semaphore *semaphore;
private:
	TaskManager(int threadPoolSize);
public:
	~TaskManager();
	void addTask(Task* task);
	void StartTasks();
	void clearTasks();
	void taskFinished();
	Task* getTask();
	static TaskManager* getInstance();
	bool isWorking();
	int GetThreadPoolSize();
	void WaitForAllTasks();
	static void DestroySingleton();
};

inline int TaskManager::GetThreadPoolSize()
{
	return poolSize;
}

#endif