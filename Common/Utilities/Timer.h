///////////////////////////////////////////////////////////////////////////////
//	File:    Timer.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __TIMER__
#define __TIMER__

#include <time.h>

class Timer
{
private:
	clock_t start;
	clock_t end;
public:
	Timer();
	void StartCounter();
	void StopCounter();
	double GetTimeDiff();
};

#endif