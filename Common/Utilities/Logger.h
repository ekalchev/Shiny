///////////////////////////////////////////////////////////////////////////////
//	File:    Logger.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __LOGGER__
#define __LOGGER__

#include <iostream>
#include <fstream>
using namespace std;

class Point3D;

class Logger
{
private:
	static Logger* instance;
	ofstream logfile;

private:
	Logger();
	static Logger* GetInstance();

public:
	~Logger();
	static void Log(const char* string);
	static void Log(int value);
	static void Log(int value1,int value2);
	static void Log(Point3D& point);
};

inline Logger* Logger::GetInstance()
{
	if(instance == NULL)
	{
		instance = new Logger();
	}

	return instance;
}

#endif