///////////////////////////////////////////////////////////////////////////////
//	File:    Logger.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Logger.h"
#include "ShinyMath.h"

#define LOGFILE "..\\shiny.log"

Logger* Logger::instance = NULL;

Logger::Logger()
{
	logfile.open (LOGFILE,ios::app);
	logfile << " -------------- Starting Shiny ------------" << endl;
}

void Logger::Log(const char* string)
{
#ifdef _DEBUG
	Logger* log = Logger::GetInstance();
	log->logfile << string << endl;
#endif
}

void Logger::Log(int value)
{
	Logger* log = Logger::GetInstance();
	log->logfile << value << endl;
}

void Logger::Log(int value1,int value2)
{
	Logger* log = Logger::GetInstance();
	log->logfile << value1 << value2 << endl;
}

void Logger::Log(Point3D& point)
{
	Logger* log = Logger::GetInstance();
	log->logfile << point.x << ',' << point.y << ',' << point.z << endl;
}

Logger::~Logger()
{
	Logger* log = Logger::GetInstance();
	log->logfile.close();
}

