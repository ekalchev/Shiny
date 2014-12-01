///////////////////////////////////////////////////////////////////////////////
//	File:    Timer.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Timer.h"


Timer::Timer()
{
}

void Timer::StartCounter()
{
	start = clock();
}
void Timer::StopCounter()
{
	end = clock();
}
double Timer::GetTimeDiff()
{
	return (double)(end - start)/CLOCKS_PER_SEC;
}