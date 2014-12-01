///////////////////////////////////////////////////////////////////////////////
//	File:    TaskManager.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "TaskManager.h"
#include "Thread.h"
#include "Task.h"
#include "Event.h"
#include "Semaphore.h"


TaskManager* TaskManager::instance = NULL;

TaskManager::TaskManager(int threadPoolSize) : poolSize(threadPoolSize)
{
	semaphore = new Semaphore();
	threadPool = new Thread[poolSize]();
	events = new Event[poolSize]();
	

	for(int i = 0;i < poolSize; ++i)
	{
		threadPool[i].Create(this,semaphore);
	}
}

TaskManager::~TaskManager()
{	
	for(int i = 0;i < poolSize; ++i)
	{
		threadPool[i].Destroy();
	}

	delete semaphore;
	delete[] threadPool;
	delete[] events;	
}

void TaskManager::StartTasks()
{

}

void TaskManager::clearTasks()
{
	std::vector<Task*>::iterator iter;
	for(iter = taskList.begin();iter != taskList.end(); ++iter)
	{
		delete (*iter);
	}
	taskList.clear();
}

void TaskManager::addTask(Task* task)
{
	taskList.push_back(task);	
	semaphore->Release();
}



Task* TaskManager::getTask()
{
	Task *ret = NULL;
	for(int i = 0; i < taskList.size(); ++i)
	{
		cs.Lock();
		//if there is task waiting to be executed, run it
		if(taskList[i]->getState() == Task::E_WAITING)
		{
			taskList[i]->setState(Task::E_WORKING);
			ret = taskList[i];
			cs.Unlock();
			break;
		}
		cs.Unlock();
	}

	return ret;
}

void TaskManager::WaitForAllTasks()
{
	std::vector<Task*>::iterator iter;
	for(iter = taskList.begin();iter != taskList.end(); ++iter)
	{
		WaitForSingleObject((HANDLE)(*iter)->GetEvent()->GetHandle(),INFINITE);
	}


}

bool TaskManager::isWorking()
{
	for(int i = 0;i < poolSize; ++i)
	{
		if(threadPool[i].isWorking() == true)
			return true;
	}
	return false;
}

TaskManager* TaskManager::getInstance()
{
	if(instance == NULL)
	{
		instance = new TaskManager(NUM_THREADS);
	}
	return instance;
}

void TaskManager::DestroySingleton()
{
	if(instance != NULL)
	{
		delete instance;
	}
}